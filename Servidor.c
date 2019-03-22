#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <netdb.h> 
#include <netinet/in.h>  
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include "Servidor.h"
#define MAX 80 
<<<<<<< HEAD
#define PORT 8080
#define LENGTH_NAME 31
#define LENGTH_MSG 101
#define LENGTH_SEND 201 
=======
#define PORT 8080 
>>>>>>> master
#define SA struct sockaddr
#define COLOR_BLUE    "\x1b[34m" 
#define COLOR_GREEN   "\x1b[32m"

<<<<<<< HEAD
ClientList *root, *now;

void readFuncion(int sockfd){
    char buff[MAX]; 	
    for(;;){
        bzero(buff, MAX); 
	// read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf(COLOR_GREEN "Desde el Cliente: %s", buff);     
=======

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
>>>>>>> master
    }
}

void writeFuncion(int sockfd){
    char buff[MAX]; 
    int n; 
    for(;;){
<<<<<<< HEAD
	bzero(buff, MAX);
	n = 0;
=======
>>>>>>> master
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n'); 
  	// send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
    }
} 

<<<<<<< HEAD

void send_to_all_clients(ClientList *np, char tmp_buffer[]) {
    ClientList *tmp = root->link;
    while (tmp != NULL) {
        if (np->data != tmp->data) { // all clients except itself.
            printf("Send to sockfd %d: \"%s\" \n", tmp->data, tmp_buffer);
            send(tmp->data, tmp_buffer, LENGTH_SEND, 0);
        }
        tmp = tmp->link;
    }
}

void client_handler(void *p_client) {
    int leave_flag = 0;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientList *np = (ClientList *)p_client;

    // Naming
    if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) {
        printf("%s didn't input name.\n", np->ip);
        leave_flag = 1;
    } else {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("%s(%s)(%d) join the chatroom.\n", np->name, np->ip, np->data);
        sprintf(send_buffer, "%s(%s) join the chatroom.", np->name, np->ip);
        send_to_all_clients(np, send_buffer);
    }

    // Conversation
    while (1) {
        if (leave_flag) {
            break;
        }
        int receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
        if (receive > 0) {
            if (strlen(recv_buffer) == 0) {
                continue;
            }
            sprintf(send_buffer, "%s：%s from %s", np->name, recv_buffer, np->ip);
        } else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) {
            printf("%s(%s)(%d) leave the chatroom.\n", np->name, np->ip, np->data);
            sprintf(send_buffer, "%s(%s) leave the chatroom.", np->name, np->ip);
            leave_flag = 1;
        } else {
            printf("Fatal Error: -1\n");
            leave_flag = 1;
        }
        //send_to_all_clients(np, send_buffer);
    }

    // Remove Node
    close(np->data);
    if (np == now) { // remove an edge node
        now = np->prev;
        now->link = NULL;
    } else { // remove a middle node
        np->prev->link = np->link;
        np->link->prev = np->prev;
    }
    free(np);
}
=======
>>>>>>> master
  
// Driver function 
int main() 
{ 	

    int server_sockfd, client_sockfd, len; 
    struct sockaddr_in server_info, client_info; 
  
    // Socket create and verification 
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_sockfd == -1) { 
        printf("[-]Socket creation failed...\n"); 
        exit(0); 
<<<<<<< HEAD
    }else{
        printf("[+]Socket successfully created...\n");
    }
    
    // Assign socket information(IP, PORT)
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);	 
    server_info.sin_family = AF_INET; 
    server_info.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_info.sin_port = htons(PORT); 
=======
    } 
    else
        printf("[+]Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
>>>>>>> master
  
    // Binding newly created socket to given IP and verification 
    if ((bind(server_sockfd, (SA*)&server_info, s_addrlen)) != 0) { 
        printf("[-]Socket bind failed...\n"); 
        exit(0); 
<<<<<<< HEAD
    }else{
        printf("[+]Socket successfully binded...\n"); 
    }

=======
    } 
    else
        printf("[+]Socket successfully binded..\n"); 
  
>>>>>>> master
    // Now server is ready to listen and verification 
    if ((listen(server_sockfd, 5)) != 0) { 
        printf("[-]Listen failed...\n"); 
        exit(0); 
<<<<<<< HEAD
    }else{
        printf("[+]Server listening...\n"); 
    }
    
    // Initial linked list for clients
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
    now = root;    
 
    getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("[+]Start Server on: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
	
    pid_t childpid;

    while(1){
        // Accept the data packet from client and verification 
        client_sockfd = accept(server_sockfd, (SA*)&client_info, &s_addrlen); 
    
        if (client_sockfd < 0) { 
            printf("[-]server acccept failed...\n"); 
            exit(0); 
        }else{
            printf("[+]Server acccept the client...\n"); 
        }

	ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
	c->prev = now;
	now->link = c;
	now = c;

	if((childpid = fork()) == 0){
	    client_handler((void *)c);
	}
    }

    close(server_sockfd);
    return 0; 
=======
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
>>>>>>> master
} 

