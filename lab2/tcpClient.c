//TCP CLIENT PROGRAM
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 9001

int main()
{
	int clientSocket,con_status;
	printf("--Type 'exit' to disconnect from server--\n");

	//creating socket
	clientSocket = socket(AF_INET,SOCK_STREAM,0);
	if(clientSocket<0)
	{
		printf("Error cannot create socket!\n");
		exit(1);
	}
	printf("Socket is created \n");

	//creating server address
	struct sockaddr_in server_addr;
	
	memset(&server_addr,'\0',sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY; // specify the address of serv

	con_status = connect(clientSocket,(struct sockaddr *)&server_addr, sizeof(server_addr));
	if(con_status<0)
	{
		printf("Connection unsuccessful!\n");
		exit(1);
	}
	printf("Connected to the Server\n");

	char buffer[256];
	//infinite loop until the client disconnects with the server	
	for(;;)
	{
		printf("Client: ");
		fgets(&buffer[0],256, stdin); 
		send(clientSocket,buffer,sizeof(buffer),0);

		if(strcmp(buffer,"exit\n")==0)
		{
			close(clientSocket);
			printf("Disconnected from the server\n");
			exit(0);
		}

		if(recv(clientSocket,buffer,256,0))
			printf("Response from Server : %s\n",buffer );
		else
			printf("Error in getting response\n");
	}
			return 0;
}