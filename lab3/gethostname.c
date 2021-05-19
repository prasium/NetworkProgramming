#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>

int main()
{
    char hostnamebuff[128];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;

    //Get hostname
    hostname= gethostname(hostnamebuff, sizeof(hostnamebuff));

    //check if host name exists
    if (hostname == -1) 
    { 
        perror("gethostname"); 
        exit(1); 
    }

    host_entry = gethostbyname(hostnamebuff);
    // Check information about the host
    if (host_entry == NULL) 
    { 
        perror("gethostbyname"); 
        exit(1); 
    } 

    //Convert IP Address to ASCII format
    IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));

    printf("Host Name : %s",hostnamebuff);
    printf("\nHost IP Address : %s\n",IPbuffer);

    return 0;

}