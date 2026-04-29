#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include "ActualChunking.h"
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

#define MAX_CHUNKS 4

void chunk_the_file(char* filename){
	FILE* fp=fopen(filename,"rb");
	if(!fp){
		perror("Error opening the file!");
		return;
	}
	
	fseek(fp,0,SEEK_END);
	long size=ftell(fp);
	fseek(fp,0,SEEK_SET);

	if(size<10){
		perror("Size too small lol!");
		return;
	}

	FILE* f1=fopen("1.txt","wb");
	FILE* f2=fopen("2.txt","wb");
	FILE* f3=fopen("3.txt","wb");
	FILE* f4=fopen("4.txt","wb");

	if(!f1 || !f2 || !f3 || !f4){
	    perror("Error opening output files");
	    fclose(fp);
	    return;
	}

	// printf("Check");
	
	long s=size/MAX_CHUNKS;

	for(int i=0;i<s;i++){
		int ch=fgetc(fp);
		if(ch==EOF) break;
		fputc(ch,f1);
	}
	fseek(fp,s,SEEK_SET);

	for(int i=0;i<s;i++){
		int ch=fgetc(fp);
		if(ch==EOF) break;
		fputc(ch,f2);
	}
	// printf("Check");
	
	fseek(fp,2*s,SEEK_SET);

	for(int i=0;i<s;i++){
		int ch=fgetc(fp);
		if(ch==EOF) break;
		fputc(ch,f3);
	}
	
	fseek(fp,3*s,SEEK_SET);

	for(int i=0;i<s;i++){
		int ch=fgetc(fp);
		if(ch==EOF) break;
		fputc(ch,f4);
	}	
	// printf("Check");
	char* chunk_names[MAX_CHUNKS] = {"1.txt","2.txt","3.txt","4.txt"};

	fclose(fp);
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);

	FILE* meta = fopen("metadata.txt","w");
	if (!meta){
	    perror("Error creating metadata");
	    return;
	}
	fprintf(meta, "filename:%s\n", filename);
	fprintf(meta, "filesize:%ld\n", size);
	fprintf(meta, "chunks:%d\n", MAX_CHUNKS);
	for(int i=0;i<MAX_CHUNKS;i++){
	    fprintf(meta, "chunk%d:%s\n",i,chunk_names[i]);
	}
	fclose(meta);
	
}

void reconstruct_from_metadata(char* output_filename){
    FILE* meta=fopen("metadata.txt", "r");
    if (!meta) {
        perror("Metadata missing");
        return;
    }
	char line[50];
    char key[50], value[100];
    char chunk_files[MAX_CHUNKS][100];
    char output_name[100]="output.txt";
    int chunk_count = 0;
	int total_chunks=0;

	// printf("Check1");

	while (fgets(line, sizeof(line), meta)){
		line[strcspn(line,"\n")]=0;
		char* colon=strchr(line,':');
		if(!colon) continue;

		int keyl=colon-line;
		strncpy(key,line,keyl);
		key[keyl]=0;
		strcpy(value,colon+1);
		
		if(strcmp(key,"chunks")==0){
			total_chunks=atoi(value);
		}
		else if(strncmp(key,"chunks",5)==0){
			if(chunk_count<MAX_CHUNKS){
				strcpy(chunk_files[chunk_count],value);
				chunk_count++;
			}
		}
	}

    fclose(meta);
	char* final;
	if(output_filename!=""){
		final=output_filename;
	} 
	else final="output.txt";

	if(chunk_count==0){
		fprintf(stderr,"Error lol");
		return;
	}

	puts("Reconstructing the file! Wait please.");
    FILE* out = fopen(final, "wb");
    if (!out) {
        perror("Error creating output file");
        return;
    }

    for(int i=0;i<chunk_count;i++){
        FILE* in=fopen(chunk_files[i], "rb");
        if(!in){
            perror("Missing chunk file");
            fclose(out);
            return;
        }

        int ch;
        while((ch = fgetc(in))!=EOF){
            fputc(ch,out);
        }
		// printf("Check");

        fclose(in);
    }

    fclose(out);
	printf("DONE!\n");
}

int main(void){
    chunk_the_file("test.txt");
	// printf("Check");
    reconstruct_from_metadata("lolol.txt");
    return 0;
}