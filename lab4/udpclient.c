// Client program UDP Echo
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 


int main() { 
	
    const int PORTNO=9999;

    struct sockaddr_in servaddr ; 
    memset(&servaddr,0,sizeof(servaddr));   //initialise structure items with 0
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	char *datatosend;
    char buffer[2048];

    printf("\nCLIENT SIDE\n");
    if (sockfd ==-1) { 
		perror("\nFailed to create Socket"); 
		exit(EXIT_FAILURE); 
	} 
	// servadd information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORTNO); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len; 
	
    printf("\nEnter Data to Send :");
    scanf("%[^\n]s",datatosend);
    len = sendto(sockfd, datatosend, strlen(datatosend),0,
     (struct sockaddr *) &servaddr,sizeof(servaddr)); 
	
    if(len==-1)
    {
        perror("\nFailed to send");
    }	
    n = recvfrom(sockfd, buffer, 2048, MSG_WAITALL, (struct sockaddr *) &servaddr,&len);

    if(n==-1)
    {
        perror("\nFailed to receive from server");
    }             
	buffer[n] = '\0'; 
	printf("\nResponse from Server : %s\n", buffer); 

	close(sockfd); 
	return 0; 
} 
