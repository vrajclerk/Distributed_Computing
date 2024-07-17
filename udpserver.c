#include <sys/types.h> 
#include <sys/socket.h> #include <stdio.h> 
#include <netinet/in.h> 
#define MAXLINESIZE 100 
#define SERV_PORT 8000 
int main(int argc, char** argv) 
{ 
int sockfd; 
struct sockaddr_in servaddr, cliaddr; 
int n; 
socklen_t len; 
char mesg [MAXLINESIZE]; 

/*Create socket*/ 
sockfd = socket(AF_INET,SOCK_DGRAM,0); 
/*Initialize socket address structure*/ 
bzero(&servaddr,sizeof(servaddr)); servaddr.sin_family = AF_INET; 
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

servaddr.sin_port = htons(SERV_PORT); 
/*bind socket address to the socket*/ 
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)); 

for(;;) { 
len=sizeof(cliaddr); 
/*wait for datagram to arrive, receive a datagram*/ 
n=recvfrom(sockfd,mesg, MAXLINESIZE,O,(struct sockaddr*)&cliaddr,&len); 
/*send back the datagram to the client from which it arrived*/ 
sendto(sockfd,mesg,n,0, (struct sockaddr*)&cliaddr,len); 
} 
} 
