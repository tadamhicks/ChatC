#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

 
void error(char *msg)
{
    perror(msg);
    exit(0);
}
 
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[512];
    if (argc < 3) {
        fprintf(stderr,"Usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR ON OPENING SOCKET");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR NO SUCH HOST\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    
    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) error("ERROR CONNECTING");
    printf("You are connected, you write first!\n");
    while(1)
    {
        printf("Please enter the message: ");
        bzero(buffer,512);
        fgets(buffer,511,stdin);
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) error("ERROR WRITING TO SOCKET");
        bzero(buffer,512);
        
        n = read(sockfd,buffer,511);
        if (n < 0) error("ERROR READING FROM SOCKET");
        printf("Friend: %s\n", buffer);
    }
    close(sockfd);
}
