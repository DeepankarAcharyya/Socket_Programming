//this is the server program that will receive a single message from the client

//import statements
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<string.h>

#define PORT  8080

int main(int argc, char const *argv[]){

//socket structure declaration and initializing it to null
struct  sockaddr_in server_add;
server_add.sin_family=AF_INET;
server_add.sin_port=htons(PORT);
server_add.sin_addr.s_addr=INADDR_ANY;


//Socket Creation
int socket_server = socket(AF_INET, SOCK_STREAM, 0);

if(socket_server<0){
    perror("\n Error in creating/opening the Socket!\n");
    exit(1);
}
else
{
    printf("\nSocket Created Successfully!\n");
}

//Binding the socket 
int bind_value=bind(socket_server,(struct sockaddr*)&server_add,sizeof(server_add));


if(bind_value<0){
    perror("\n Error in Socket Binding!\n");
    exit(1);
}
else
{
    printf("\nSocket Binded Successfully!\n");
}

//Listening for incoming requests
listen(socket_server,5);

//accepting the incoming request
int client_socket=accept(socket_server,NULL,NULL);


if(socket_server<0){
    perror("\n Error in accepting connection!\n");
    exit(1);
}
else
{
    printf("\nConnection Accepted Successfully!\n");
    //data exchange---in this program it will only receive 1 line of message
    char client_response[256];

    printf("\nClient message was received successfully!\n");
    int i=1;
    while(1){
        //receiving the message
        recv(client_socket,&client_response,sizeof(client_response),0);
        //checking if it is the end of the transmission
        if (strcmp(client_response,"-1")==0){
            break;
        }
        //Display the message
        printf("%s",client_response);
        //flushing the buffer
        client_response[0]='\0';
    }
}

//Close the socket
close(socket_server);

printf("\nclosing the socket.\n");
    return 0;
}