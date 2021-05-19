// Client program UDP Echo using Connect
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 


#define PORTNO 9090
#define MAX 2048

int main() { 
	
    
    struct sockaddr_in servaddr ; 
    memset(&servaddr,0,sizeof(servaddr));   //initialise structure items with 0
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	char datatosend[MAX];
    char buffer[MAX];

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
	int size= sizeof(servaddr);
    if(connect(sockfd,(struct sockaddr *)&servaddr,size)<0)
    {
        perror("Connect Error");
        exit(EXIT_FAILURE);
    }

    
    printf("\nEnter Data to Send :");
    scanf("%[^\n]s",datatosend);

    len = send(sockfd, datatosend, strlen(datatosend),0); 
	
    if(len==-1)
    {
        perror("\nFailed to send");
    }	

	close(sockfd); 
	return 0; 
} 
