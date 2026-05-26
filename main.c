#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<unistd.h>

int main(int argc,char* argv[]){
    printf("Step 1: Chunking\n");
    system("./chunk");
    printf("STEP 2: Compressing\n");

    system("./compress src/Chunking/1.txt src/Compressor/1.dat");
    system("./compress src/Chunking/2.txt src/Compressor/2.dat");
    system("./compress src/Chunking/3.txt src/Compressor/3.dat");
    system("./compress src/Chunking/4.txt src/Compressor/4.dat");

    printf("STEP 3: Transfer\n");

    system("./client 127.0.0.1 8080 1.dat");
    system("./client 127.0.0.1 8081 2.dat");
    system("./client 127.0.0.1 8082 3.dat");
    system("./client 127.0.0.1 8083 4.dat");

    printf("STEP 4: Decompressing\n");

    system("./decompress received1.dat out1.txt");
    system("./decompress received2.dat out2.txt");
    system("./decompress received3.dat out3.txt");
    system("./decompress received4.dat out4.txt");

    printf("DONE!\n");

    return 0;
}