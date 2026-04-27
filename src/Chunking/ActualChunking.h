#ifndef ACTUALCHUNKING_H
#define ACTUALCHUNKING_H

#include <stdio.h>

#define MAX_CHUNKS 4

void chunk_the_file(char *filename);

void reconstruct_from_metadata(char* filename);

#endif
