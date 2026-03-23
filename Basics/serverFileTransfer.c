#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<ctype.h>
#include<netdb.h>
#include<netinet/in.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc,char* argv[]){
    if(argc<2){
        fprintf(stderr,"Port number not provided!\n");
        exit(1);
    }
    
    int sockfd,newsockfd,portno,n;
    
    char str[256];
    
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    if(sockfd<0){
        error("Error opening Socket!");
    }
    
    memset(&server_addr, 0, sizeof(server_addr));

    portno=atoi(argv[1]);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(portno);

    if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        error("Binding Failed!\n");
    }

    listen(sockfd,5);
    client_len=sizeof(client_addr);
    newsockfd=accept(sockfd,(struct sockaddr*) &client_addr,&client_len);

    if(newsockfd<0){
        error("Error on Accept!\n");
    }

    FILE* fp;
    fp=fopen("Hello_gathered.txt","w");
    if(fp==NULL){
        error("File open failed!");
    }

    char buffer[1024];

    while((n = read(newsockfd,buffer,sizeof(buffer))) > 0){
        fwrite(buffer,1,n,fp);
    }

    printf("The File has been received!\n");
    fclose(fp);
    close(newsockfd);
    close(sockfd);
    return EXIT_SUCCESS;
}