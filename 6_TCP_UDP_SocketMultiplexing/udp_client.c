//udp client file
//import statements
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char const *argv[]){
//extracting the inputs from the command-line argument
char string[600], PORT[10], server_ip[16];

if(argc<4){
    printf("\nInsufficient arguments!\n");
    exit(1);
}
else{
    strcpy(string,argv[3]);
    strcpy(PORT,argv[2]);
    strcpy(server_ip,argv[1]);
}

//socket creation
int socket_client=socket(AF_INET,SOCK_DGRAM,0);
//checking if the socket was created successfully
if (socket_client<0){
    perror("\n Error in creating/opening the Socket!\n");
    exit(1);
}
else
    printf("\nSocket Created successfully!\n");

//address structures for storing the server address to connect to
struct sockaddr_in server_add;
bzero((char *)&server_add,sizeof(server_add));
server_add.sin_family=AF_INET; //type of family
server_add.sin_port=htons(atoi(PORT));//port we are gonna connect to
server_add.sin_addr.s_addr=inet_addr(server_ip); //server's ip add

//sendto()
//recvfrom()
//close()

//sending the string to the server
int n, len; 
sendto(socket_client,&string, strlen(string),MSG_CONFIRM, (const struct sockaddr *) &server_add,sizeof(server_add)); 
printf("\nSent String:%s\n",string);
//receive the string from the server
bzero(string,sizeof(string));
recvfrom(socket_client,string,sizeof(string),MSG_WAITALL, (struct sockaddr *) &server_add,&len);    
//printing out the received string
printf("\nReversed String:%s\n",string);

//Close the socket
close(socket_client);
printf("\nclosing the socket.\n");
return 0;
}