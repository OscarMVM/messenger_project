#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> 
#include <netdb.h> 
#include <netinet/in.h>  
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "Servidor.h"
#define MAX 80 
#define PORT 8080
#define LENGTH_NAME 31
#define LENGTH_MSG 101
#define LENGTH_SEND 201 
#define SA struct sockaddr
#define COLOR_BLUE    "\x1b[34m" 
#define COLOR_GREEN   "\x1b[32m"

int server_sockfd = 0, client_sockfd = 0;
ClientList *root, *now;


void send_to_all_clients(ClientList *np, char tmp_buffer[]) {
    ClientList *tmp = root->link;
    while (tmp != NULL) {
        if (np->data != tmp->data) { // all clients except itself.
            printf("Send to sockfd %d: \"%s\" \n", tmp->data, tmp_buffer);
	    write(tmp->data, tmp_buffer, LENGTH_SEND);
            //send(tmp->data, tmp_buffer, LENGTH_SEND, 0);
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
        printf("%s:(%s)(%d) join the chatroom.\n", np->name, np->ip, np->data);
        sprintf(send_buffer, "%s:(%d) join the chatroom.", np->name, np->data);
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
            sprintf(send_buffer, "%s : %s from %s", np->name, recv_buffer, np->ip);
        } else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) {
            printf("%s(%s)(%d) leave the chatroom.\n", np->name, np->ip, np->data);
            sprintf(send_buffer, "%s(%s) leave the chatroom.", np->name, np->ip);
            leave_flag = 1;
        } else {
            printf("Fatal Error: -1\n");
            leave_flag = 1;
        }
	send_to_all_clients(np, send_buffer);
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
  
// Driver function 
int main() 
{ 	
    struct sockaddr_in server_info, client_info; 
  
    // Socket create and verification 
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_sockfd == -1) { 
        printf("[-]Socket creation failed...\n"); 
        exit(0); 
    }else{
        printf("[+]Socket successfully created...\n");
    }
    
    // Assign socket information(IP, PORT)
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);	 
    server_info.sin_family = PF_INET; 
    server_info.sin_addr.s_addr = INADDR_ANY; 
    server_info.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(server_sockfd, (SA*)&server_info, s_addrlen)) != 0) { 
        printf("[-]Socket bind failed...\n"); 
        exit(0); 
    }else{
        printf("[+]Socket successfully binded...\n"); 
    }

    // Now server is ready to listen and verification 
    if ((listen(server_sockfd, 5)) != 0) { 
        printf("[-]Listen failed...\n"); 
        exit(0); 
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
    	getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
	printf("Client %s:%d come in.\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
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
		client_handler((void*)c);
	}
    }

    close(server_sockfd);
    return 0; 
} 


