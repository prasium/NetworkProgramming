#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>

#define PORT 6500

void str_echo(int s)
{

}
int main()
{
 int ls;
 struct sockaddr_in cli;
 puts("Client");
//creating socket/
 //creating socket
	ls = socket(AF_INET,SOCK_STREAM,0);
	if(ls<0)
	{
		printf("Error cannot create socket!\n");
		exit(1);
	}
	printf("Socket is created \n");

	
//socket address structure/
 cli.sin_family=AF_INET;
 cli.sin_addr.s_addr=inet_addr("127.0.0.1");
 cli.sin_port=htons(PORT);
//connecting to server/
 connect(ls,(struct sockaddr*)&cli,sizeof(cli));
 puts("Connected to the Server.");
 char buf[50],buf1[50];
 puts("Text : ");
 fgets(buf,50,stdin);
 send(ls,buf,50,0); //sending data to server
//receiving data from server
 recv(ls,buf1,50,0);
 puts("Response from Server : ");
 fputs(buf1,stdout);
 
 close(ls);
 return 0;
}