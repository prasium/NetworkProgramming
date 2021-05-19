// UDP Client server to show header info
#include<netinet/in.h>
#include<errno.h>
#include<netdb.h>
#include<stdio.h> 
#include<stdlib.h>    
#include<string.h>    
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<netinet/if_ether.h>  //For ETH_P_ALL
#include<net/ethernet.h>  //For ether_header
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
 
 
void ProcessPacket(unsigned char* , int);
void print_ip_header(unsigned char* , int);
void print_udp_packet(unsigned char * , int );
void PrintData (unsigned char* , int);
 
struct sockaddr_in source,dest;
int i,j; 
 
int main()
{
    int saddr_size , data_size;
    struct sockaddr saddr;
         
    unsigned char *buffer = (unsigned char *) malloc(65536); //Its Big!
    printf("Server running...\n");
     
    int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
    setsockopt(sock_raw , SOL_SOCKET , SO_BINDTODEVICE , "eth0" , strlen("eth0")+ 1 );
     
    if(sock_raw < 0)
    {
        //Print the error with proper message
        perror("Socket Error");
        return 1;
    }

        saddr_size = sizeof saddr;
        //Receive a packet
        data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , (socklen_t*)&saddr_size);
        if(data_size <0 )
        {
            printf("Recvfrom error , failed to get packets\n");
            return 1;
        }
        //Now process the packet
        ProcessPacket(buffer , data_size);
    close(sock_raw);
    return 0;
}
 
void ProcessPacket(unsigned char* buffer, int size)
{
    //Get the IP Header part of this packet , excluding the ethernet header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
     //UDP Protocol
            print_udp_packet(buffer , size);

 }

void print_udp_packet(unsigned char *Buffer , int Size)
{
     
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
    iphdrlen = iph->ihl*4;
     
    struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
     
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
     
    printf( "\nReceived! \nUDP Packet\n");
     
	print_ip_header(Buffer,Size);         // To print Ip header  
     
    printf( "\nUDP Header\n");
    printf( "\tSource Port      : %d\n" , ntohs(udph->source));
    printf( "\tDestination Port : %d\n" , ntohs(udph->dest));
    printf( "\tUDP Length       : %d\n" , ntohs(udph->len));
    printf( "\tUDP Checksum     : %d\n" , ntohs(udph->check));
     
    printf( "\nIP Header\n");
    PrintData(Buffer , iphdrlen);
         
    printf( "UDP Header\n");
    PrintData(Buffer+iphdrlen , sizeof udph);
         
    printf("\nPayload data\n");    
     
    //Move the pointer ahead and reduce the size of string
    PrintData(Buffer + header_size , Size - header_size);
     
}

void print_ethernet_header(unsigned char* Buffer, int Size)
{
    struct ethhdr *eth = (struct ethhdr *)Buffer;
     
    printf( "\nEthernet Header\n");
    printf( "\tDestination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
    printf( "\tSource Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
    printf( "\tProtocol            : %u \n",(unsigned short)eth->h_proto);
}
 
void print_ip_header(unsigned char* Buffer, int Size)
{
    
   	print_ethernet_header(Buffer , Size); // To print ethernet header 
    
    unsigned short iphdrlen;
         
    struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    iphdrlen =iph->ihl*4;
     
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
     
    printf("\n");
    printf("IP Header\n");
    printf("\tIP Header Length  : %d Double Word | %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
	printf("\tIP Version        : %d\n",(unsigned int)iph->version);
	printf("\tSource IP        : %s\n",inet_ntoa(source.sin_addr));
    printf("\tDestination IP   : %s\n",inet_ntoa(dest.sin_addr));
    printf("\tType Of Service   : %d\n",(unsigned int)iph->tos);
    printf("\tIP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    printf("\tIdentification    : %d\n",ntohs(iph->id));
    printf("\tTTL      : %d\n",(unsigned int)iph->ttl);
    printf("\tProtocol : %d\n",(unsigned int)iph->protocol);
    printf("\tChecksum : %d\n",ntohs(iph->check));
}
 
void PrintData (unsigned char* data , int Size)
{
    int i , j;
    for(i=0 ; i < Size ; i++)
    {
        if( i!=0 && i%16==0)   //if one line of hex printing is complete...
        {
            printf( "         ");
            for(j=i-16 ; j<i ; j++)
            {
                if(data[j]>=32 && data[j]<=128)
                    printf( "%c",(unsigned char)data[j]); //if its a number or alphabet
                 
                else printf( "."); //otherwise print a dot
            }
            printf( "\n");
        } 
         
        if(i%16==0) printf( "   ");
            printf( " %02X",(unsigned int)data[i]);
                 
        if( i==Size-1)  //print the last spaces
        {
            for(j=0;j<15-i%16;j++) 
            {
              printf( "   "); //extra spaces
            }
             
            printf( "         ");
             
            for(j=i-i%16 ; j<=i ; j++)
            {
                if(data[j]>=32 && data[j]<=128) 
                {
                  printf( "%c",(unsigned char)data[j]);
                }
                else
                {
                  printf( ".");
                }
            }            
            printf(  "\n" );
        }
    }
}