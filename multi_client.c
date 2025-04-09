#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 5000
#define BUFF_SIZE 100
int main(int argc,char *argv[]){


    int sockfd;
    struct sockaddr_in server;
    char buffer[BUFF_SIZE];
    
    
    if(argc<2){
        printf("Usage %s ",argv[0]);
    }

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=inet_addr(argv[1]);

    connect(sockfd,(struct sockaddr*)&server,sizeof(server));
    printf("Connected to port %s %d\n",argv[1],PORT);

    while(1){
        printf("You: ");
        fgets(buffer,BUFF_SIZE,stdin);
        //buffer[strcspn(buffer,"\n")]='\0';
        if(strncmp(buffer,"exit",4)==0){
               break;
        }
           
        
        send(sockfd,buffer,strlen(buffer),0);
        memset(buffer,0,BUFF_SIZE);
        recv(sockfd,buffer,BUFF_SIZE,0);

        printf("Server: %s",buffer);
    }
    close(sockfd);

    return 0;



}
