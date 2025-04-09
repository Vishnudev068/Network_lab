#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 5000
#define BUFF_SIZE 100
int main(){

    int sockfd,newsockfd;
    struct sockaddr_in server, client;
    char buffer[BUFF_SIZE];
    pid_t child;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    listen(sockfd,5);

    while(1){
        socklen_t len=sizeof(client),
        newsockfd=accept(sockfd,(struct sockaddr*)&client,&len);
        if((child=fork()==0)){
            close(sockfd);
          while(1){
            memset(buffer,0,BUFF_SIZE);
            int n=recv(newsockfd,buffer,BUFF_SIZE,0);
            if(n<=0) break;

            printf("Client:%s\n",buffer);
            send(newsockfd,buffer,n,0);
          }
          close(newsockfd);
          exit(0);
        }
        close(newsockfd);
    }
    return 0;
}
