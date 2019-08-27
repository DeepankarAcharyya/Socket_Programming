//imports
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc, char const *argv[]){
    char PORT[10], server_ip[16];
    if(argc<3){
        printf("\nInsufficient arguments!\n");
        exit(1);
    }
    else{
        strcpy(PORT,argv[2]);
        strcpy(server_ip,argv[1]);
    }

    struct  sockaddr_in server_add;
    bzero((char *)&server_add,sizeof(server_add));
    server_add.sin_family=AF_INET;
    server_add.sin_port=htons(atoi(PORT));
    server_add.sin_addr.s_addr=inet_addr(server_ip);

    //Socket Creation
    int socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_server<0){
        perror("\n Error in creating/opening the Socket!\n");
        exit(1);
    }
    else
        printf("\nSocket Created Successfully!\n");

    
    return 0;
}