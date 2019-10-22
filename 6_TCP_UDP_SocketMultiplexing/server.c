//server file
//import statements
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

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

    //fd_set to store the file descriptors
    fd_set rset;
    FD_ZERO(&rset);

    //socket structure declaration and initializing it to null
    struct  sockaddr_in server_add,client_add;
    bzero((char *)&server_add,sizeof(server_add));
    server_add.sin_family=AF_INET;
    server_add.sin_port=htons(atoi(PORT));
    server_add.sin_addr.s_addr=inet_addr(server_ip);

    //Socket Creation
    //for tcp
    int socket_server_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_server_tcp<0){
        perror("\n Error in creating/opening the Socket!--TCP\n");
        exit(1);
    }
    else
        printf("\nTCP Socket Created Successfully!\n");
    //for udp
    int socket_server_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_server_udp<0){
        perror("\n Error in creating/opening the Socket!--UDP\n");
        exit(1);
    }
    else
        printf("\nUDP Socket Created Successfully!\n");

    //Binding the sockets
    //for tcp
    int bind_value_tcp=bind(socket_server_tcp,(struct sockaddr*)&server_add,sizeof(server_add));
    if(bind_value_tcp<0){
        perror("\n Error in Socket Binding!--TCP\n");
        exit(1);
    }
    else
        printf("\nTCP Socket Binded Successfully!\n");
    //Listening for incoming requests
    listen(socket_server_tcp,5);
    //for udp
    int bind_value_udp=bind(socket_server_udp,(struct sockaddr*)&server_add,sizeof(server_add));
    if(bind_value_udp<0){
        perror("\n Error in Socket Binding!--UDP\n");
        exit(1);
    }
    else
        printf("\nUDP Socket Binded Successfully!\n");
    
    char client_string[600];
        
    //selecting the socket with maximum number of descriptors ready
    int max=(socket_server_udp>socket_server_tcp)?socket_server_udp:socket_server_tcp;
    max=max+1;

    int ready; 
    
    while(1){
        // set tcp and udp socket fds in readset 
        FD_SET(socket_server_tcp, &rset); 
        FD_SET(socket_server_udp, &rset);

        ready= select(max, &rset, NULL, NULL, NULL); 
        //if tcp socket is selected
        if (FD_ISSET(socket_server_tcp, &rset)) { 
            //accept the client connection
            int client_socket=accept(socket_server_tcp,NULL,NULL);
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
                    close(socket_server_tcp);
                    //data exchange
                    bzero(client_string,sizeof(client_string));
                    recv(client_socket,client_string,sizeof(client_string),0);
                    reverse_string(client_string);
                    //puts(client_string);
                    send(client_socket,client_string,strlen(client_string),0);
                    printf("\nTCP Server job completed!\n");
                    exit(0);
                }
            close(client_socket);
            }
        } 
    // if udp socket is selected 
        if (FD_ISSET(socket_server_udp, &rset)) { 
                bzero(client_string,sizeof(client_string));
            int len, n; 
            n = recvfrom(socket_server_udp, (char *)client_string,600, MSG_WAITALL, ( struct sockaddr *) &client_add,&len); 
            if(n>0){
        
            printf("\nFrom child\nReceived String=%s\n",client_string);
            reverse_string(client_string);
            puts(client_string);
            printf("\n%d\n",sendto(socket_server_udp,client_string, strlen(client_string),MSG_CONFIRM, (const struct sockaddr *) &client_add,len)); 
            printf("\nUDP Server job completed!\n");

    }
    memset(&client_add, 0, sizeof(client_add)); 
    }}
    return 0;
}