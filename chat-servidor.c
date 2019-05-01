#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int init()
{
 mkfifo("/tmp/fifo-clients-servers", 00666);
 chmod("/tmp/fifo-clients-servers", 00666);
 
 return(0);
}

int deletefiles()
{
 remove("/tmp/fifo-clients-servers");
 return(0);
}

int main() {
 int fd_clients_servers, fd_servers_client, cont=1;
 char template[40], request[220], send[160];
 
 init();
 
 fd_clients_servers=open("/tmp/fifo-clients-servers", O_RDWR);
 
 while(1) {
	 read(fd_clients_servers, request, sizeof(request));
	 sscanf(request, "%s%s", send, template);
	 memcpy(send, request, sizeof(send));
	 memcpy(template, request+sizeof(send), sizeof(template));
	 printf("server [%d]: De : %s\n", getpid(), template);
	 printf("server [%d]: msg: %s\n", getpid(), send);
	 //lseek(fd_clients_servers, 160, SEEK_SET);
	 //read(fd_clients_servers, send, 160);
	 //cont++;
	 //printf("server [%d]: word: %s\n", getpid(), send);
	 fd_servers_client=open(template, O_RDWR);
	 write(fd_servers_client, send, 160);
	 close(fd_servers_client);
	 
 }
 deletefiles();
 
 return(0);
}
