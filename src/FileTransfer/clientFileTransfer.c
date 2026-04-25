#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<ctype.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc,char* argv[]){
    int sockfd,portno,n;
    struct sockaddr_in server_addr;
    struct hostent* server;

    char str[255];
    
    if(argc<3){
        error("Not enough arguments!\n");
        exit(1);
    }
    
    portno=atoi(argv[2]);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    if(sockfd<0){
        error("Error opening socket!\n");
    }
    
    server = gethostbyname(argv[1]);
    
    if(server==NULL){
        fprintf(stderr,"Error, no such host");
        exit(1);
    }
    
    memset((char*)&server_addr, 0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    memcpy((char*)&server_addr.sin_addr.s_addr,(char*)server->h_addr_list[0],server->h_length);
    server_addr.sin_port=htons(portno);
    
    if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        error("Connection Failed!\n");
    }
    
    FILE* f;
    f=fopen("Hello.txt","r");
    if(f==NULL){
        error("File open failed!\n");
    }

    char buffer[1024];

    while((n = fread(buffer,1,sizeof(buffer),f)) > 0){
        write(sockfd,buffer,n);
    }

    printf("The file has been successfully sent.Thankyou!\n");
    fclose(f);
    close(sockfd);
    return EXIT_SUCCESS;
}