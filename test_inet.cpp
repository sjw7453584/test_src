#include<stdlib.h>
#include<cstdio>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(int argc ,char ** argv)
{
    // int ip = ;                  //
    struct in_addr sin_addr;
    // sin_addr.s_addr= 3272612012 ;
    
    sin_addr.s_addr= atoi(argv[1]) ;
    char * ipstr = inet_ntoa(sin_addr);
    char * tmp =ipstr;
    printf("%s\n",tmp);
}
