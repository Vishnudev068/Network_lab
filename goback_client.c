#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
int current;
int sockfd,newsockfd;
struct sockaddr_in server;
socklen_t len;
char buffer[100];

sockfd=socket(AF_INET,SOCK_STREAM,0);
server.sin_family=AF_INET;
server.sin_port=htons(5000);
server.sin_addr.s_addr=INADDR_ANY;


len=sizeof(server);
connect(sockfd,(struct sockaddr*)&server,sizeof(server));
int first=1;
send(sockfd,"REQUEST",100,0);

do{
	recv(sockfd,buffer,100,0);
	current=atoi(buffer);
	printf("Packet recived %d\n",current);
	if(current==3 && first){
	 	printf("Requesting packet %d\n",current);
		send(sockfd,"R3",100,0);
		first=0;
         }
	else{
		memset(buffer,'\0',100);
		sprintf(buffer,"A%d",current);
		send(sockfd,buffer,100,0);
		printf("Ack sended\n");
	}
}while(current!=9);
close(sockfd);
}
