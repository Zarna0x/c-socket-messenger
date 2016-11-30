#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

int main () {
   int client_sock, server_sock;
   int port_num = 1529;
   bool exit_loop = true;
   int buff_size = 1024;
   char buffer[buff_size];
   char buff[buff_size];
   struct sockaddr_in server,client;
   socklen_t size;
   char *client_addr;
   int client_port;
   int read_size;
   int send_size;
   // init socket

   client_sock = socket(AF_INET,SOCK_STREAM,0);

   if (client_sock < 0) {
      perror("Cant create socket: ");
      exit(1);
   }

   printf("Server Socket connection created\n\n");


   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = htons(INADDR_ANY);
   server.sin_port        = htons(port_num);

   // bind socket

   if (bind (client_sock,(struct sockaddr *)&server,sizeof(server) ) < 0) {
      perror("Cant bin socket: ");
      exit(1);
   }
   printf("Binded succesfully\n\n\n\n");

    size = sizeof(server);
    printf("Looking for clients... \n\n\n");

    listen(client_sock,1);


    while (server_sock = accept(client_sock,(struct sockaddr *)&client,&size)) {

         client_addr = inet_ntoa(client.sin_addr);// client IP
         client_port = ntohs(client.sin_port); // client Port


           strcpy(buffer,"Server Connected...\n\n\n");

         if ( send (server_sock,buffer,strlen(buffer),0)  < 0) {
           perror("Send failed: ");
           exit(1);

         }

        printf("Client with IP address %s Connected  from port %d \n\n",client_addr,client_port);
        printf("Enter # to end the connection \n\n");


  /*     while (exit_loop) {
           // printf("wtfffffffffffffffff\n\n");



        while ( *buff != '#' ) {
          printf("Enter Message: ");
          scanf("%s",buff);
         // printf("0xfffr \n\n %s \n\n",buff);
          if ( (send_size =    send(server_sock,buff,strlen(buff),0)) < 0) {
               perror("Cant send mssg: ");
               exit(1);
          }
       // printf("Send size is:   %d",send_size);
        if (*buff == '#') {
            exit_loop = false;

          }
       }


       }
*/
        // Receive messages from client
        memset(buffer,0,buff_size);

        while ((read_size = recv(server_sock,buffer,1024,0)) > 0) {
             printf("Client: ");
             printf("%s\n\n",buffer);
              write(server_sock,buffer,strlen(buffer));
            if (*buffer == '#') {
                break;
              }

             memset(buffer,0,buff_size);
             //printf("say something: \n\n");

             //scanf("%s",msg);
             //printf("tqva - %s \n",msg);
             //send(server_sock,msg,strlen(msg),0);
            //send(server_sock,msg,strlen(msg),0);
        }



    }

    if (server_sock  <  0) {
      perror("Cant Accept Connections!");
      exit(1);
    }



  return 0;
}
