//this is the server program that will receive string from the client and reverse it and send it back
//Done by CSB17017
//import statements
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
//function to reverse a given string
void reverse_string(char *string){
    int temp=strlen(string);
    char *b,*e,c;
    b=string;
    e=string+temp-1;
    int i=0;
    while(i<temp/2){
        c=*b;
        *b=*e;
        *e=c;
        b++;
        e--;
        i++;    
    }
}

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
    else
        printf("\nSocket Created Successfully!\n");

    //Binding the socket 
    int bind_value=bind(socket_server,(struct sockaddr*)&server_add,sizeof(server_add));
    if(bind_value<0){
        perror("\n Error in Socket Binding!\n");
        exit(1);
    }
    else
        printf("\nSocket Binded Successfully!\n");

    //Listening for incoming requests
    listen(socket_server,5);
    while(1){
        //accepting the incoming request
        int client_socket=accept(socket_server,NULL,NULL);
        if(client_socket<0){
            perror("\n Error in accepting connection!\n");
            exit(1);
        }
        else{
            printf("\nConnection Accepted Successfully!\n");
            int pid=fork();
            if(pid<0){
                printf("\nThe fork failed!\n");
                exit(1);
            }
            else if(pid==0){ 
                close(socket_server);
                //data exchange---in this program it will only receive 1 line of message
                char client_string[600];
                bzero(client_string,sizeof(client_string));
                recv(client_socket,client_string,sizeof(client_string),0);
                reverse_string(client_string);
                puts(client_string);
                send(client_socket,client_string,strlen(client_string),0);
                printf("\nServer job completed!\n");
                exit(0);
            }
           close(client_socket);
        }
    }
    close(socket_server);//Close the socket
    printf("\nclosing the socket.\n");
    return 0;
}