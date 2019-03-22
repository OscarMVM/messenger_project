Tarea Programada #1

Lenguajes de programación

Tecnológico de Costa Rica

Documentación Messenger en C

Integrantes: Natalia Rodríguez y Oscar Vega

Fecha: 22 de Marzo del 2019

En la actualidad existen innovadores medios de comunicación, uno de estos son los chats virtuales. En el siguiente documento se describe el programa de software desarrollado. Messenger es un programa de mensajería entre varios usuarios. 
    
En este proyecto se desarrolló un programa que contiene un servidor central que almacena la información de los usuarios. Los usuarios se pueden mandar mensajes a través del servidor, esto quiere decir que si un usuario A quiere mandar un mensaje al usuario B, tiene que mandarlo por medio del servidor central.
    
Al comenzar la ejecución del programa, el servidor se conecta por medio de sockets con los clientes. Cada cliente digita un nombre de usuario donde se van almacenar en el servidor central, además se obtiene de forma automática el IP del usuario. Se va a manejar un archivo de configuración donde se almacena el puerto de los clientes. El programa de los clientes lee este archivo automáticamente, para conectarse con el servidor. 
    
Para recibir y enviar mensajes de manera simultánea, se utiliza la función de fork, que funciona de la siguiente manera: Esta genera un duplicado del proceso actual. El duplicado comparte los valores actuales de todas las variables, fichero y otras estructuras de datos. La llamada a fork retorna al proceso padre el identificador del proceso hijo y retorna un cero al proceso hijo. 


Librerías utilizadas:

1. #include <stdio.h>: significa “estándar entrada/salida”, contiene macro definiciones, declaraciones de funciones y tipos usados para la entrada de varios estándar y operaciones de salida. 

2. #include <sys/socket.h>: se utiliza para hacer uso de los sockets en C.

3. #include <stdlib.h>: contiene los prototipos de funciones d C para gestionar memoria dinámica, control de procesos y otras.

4. #include <string.h>: contiene definiciones de macros constantes, funciones y tipos de algunas operaciones de manipulación de memoria. 

5. #include <netinet/in.h>: define la estructura de sockaddr_in. Esta estructura se utiliza para almacenar direcciones para la familia de protocolos de Internet, estos se utilizan para las interfaces de sockets. 

6. #include <sys/types.h>: contiene definiciones de algunos tipos como los siguientes utilizados: pid_t y size_t.

7. #include <netinet/in.h>: define los tipos in_port_t, que es un tipo integral indefinido de exactamente 16 bits y el tipo in_addr_t, el cual es un tipo integral indefinido de 32 bits.

8. #include <arpa/inet.h>: este encabezado habilita el tipo in_port_t y el tipo in_addr_t que se definen en <netinet/in.h>.



Pasos a seguir para compilar el código y generar ejecutable:

1. Se deben tener los archivos en una misma carpeta.
2. Para el servidor, digitar en la terminal digitar “cd PathDeCarpeta”.
3. Digitar en la terminal “gcc Servidor.c -o Servidor”.
4. Digitar en la terminal “./Servidor”.
5. Seguidamente va a esperar a que se conecten los clientes.
6. Para los clientes, digitar terminales aparte “cd PathDeCarpeta”.
7. Digitar en las terminales “gcc Cliente.c -o Cliente”.
8. Digitar en la terminal “./Cliente”.
9. Se van a conectar con el servidor.
10. Cada cliente debe digitar un nombre de usuario. 
11. Está listo para iniciar la conversación. 


Referencias:

1. Para las pruebas iniciales de sockets y el código inicial:
Shukla, Y. (n.d.). TCP Server-Client implementation in C - GeeksforGeeks. [online] GeeksforGeeks.https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

2. Para la investigación y comprensión de la función fork() se utilizó: 
Csl.mtu.edu. (n.d.). The fork() System Call. [online] Available at: http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html

3. Investigación de las librerías:
The Open Group (1997). System Headers. [online] The Single Unix. Available at: https://pubs.opengroup.org/onlinepubs/7990989775/xns/netinetin.h.html 

4. Investigación para obtener IP de manera automática:
Includehelp.com. (n.d.). C program to Get Computer System IP Address in Linux - IncludeHelp. [online] Available at: https://www.includehelp.com/c-programs/get-ip-address-in-linux.aspx


