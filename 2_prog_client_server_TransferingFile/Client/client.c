//this is the client program which will transmit a single file to the server.

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

//socket creation
int socket_client=socket(AF_INET,SOCK_STREAM,0);

//checking if the socket was created successfully
if (socket_client<0){
    perror("\n Error in creating/opening the Socket!\n");
    exit(1);
}
else{
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
else{
    printf("\n Connected to the server Successfully!\n");
}

//file part
//opening the file
FILE* input_file=fopen("abc.txt","r");

if (input_file==NULL){
    printf("\nError opening the file!\n");
}
else{
    char file_content[50];
//loop
while(!feof(input_file)){

//reading the content of the file line by line
fscanf(input_file,"%[^\n]s",file_content);

//sending the file content to the server
send(socket_client,file_content,strlen(file_content)+1,0);
printf("\nSent String:%s\n",file_content);

//flushing the buffer
file_content[0]='\0';
}
send(socket_client,"-1",sizeof("-1"),0);

//close the file
fclose(input_file);}
//Close the socket
close(socket_client);
printf("\nclosing the socket.\n");
    return 0;
}