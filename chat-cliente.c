#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
 int fd_clients_servers, fd_servers_client;
 char template[40], request[220], send[160], nick[20],recive[160];
 
 fd_clients_servers=open("/tmp/fifo-clients-servers", O_RDWR);

// sprintf(template, "/tmp/fifo-servers-client-%d", getpid());

 
 
 printf("Bem-vindo ao PinguCHAT divirtasse.\n"); 
 printf("Insira o seu Nick: "); 
 scanf("%s\n", nick);
 
 sprintf(template, "/tmp/fifo-servers-client-%s", nick);	
 mkfifo(template, 00666); chmod(template, 00666);
 fd_servers_client=open(template, O_RDWR);
 
if(fork()==0){
	while(1) {
	// printf("client [%d]: index? ", getpid()); 
	 //scanf("%s", send);
	 gets(send);//alternativa ao scanf
	 sprintf(request, "%s%s", send, template);
	 memcpy(request, send, sizeof(send));
	 memcpy(request+sizeof(send), template, sizeof(template));
	 write(fd_clients_servers, request, sizeof(request));
	// read(fd_servers_client, send, 160);
	 printf("client: word debug: %s\n", send);
	}
}
while(1){
//working......	
	fd_servers_client=open(template, O_RDWR);
	 read(fd_servers_client, recive, 160);
	 printf("%s\n", recive);
	// close(fd_servers_client);
	}
 close(fd_clients_servers); 
 close(fd_servers_client);
 remove(template);

 return(0);
}
