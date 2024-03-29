
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr
#define COLOR_BLUE    "\x1b[34m" 
#define COLOR_GREEN   "\x1b[32m"


void readFuncion(int sockfd){
    char buff[MAX]; 
    int n; 	
    for(;;){
	// read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf(COLOR_GREEN "Desde el Cliente: %s", buff); 
        n = 0;
	// if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        }
        bzero(buff, MAX);    
    }
}

void writeFuncion(int sockfd){
    char buff[MAX]; 
    int n; 
    for(;;){
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n'); 
  	// send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
    }
} 

  
// Driver function 
int main() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("[+]Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("[+]Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("[+]Server listening...\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("[+]Server acccept the client...\n"); 
  
    // Funcion para el chat
    if(fork() == 0){
        readFuncion(connfd);
    }else{
        writeFuncion(connfd);
    }
  
    // After chatting close the socket 
    close(sockfd); 
} 

