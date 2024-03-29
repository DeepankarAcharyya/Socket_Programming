#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

//function for producing the parity bit
int parity(char input[],int pos){
    //odd parity scheme is to be followed
    int i,count=0;
    for(i=0;i<strlen(input);i++){
        if(input[i]=='1')
            count++;
    }
    if(count%2==0)
        return 1;
    else return 0;
}

//function for generating pseudo random number

int main(int argc,char *argv[]){
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
//taking input(8-bit) from the user
    int i=0;
    char input[8];
    gets(input);
    puts(input);
//producing the hamming code
char hc[12];
int pos,parity_bit,c1=0;
for(i=0;i<12;i++){
    if (((i&(i-1))==0) || i==0){
        pos=math.pow(2,i);
        parity_bit=parity(input,pos);
        hc[pos]=(char)parity_bit;
        c1=pos;
    }
    

}
//taking input of the error rate
float error;
printf("\nEnter the error rate:");
scanf("%.2f",&error);
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
    //accepting the incoming request
    int client_socket=accept(socket_server,NULL,NULL);
    if(client_socket<0){
            perror("\n Error in accepting connection!\n");
            exit(1);
        }
    else{
            char client_string[600];
                bzero(client_string,sizeof(client_string));
                recv(client_socket,client_string,sizeof(client_string),0);
                reverse_string(client_string);
                puts(client_string);
                send(client_socket,client_string,strlen(client_string),0);
                printf("\nServer job completed!\n");
                close(client_socket);
        }
    close(socket_server);//Close the socket
    printf("\nclosing the socket.\n");
    return 0;
}