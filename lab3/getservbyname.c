#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/in.h>
#include<netdb.h>

int main()
{
    struct servent *servp;  //structure pointer to store getservbyname()
    // Some services name to check 
    char *ser_name[5] = {"http","smtp","ftp","echo","telnet"};
    // Possible protocols for a service
    char *ser_proto[2]={"tcp","udp"};
    
    int i=0;
    //Applying getservbyname on the list of services
    printf("FOR TCP PROTOCOL SERVICES :-\n");
    for(i=0;i<5;i++)
    {
        //ser_proto[0] for tcp ser_proto[1] for udp
        servp = getservbyname(ser_name[i],ser_proto[0]); 
        // if the return value is not NULL
        if(servp!=NULL)
        {
            //vars to store values
            char *name = servp->s_name, *proto = servp->s_proto;
            // port number of a service
            int port= ntohs(servp->s_port);
            // char var to store value of alias
            char **alias = servp->s_aliases;
            printf("Service Name : %s \nService Port Number : %d",name,port);
            printf("\nProtocol : %s \nAliases : %s",proto,*alias);
        }
        else{
            perror("getservbyname");
        }
        printf("\n\n");
    }
     printf("FOR UDP PROTOCOL SERVICES :-\n");
    for(i=0;i<5;i++)
    {
        servp = getservbyname(ser_name[i],ser_proto[1]); 
        if(servp!=NULL)
        {
            //vars to store values
            char *name = servp->s_name, *proto = servp->s_proto;
            // port number of a service
            int port= ntohs(servp->s_port);
            // char var to store value of alias
            char **alias = servp->s_aliases;
            printf("Service Name : %s \nService Port Number : %d",name,port);
            printf("\nProtocol : %s \nAliases : %s",proto,*alias);
        }
        else{
            continue;
        }
        printf("\n\n");
    }    

    return 0;

}