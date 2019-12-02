//server program

//include libraries
#include "string.h"
#include "server.h"
#include <unistd.h>
#include <sys/types.h>
#include "stdio.h"
#include <stdlib.h>
#include "netdb.h"
#include "netinet/in.h"

//the authorisation function
int authorised( char *user, char *password){

    FILE *fp = fopen("login.txt", "r");
    char buff[50];
    
    while( fgets(  buff, sizeof(buff), fp) != NULL ){
        char *user1 = strtok(buff, ":");
        char *pass1 = strtok(NULL, "\n");
        
        if( strcmp( user, user1) == 0 ){
            if( strcmp(password, pass1)==0)
               return 0; //matched
            else 
               return 1; //wrong password
        }
    }
    return -1; //user not found
}
//functions required
/*
-the request structure-->must be universal
-the menu display option
-the user count
-the menu will consist of -Buying Options
                          -Selling Opions
                          -View Orders
                          -Buy 
                          -Sell
*/

//main function
int main(int argc, char const *argv[]){
//extracting the input values from the command line arguments
char PORT[10], server_ip[16];

if(argc<3){
    printf("\nInsufficient arguments!\n");
    exit(1);
}
else{
    strcpy(PORT,argv[2]);
    strcpy(server_ip,argv[1]);
}

//socket structure declaration and initializing it to null
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
else{
    printf("\nSocket Created Successfully!\n");
}

//Binding the socket 
int bind_value=bind(socket_server,(struct sockaddr*)&server_add,sizeof(server_add));

if(bind_value<0){
    perror("\n Error in Socket Binding!\n");
    exit(1);
}
else{
    printf("\nSocket Binded Successfully!\n");
}

//Listening for incoming requests
listen(socket_server,5);

//accepting the incoming request
int client_socket=accept(socket_server,NULL,NULL);


if(client_socket<0){
    perror("\n Error in accepting connection!\n");
    exit(1);
}
else{
    printf("\nConnection Accepted Successfully!\n");
    //do the needfull
}

//Close the socket
close(socket_server);
printf("\nclosed the socket.\n");
    return 0;
}