#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
void itoa(int num,char strg[]){
 sprintf(strg,"%d",num);
}
int main(){
int start=1,current=1,end=4,old;
int sockfd,newsockfd;
struct sockaddr_in server,client;
socklen_t len;
char buffer[100];

sockfd=socket(AF_INET,SOCK_STREAM,0);
server.sin_family=AF_INET;
server.sin_port=htons(5000);
server.sin_addr.s_addr=INADDR_ANY;

bind(sockfd,(struct sockaddr*)&server,sizeof(server));
listen(sockfd,1);
len=sizeof(client);
newsockfd=accept(sockfd,(struct sockaddr*)&client,&len);

recv(newsockfd,buffer,100,0);

do{
  if(current!=end){
	itoa(current,buffer);
	send(newsockfd,buffer,100,0);
	printf("Packet %d\n",current);
	current++;
  }
  recv(newsockfd,buffer,100,0);
 if(buffer[0]=='R'){
	printf("Retransmitting\n");
	int resend=atoi(&buffer[1]);
	itoa(resend,buffer);
	send(newsockfd,buffer,100,0);
        current=resend;
	current++;
  }
 else if(buffer[0]=='A'){
	old=start;
	start=atoi(&buffer[1])+1;
	end+=(old-start);
	printf("Ack recieved\n");
 }
}while(current!=10);
close(sockfd);
close(newsockfd);
}
