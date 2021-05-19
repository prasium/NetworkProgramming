// Server side iprogram UDP
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORTNO 9999
#define MAXLIM 2048

int main() { 
	
    struct sockaddr_in servaddr ;
    memset(&servaddr,0,sizeof(servaddr)); 
    int sockfd; 
	printf("SERVER IS UP AND RUNNING...");
	
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd==-1) { 
		perror("failed to create socket"); 
		exit(EXIT_FAILURE); 
	} 
	
    // server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_port = htons(PORTNO); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	
	// Bind the socket with the server address 
	int rc = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    if (rc==-1) 
	{ 
		perror("Failed to bind"); 
        close(sockfd);
		exit(EXIT_FAILURE); 
	} 
	// Socket address to store client address
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(clientaddr));
    int len=sizeof(clientaddr);

    while(1)
    {
    char buffer[MAXLIM]; 
	
    int n = recvfrom(sockfd, buffer, sizeof(buffer),0, (struct sockaddr *) &clientaddr, &len); 
     buffer[n]='\0';
	printf("\nReceived from Client (%s) : %s\n", inet_ntoa(clientaddr.sin_addr),buffer); 
	
    //Echo back the received message to client
    sendto(sockfd, buffer,sizeof(buffer),0, (struct sockaddr *) &clientaddr,sizeof(clientaddr)); 
    
    }
    
        
	return 0; 
} 
