#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
    int i=0;
    char input[8];

    gets(input);
    puts(input);

    for(i=0;i<8;i++){
        printf("\n Enter the %d th bit: %c",i+1,input[i]);
    }
}