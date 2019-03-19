#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80 
#define PORT 8080
#define SA struct sockaddr 
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"


void ChildProcess(int sockfd)
{
	char buff[MAX]; 
    	int n; 
    	for (;;) { 
        	bzero(buff, sizeof(buff)); 
        	printf(COLOR_BLUE "Escribe Mensaje : "); 
        	n = 0; 
        	while ((buff[n++] = getchar()) != '\n') 
            	; 
        	write(sockfd, buff, sizeof(buff)); 
        	if ((strncmp(buff, "exit", 4)) == 0) { 
            		printf("Client Exit...\n"); 
            		break; 
        	} 
    	} 
	printf("Child process is done\n");
}

void ParentProcess(int sockfd)
{
	char buff[MAX]; 
    	int n; 
    	for (;;) {  
        	bzero(buff, sizeof(buff)); 
        	read(sockfd, buff, sizeof(buff)); 
        	printf(COLOR_GREEN "\nFrom Server : %s", buff, COLOR_BLUE, "\nEscribe mensaje:"); 
        	if ((strncmp(buff, "exit", 4)) == 0) { 
            		printf("Client Exit...\n"); 
            		break; 
        	} 
    	} 
	printf("Parent is donde\n");
}

void main(void){
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	//Creacion de socekt y validacion
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1){
		printf("Error al crear el socket...\n");
		exit(0);
	}
	else
		printf("Socket creado con exito...\n");
	bzero(&servaddr,sizeof(servaddr));

	//Asigna IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	//Conectar cliente sockets a servidor sockets
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){
		printf("Error de conexion con el servidor...\n");
		exit(0);
	}
	else
		printf("Exito de conexion con el servidor...\n");
	//Funcion para el chat
	pid_t pid;
	pid = fork();
	if(pid == 0)
		ChildProcess(sockfd);
	else
		ParentProcess(sockfd);	

	//Cerrar socket
	close(sockfd);

}
