//this is the client program which will transmit a single message to the server.

//import statements
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#define PORT  8080

int main(int argc, char const *argv[]){

//socket creation
int socket_client=socket(AF_INET,SOCK_STREAM,0);

//checking if the socket was created successfully
if (socket_client<0){
    perror("\n Error in creating/opening the Socket!\n");
    exit(1);
}
else
{
    printf("\nSocket Created successfully!\n");
}


//address structures for storing the server address to connect to
struct sockaddr_in server_add;

server_add.sin_family=AF_INET; //type of family
server_add.sin_port=htons(PORT);//port we are gonna connect to
server_add.sin_addr.s_addr=INADDR_ANY; //server's ip add

//connecting to the server
int connect_value=connect(socket_client,(struct sockaddr *) &server_add, sizeof(server_add));

//checking if the connection was done properly
if (connect_value<0){
    perror("\n Error in connecting to the Server!\n");
    exit(1);
}
else
{
    printf("\n Connected to the server Successfully!\n");
}

//data exchange-->this program only sends a single message
char client_message[]="This message is from the client.";

send(socket_client,client_message,sizeof(client_message),0);

//Close the socket
close(socket_client);
printf("\nclosing the socket.\n");
    return 0;
}