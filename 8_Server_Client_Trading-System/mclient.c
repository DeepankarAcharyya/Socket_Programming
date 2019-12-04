#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

void display_menu(){
    printf("\n**********************MENU*************************\n");
    printf("\nEnter 1 for Buying\n");
    printf("\nEnter 2 for Selling\n");
    printf("\nEnter 3 for Viewing Order Stats\n");
    printf("\nEnter 4 for Viewing the available stocks to Buy\n");
    printf("\n***************************************************\n");
}
int main(){
    //connecting to the server part

    //login part
    int trader_id;
    printf("Enter the trade ID:");
    scanf("%d",&trader_id);

    //displaying the menu

    //taking input

    //if request based-> filling up the request structure 
    
    //sending the request structure to the server
    
    return 0;
}