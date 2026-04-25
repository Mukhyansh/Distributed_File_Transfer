#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]){
    int sockfd,portno,n;
    struct sockaddr_in server_addr;
    struct hostent* server;
    char str[256];
    if(argc<3){
        fprintf(stderr,"usage %s hostname port\n",argv[0]);
        exit(1);
    }
    portno=atoi(argv[2]);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        error("Error opening socket!\n");
    }
    server = gethostbyname(argv[1]);
    if(server==NULL){
        fprintf(stderr,"Error, No Such Host!\n");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    memcpy(&server_addr.sin_addr.s_addr,
       server->h_addr_list[0],
       server->h_length);

    server_addr.sin_port = htons(portno);

    if(connect(sockfd,(struct sockaddr*) &server_addr,sizeof(server_addr))<0){
        error("Connection failed!\n");
    }
    while(1){
        memset(str,0,255);
        fgets(str,255,stdin);
        n=write(sockfd,str,strlen(str));
        if(n<0){
            error("Write Failed!\n");
        }
        memset(str,0,255);
        n=read(sockfd,str,255);
        if(n<0){
            error("Reading failed!\n");
        }
        printf("Server: %s\n",str);
        int i=strncmp("Bye",str,3);
        if(i==0) break;
    }
    close(sockfd);
}