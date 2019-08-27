    
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
        }
    }
    close(socket_server);//Close the socket
    printf("\nclosing the socket.\n");
    return 0;
}