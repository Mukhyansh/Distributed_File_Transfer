#include<stdio.h>
#include<stdlib.h>

int main(){

    FILE *f1=fopen("src/Chunking/out1.txt","rb");
    FILE *f2=fopen("src/Chunking/out2.txt","rb");
    FILE *f3=fopen("src/Chunking/out3.txt","rb");
    FILE *f4=fopen("src/Chunking/out4.txt","rb");

    FILE *out=fopen("src/Chunking/final_output.txt","wb");
    if(!f1 || !f2 || !f3 || !f4 || !out){
        printf("File opening failed.\n");
        return 1;
    }

    int ch;
    while((ch=fgetc(f1))!=EOF) fputc(ch,out);
    while((ch=fgetc(f2))!=EOF) fputc(ch,out);
    while((ch=fgetc(f3))!=EOF) fputc(ch,out);
    while((ch=fgetc(f4))!=EOF) fputc(ch,out);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(out);

    printf("Reconstruction complete.\n");

    return 0;
}