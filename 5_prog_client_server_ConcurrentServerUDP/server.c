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
    struct  sockaddr_in server_add,client_add;
    
    //initializing the memory space with null values
    memset(&server_add, 0, sizeof(server_add)); 
    memset(&client_add, 0, sizeof(client_add)); 
    
    //filling up the server_add struct
    bzero((char *)&server_add,sizeof(server_add));
    server_add.sin_family=AF_INET;
    server_add.sin_port=htons(atoi(PORT));
    server_add.sin_addr.s_addr=inet_addr(server_ip);

    //Socket Creation
    int socket_server = socket(AF_INET, SOCK_DGRAM, 0);
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
    
    char client_string[600];
    while(1){
    bzero(client_string,sizeof(client_string));
    int len, n; 
    n = recvfrom(socket_server, (char *)client_string,600, MSG_WAITALL, ( struct sockaddr *) &client_add,&len); 
    if(n>0){
        int pid=fork();
        if(pid==0){
            printf("\nFrom child\nReceived String=%s\n",client_string);
            reverse_string(client_string);
            puts(client_string);
            printf("\n%d\n",sendto(socket_server,client_string, strlen(client_string),MSG_CONFIRM, (const struct sockaddr *) &client_add,len)); 
            printf("\nServer job completed!\n");
            exit(0);
        }
    }
    memset(&client_add, 0, sizeof(client_add)); 
    }
    printf("\nParent closing socket\n");
    close(socket_server);
return 0;
}