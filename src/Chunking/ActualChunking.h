#ifndef ACTUALCHUNKING_H
#define ACTUALCHUNKING_H

#include <stdio.h>

#define MAX_CHUNKS 4

void chunk_the_file(char *filename);

void reconstruct_the_file(char filenames[MAX_CHUNKS][10]);

#endif
