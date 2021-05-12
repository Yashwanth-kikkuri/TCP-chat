#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
int main(int argc, char* argv[])
{
   int sockfd, newsockfd, portno, n;
   char buffer[500];
 
   struct sockaddr_in serv_addr, cli_addr;
   socklen_t clilen;
 
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   bzero((char*) &serv_addr, sizeof(serv_addr));
 
   portno = atoi(argv[1]);
 
   serv_addr.sin_family=AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
 
   if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))<0)printf("error");
 
   listen(sockfd, 5);
 
   clilen =  sizeof(cli_addr);
 
   newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
 
   while(1){
       bzero(buffer, 500);
       read(newsockfd, buffer, 500);
 
       printf("Client : %s\n", buffer);
 
       bzero(buffer, 500);
       fgets(buffer, 500, stdin);
 
       write(newsockfd, buffer, strlen(buffer));
 
       if(strncmp("bye", buffer, 3)==0)break;
   }
 
   close(newsockfd);
   close(sockfd);
}
