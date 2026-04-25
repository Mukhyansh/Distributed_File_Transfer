#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

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
	socklen_t client_len; //32 bit data type, contains our internet address
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0){
		error("Error opening Socket!");
	}
	
	memset(&server_addr, 0, sizeof(server_addr)); //clears any data/text

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
	while(1){
		memset(&str,0,sizeof(str));
		n=read(newsockfd,str,256);
		if(n<0){
			error("Error on reading!\n");
		}
		printf("Client: %s\n", str);
		memset(str,0,255);
		fgets(str,255,stdin);
		n=write(newsockfd,str,strlen(str));

		if(n<0){
			error("Error on Writing!\n");
		}
		int i=strncmp("Bye",str,3);
		if(i==0){
			break;
		}
	}
	close(newsockfd);
	close(sockfd);
	return EXIT_SUCCESS;
}
