#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#define MAX 80 
#define PORT 8080
#define SA struct sockaddr 
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"
#define LENGTH_NAME 31



void ChildProcess(int sockfd)
{
	char buff[MAX]; 
    	int n; 
    	for (;;) { 
        	bzero(buff, sizeof(buff));
		COLOR_BLUE; 
        	printf(COLOR_BLUE ">"); 
        	n = 0; 
        	while ((buff[n++] = getchar()) != '\n') 
            	; 
        	write(sockfd, buff, sizeof(buff)); 
        	if ((strncmp(buff, "exit", 4)) == 0) { 
            		printf("Client Exit...\n"); 
            		break; 
        	} 
    	} 
}

void ParentProcess(int sockfd)
{
	char buff[MAX]; 
    	int n; 
    	for (;;) {  
        	bzero(buff, sizeof(buff)); 
        	read(sockfd, buff, sizeof(buff)); 
        	printf(COLOR_GREEN "\nFrom Server : %s", buff); 
        	if ((strncmp(buff, "exit", 4)) == 0) { 
            		printf("Client Exit...\n"); 
            		break; 
        	} 
    	} 
}

void str_trim_lf (char* arr, int length) {
    int i;
    for (i = 0; i < length; i++) { // trim \n
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

void main(void){
	char nickname[LENGTH_NAME] = {};

	//Ask for the nickname and validates
	printf("Please enter your nickname: ");
	
	if (fgets(nickname, LENGTH_NAME, stdin) != NULL) {
        	str_trim_lf(nickname, LENGTH_NAME);
    	}
    	if (strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) {
        	printf("\nNickname must be more than one and less than thirty characters.\n");
        	exit(EXIT_FAILURE);
	}

	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	//Socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1){
		printf("[-]Socket creation failed...\n");
		exit(0);
	}
	else
		printf("[+]Socket successfully binded...\n");
	bzero(&servaddr,sizeof(servaddr));

	//Assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	//Connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){
		printf("[-]Connection with the server failed...\n");
		exit(0);
	}
	else
		printf("[+]Connected to the server...\n");
	
	//Function fork() for the chat
	pid_t pid;
	pid = fork();
	if(pid == 0)
		ChildProcess(sockfd);
	else
		ParentProcess(sockfd);	

	//Close socket
	close(sockfd);

}
