#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
 
int main(int argc, char* argv[])
{
   int sockfd, portno, n;
   char buffer[500];
 
   struct sockaddr_in serv_addr;
   struct hostent* server;
 
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   bzero((char*) &serv_addr, sizeof(serv_addr));
 
   portno = atoi(argv[2]);
 
   server = gethostbyname(argv[1]);
 
   serv_addr.sin_family=AF_INET;
   bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
 
   connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
 
   while(1){
       bzero(buffer, 500);
       fgets(buffer, 500, stdin);
 
       write(sockfd, buffer, strlen(buffer));
 
       bzero(buffer, 500);
 
       read(sockfd, buffer, 500);
 
       printf("Server : %s\n", buffer);       
 
       if(strncmp("bye", buffer, 3)==0)break;
   }
 
   close(sockfd);
}
