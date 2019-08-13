//this is the client program which will transmit a single file to the server.
//done by CSB17017
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
char file_name[10], PORT[10], server_ip[16];

if(argc<4){
    printf("\nInsufficient arguments!\n");
    exit(1);
}
else
{
    strcpy(file_name,argv[3]);
    strcpy(PORT,argv[2]);
    strcpy(server_ip,argv[1]);
}

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
bzero((char *)&server_add,sizeof(server_add));

server_add.sin_family=AF_INET; //type of family
server_add.sin_port=htons(atoi(PORT));//port we are gonna connect to
server_add.sin_addr.s_addr=inet_addr(server_ip); //server's ip add

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
FILE* input_file=fopen(file_name,"r");

if (input_file==NULL){
    printf("\nError opening the file!\n");
}
else{
    char file_content[600];

//loop
while(!feof(input_file)){
    //flushing the buffer
    bzero(file_content,sizeof(file_content));

    //reading the content of the file line by line
    fgets(file_content,550,input_file);
    printf("%s",file_content);

    //sending the file content to the server
    send(socket_client,file_content,strlen(file_content),0);
    }

send(socket_client,"$a1",sizeof("$a1"),0);
printf("\nFile transferred to the server successfully!\n");

//close the file
fclose(input_file);
}

//Close the socket
close(socket_client);
printf("\nclosing the socket.\n");
    return 0;
}