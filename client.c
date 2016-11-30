// Client socket
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>

//void* send_handler(void*);
//void* recv_handler(void*);

int main () {

/* .... */
   bool exit_loop = true;
   int sockclient;
   struct sockaddr_in server;
   char buff[1024];

   int sock = socket(AF_INET,SOCK_STREAM,0);


   if (sock < 0) {
      perror("Cant create socket:  ");
      exit(1);
    }

    printf("=> Socket Created succesfully...\n\n");

    server.sin_port = htons(1529);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;

    if (connect (sock,(struct sockaddr*)&server,sizeof(server)) < 0 ) {
       perror("Cant connect to server!: ");
       exit(1);

    }

    printf("=> Connected!\n");

    while (exit_loop) {
      // We need Two (send,receive loop inside)


      /* send while */
       while ( *buff != '#' ) {
       printf("Enter Message:  ");
          scanf("%s",buff);
          //printf("%s \n\n",buff);
           send(sock,buff,strlen(buff),0);
        if (*buff == '#') {
            exit_loop = false;

          }
       }

       /*Receive while
        while ( *buff != '#' ) {
        printf("0xff ?\n\n");
          //printf("%s \n\n",buff);
           recv(sock,buff,strlen(buff),0);
           printf("\n Server: %s ",buff);
        if (*buff == '#') {
            exit_loop = false;

          }
       }
*/
    }

 printf("=> Morcha kino wait saxlshi \n\n");

   return 0;
}

//void* recv_handler(void* sock_ptr) {
 //int sock = *(int *) sock_ptr;
//}
