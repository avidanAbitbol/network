
#include <sys/types.h> 
#include <sys/socket.h>

#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <string.h>
#include <arpa/inet.h> 
#include <stdint.h>


#include <string.h>
#include <arpa/inet.h> 
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#include <inttypes.h>
#include <unistd.h>

#define port 9003

int main(int argc, char **argv){
    // include timer for sending files
    // include congestion control
    // include connect host 
    char *cc_name;
    char *filename;
    if(argc == 3){
     cc_name = argv[1];
     filename = argv[2];
    }
    else{
    return 0;
    }

    char buf[256];
    socklen_t len;

    int network_socket= socket(AF_INET,SOCK_STREAM,0);
    if(network_socket< 0) {
    printf("Error creating socket\n");
    }
    struct sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port=htons(port);

    int con = connect(network_socket, (struct sockaddr *) &saddr, sizeof(saddr));
    if(con < 0 ){
        printf("cannot connect");
        return -1;
    }
    // Congestion control : 
     	len=sizeof(buf);
	// change reno to cc_name
	strcpy(buf, cc_name);
	len = strlen(buf);
	if(setsockopt(network_socket, IPPROTO_TCP, TCP_CONGESTION, buf, len)!=0){
		perror("setsockopt");
		return -1;
	}
	len = sizeof(buf);
	if(getsockopt(network_socket, IPPROTO_TCP, TCP_CONGESTION, buf, &len)!=0){
		perror("getsockopt");
		return -1;
	}
	printf("New: %s\n",buf);
	// print current is cubic
    printf("Current: %s\n", buf);

    // sending the files
    
    // set the file
    FILE * file;
    
    file = fopen(filename, "rb");
    // create buffer to send data with
    char buffer[256]; 
    struct timeval currentTime, lastTime;
		gettimeofday(&currentTime,NULL);
		for(int fileCounter=0; fileCounter < 5; fileCounter ++){
		    file = fopen(filename, "rb");
		    while(fread(buffer, 1, sizeof(buffer), file) > 0){
			// send the buffer
			send(network_socket, buffer, sizeof(buffer), 0);
		    }
		    // send ack to verify one file was sent
		    buffer[0] = EOF;
		    buffer[1] = '\0';
		    send(network_socket, buffer, sizeof(buffer), 0);
		    fclose(file);
		    
		}
		gettimeofday(&lastTime,NULL);
	    double dt = (double)(lastTime.tv_sec - currentTime.tv_sec);
		dt += (double)(lastTime.tv_usec - currentTime.tv_usec)/1000000;
	    double dt_avg=dt/5;
	    printf("Operation done for 5 files, time took to excecute : %f\n", dt);
	       printf("average time for 5 files : %f\n", dt_avg);
    close(network_socket);
}
