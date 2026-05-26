#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<unistd.h>

int main(int argc,char* argv[]){

    printf("File Chunking check\n");
    system("./src/Chunking/chunk");

    printf("File compression check\n");

    system("./src/Compressor/compress src/Chunking/1.txt src/Compressor/1.dat");
    system("./src/Compressor/compress src/Chunking/2.txt src/Compressor/2.dat");
    system("./src/Compressor/compress src/Chunking/3.txt src/Compressor/3.dat");
    system("./src/Compressor/compress src/Chunking/4.txt src/Compressor/4.dat");

    printf("File transfer check\n");

    system("./src/FileTransfer/client 127.0.0.1 8080 src/Compressor/1.dat");
    system("./src/FileTransfer/client 127.0.0.1 8081 src/Compressor/2.dat");
    system("./src/FileTransfer/client 127.0.0.1 8082 src/Compressor/3.dat");
    system("./src/FileTransfer/client 127.0.0.1 8083 src/Compressor/4.dat");

    printf("Decompressing check\n");

    system("./src/Compressor/decompress src/FileTransfer/received1.dat src/Chunking/out1.txt");
    system("./src/Compressor/decompress src/FileTransfer/received2.dat src/Chunking/out2.txt");
    system("./src/Compressor/decompress src/FileTransfer/received3.dat src/Chunking/out3.txt");
    system("./src/Compressor/decompress src/FileTransfer/received4.dat src/Chunking/out4.txt");

    printf("Reconstructing the file!\n");

    system("./src/Chunking/reconstruct");

    printf("Done!\n");

    return 0;
}