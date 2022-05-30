#include <sys/types.h> 
#include <sys/socket.h>

#include <string.h>
#include <arpa/inet.h> 
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#include <stdint.h>
#include <inttypes.h>

#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

# define port 9003
int main(){
    // include timer for receiving data
    // include server host
    // creating the socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock <0){
        printf("failed opening socket");
        return -1;
    }
    // creating a port and address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // binding the socket with the created port and address
    int b = bind(sock,(struct sockaddr *) &server_address,sizeof(server_address));
    if(b <0){
        printf("failed to bind the socket to the address");
        return -1;
    }
    // letting the socket listen to 5 connections
    int l = listen(sock,5);
    if(l < 0){
        printf("failed to listen");
        return -1;
    }
    // socket accept connection
    int sender_socket = accept(sock, NULL,NULL);
    if(sender_socket < 0){
        printf("failed to accept");
        return -1;
    }
    FILE *writeToFile;
    writeToFile = fopen("getmytext.txt", "wb");
    int true = 1;
    char buffer[1024];
    int len;
    struct timeval currentTime, lastTime;
		// set timer
		gettimeofday(&currentTime,NULL);
		for(int fileCounter=0; fileCounter < 5; fileCounter++){
			true = 1;
		    while(true == 1){
	
			len = recv(sender_socket, &buffer, sizeof(buffer),0);
			if(buffer[0] == EOF || len == 0){
			    true = 0;
			}
			fwrite(buffer, 1,len, writeToFile);
		    }
		    fclose(writeToFile);
		    writeToFile = fopen("getmytext.txt", "wb");
		// ending while loop

		}
		// set timer
	    gettimeofday(&lastTime,NULL);
	    double dt = (double)(lastTime.tv_sec - currentTime.tv_sec);
		dt += (double)(lastTime.tv_usec - currentTime.tv_usec)/1000000;
	    double dt_avg=dt/5;
	    printf("Operation completed for 5 files, time took : %f\n", dt);
	    printf("average time for 5 files : %f\n", dt_avg);
    fclose(writeToFile);
    close(sender_socket);


}
