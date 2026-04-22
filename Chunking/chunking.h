#ifndef CHUNKING_H
#define CHUNKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHUNKS 4

typedef struct {
    char* data;
    size_t size;
    int chunk_id;
} Chunk;

typedef struct {
    Chunk chunks[MAX_CHUNKS];
    int file_size;
    size_t chunk_size;
} ChunkedFile;

int chunk_size(int totalBytes);

/**
 * Load and chunk a file into 4 equal pieces
 * The remainder is added to the last chunk
 * 
 * Parameters:
 *   filename: path to the file
 *   chunked_file: pointer to ChunkedFile structure to store chunks
 * 
 * Returns: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int chunk_the_file(char* filename, ChunkedFile* chunked_file);

/**
 * Free memory allocated for chunks
 */
void free_chunks(ChunkedFile* chunked_file);

/**
 * Save a specific chunk to a file
 */
int save_chunk_to_file(Chunk* chunk, char* outputFile);

/**
 * Reconstruct file from chunks
 * Parameters:
 *   chunks: array of Chunk structures
 *   output_filename: name of the reconstructed file
 * 
 * Returns: EXIT_SUCESS on success, EXIT_FAILURE on failure
 */
int reconstruct_file(ChunkedFile* chunkedFile,char* output_filename);

#endif
