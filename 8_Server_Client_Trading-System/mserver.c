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
int main(int argc,char** argv){


    return 0;
}