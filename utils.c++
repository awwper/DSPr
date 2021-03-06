#ifndef UTIL
#define UTIL
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
extern "C" {
	char * inet_ntoa(struct in_addr);
}

void setBroadcast(int s)
{
	int arg;
#ifdef SO_BROADCAST
	arg =1;
	if(setsockopt(s, SOL_SOCKET, SO_BROADCAST, &arg, sizeof(arg)) <0){
		perror("setsockopt SO_BROADCAST---");
		exit(-1);
	}
#endif
}
void makeLocalSA(struct sockaddr_in *sa)
{
	sa->sin_family = AF_INET;
	sa->sin_port = htons(0);
	sa-> sin_addr.s_addr = htonl(INADDR_ANY);
}
void makeDestSA(struct sockaddr_in * sa, char *hostname, int port)
{
	 struct hostent *host;
	 sa->sin_family = AF_INET;
	 if((host = gethostbyname(hostname))== NULL){
		 printf("Unknown host name\n");
		 exit(-1);
	 }
	 sa-> sin_addr = *(struct in_addr *) (host->h_addr);
	 sa->sin_port = htons(port);
}
void printSA(struct sockaddr_in sa)
{
	printf("sa = %d, %s, %d\n", sa.sin_family,
			inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
}
#endif
