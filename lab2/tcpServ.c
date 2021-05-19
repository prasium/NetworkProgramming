//TCP SERVER PROGRAM
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 9001

int main()
{
	pid_t childPid;

	char buffer[256];
	int servSocket,con_status;
	//creating socket
	servSocket = socket(AF_INET,SOCK_STREAM,0);
	if(servSocket<0)
	{
		printf("Error is socket creation\n");
		exit(1);
	}
	printf("Server socket created \n");

	//creating structure for sock address
	struct sockaddr_in server_addr;
	socklen_t address_size;

	memset(&server_addr,'\0',sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY; // specify the address of serv


	//bind function to bind IP address to specific port
	con_status= bind(servSocket,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(con_status<0)
	{
		printf("Error in binding \n");
		exit(1);
	}
	printf("Binded to port %d \n",PORT);

	if(listen(servSocket,5)==0){
		printf("Listening ...\n");
	}
	else{
		printf("Error in binding\n");
	}


	int newSocket; // socket that we have to accept from client 
	struct sockaddr_in new_addr;
	//infinite loop
	while(1)
	{
		newSocket = accept(servSocket,(struct sockaddr*)&new_addr, &address_size);
		if(newSocket<0)
			exit(1);

		printf("Connection accpeted from %s:%d\n",inet_ntoa(new_addr.sin_addr),ntohs(new_addr.sin_port));
		
		if((childPid=fork())==0){
			close(servSocket);

			while(1){
				recv(newSocket,buffer,256,0); // receive from client
				if(strcmp(buffer,"exit")==0)
				{
					printf("Disconnected from %s:%d\n",inet_ntoa(new_addr.sin_addr),ntohs(new_addr.sin_port));
					break;
				}
				else{
					printf("Client[%d]: %s\n",ntohs(new_addr.sin_port),buffer);
					send(newSocket,buffer,sizeof(buffer),0);
					
				}
			}
		}	
	}

	close(newSocket);

	return 0;
}