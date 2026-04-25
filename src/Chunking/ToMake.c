#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include"chunking.h"
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

int chunk_size(int totalBytes){
    return totalBytes/MAX_CHUNKS;
}

int chunk_the_file(char* fileName, ChunkedFile* chunked_file){
    FILE* fp=fopen(fileName,"rb");
    if(!fp){
        perror("ERROR OPENING THE GIVEN FILE!\n");
        return 1;
    }
    fseek(fp,0,SEEK_END);
    int fileSize=ftell(fp);
    fseek(fp,0,SEEK_SET);

    chunked_file->file_size=fileSize;
    chunked_file->chunk_size=chunk_size(fileSize);

    for(int i=0;i<MAX_CHUNKS;i++){
        chunked_file->chunks[i].chunk_id=i;
        if(i==MAX_CHUNKS-1){
            chunked_file->chunks[i].size=fileSize-(chunked_file->chunk_size* (MAX_CHUNKS-1));
        }
        else{
            chunked_file->chunks[i].size=chunked_file->chunk_size;
        }
        chunked_file->chunks[i].data=(char*)malloc(chunked_file->chunks[i].size);
        char* stringRead=fread(chunked_file->chunks[i].data,1,chunked_file->chunks[i].size,fp);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

void free_chunks(ChunkedFile* chunkedFile){
    for(int i=0;i<MAX_CHUNKS;i++){
        if(chunkedFile->chunks[i].data!=NULL){
            free(chunkedFile->chunks[i].data);
            chunkedFile->chunks[i].data=NULL;
        }
    }
}

int reconstruct_file(ChunkedFile* chunkedFile,char* outputFile){
    FILE* fp=fopen(outputFile,"wb");
    if(!fp){
        perror("Error opening the file!\n");
        return EXIT_FAILURE;
    }
    for(int i=0;i<MAX_CHUNKS;i++){
        int stringWritten=fwrite(chunkedFile->chunks[i].data,1,chunkedFile->chunks[i].size,fp);
        if(stringWritten!=chunkedFile->chunks[i].size){
            perror("Error writing the chunks!");
            return EXIT_FAILURE;
        }
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int save_chunk_to_file(Chunk* chunk,char* outputFile){
    FILE* fp=fopen(outputFile,"wb+");
    if(!fp){
        perror("Error opening the file!\n");
        return EXIT_FAILURE;
    }
    char* stringWritten=fwrite(chunk->data, 1, chunk->size,fp);
    if(stringWritten!=chunk->size){
        perror("Error saving the chunk to the file!\n");
        return EXIT_FAILURE;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

