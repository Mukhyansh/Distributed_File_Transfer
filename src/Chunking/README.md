# File Chunking Algorithm

## Overview
This module implements a **4-piece chunking algorithm** that divides files into equal-sized chunks for distributed file transfer. Any remainder bytes are distributed to the last chunk.

## How It Works
- Takes a file and splits it into **4 equal chunks**
- Each chunk size = `total_file_size / 4`
- The **last chunk** receives any remaining bytes
  - Example: 10 KB file → 4 chunks of 2.5 KB each (last chunk naturally includes remainder)

## Files
- **chunking.h** - Header file with data structures and function declarations
- **ToMake.c** - Implementation of chunking functions

## Data Structures

### `Chunk`
```c
typedef struct {
    char* data;        // Pointer to chunk data
    size_t size;       // Size of this chunk in bytes
    int chunk_id;      // Chunk identifier (0-3)
} Chunk;
```

### `ChunkedFile`
```c
typedef struct {
    Chunk chunks[4];   // Array of 4 chunks
    int file_size;     // Original file size in bytes
    size_t chunk_size; // Size of each base chunk
} ChunkedFile;
```

## Functions

### `int chunk_size(int totalBytes)`
Calculates the base chunk size by dividing total bytes by 4.

**Parameters:**
- `totalBytes` - Total file size

**Returns:** Base chunk size in bytes

---

### `int chunk_the_file(char* fileName, ChunkedFile* chunked_file)`
Reads a file from disk and splits it into 4 chunks in memory.

**Parameters:**
- `fileName` - Path to the file to chunk
- `chunked_file` - Pointer to ChunkedFile struct (will be populated)

**Returns:** `EXIT_SUCCESS` on success, `EXIT_FAILURE` on failure

**Note:** Allocates memory for all chunks. Remember to call `free_chunks()` when done!

---

### `void free_chunks(ChunkedFile* chunkedFile)`
Frees all dynamically allocated memory used by chunks.

**Parameters:**
- `chunkedFile` - Pointer to ChunkedFile struct to clean up

---

### `int save_chunk_to_file(Chunk* chunk, char* outputFile)`
Saves a single chunk to a file on disk. *(Declared but not implemented yet)*

---

### `int reconstruct_file_from_chunks(Chunk* chunks, char* output_filename)`
Reconstructs the original file from 4 chunks. *(Declared but not implemented yet)*

## Compilation

### Compile as object file (for linking with other modules)
```bash
gcc -c ToMake.c -o chunking.o
```

### Compile with a main function
```bash
gcc ToMake.c main.c -o chunking_program
```

## Example Usage

```c
#include "chunking.h"

int main() {
    ChunkedFile chunked_file;
    
    // Chunk the file
    if (chunk_the_file("input.txt", &chunked_file) != EXIT_SUCCESS) {
        fprintf(stderr, "Failed to chunk file\n");
        return 1;
    }
    
    printf("File chunked successfully!\n");
    printf("File size: %d bytes\n", chunked_file.file_size);
    printf("Base chunk size: %zu bytes\n", chunked_file.chunk_size);
    
    // Access chunks
    for (int i = 0; i < MAX_CHUNKS; i++) {
        printf("Chunk %d: %zu bytes\n", i, chunked_file.chunks[i].size);
    }
    
    // Clean up
    free_chunks(&chunked_file);
    
    return 0;
}
```

## Current Status
- ✅ Core chunking logic implemented
- ✅ Memory allocation/deallocation
- ⚠️ `save_chunk_to_file()` - Not yet implemented
- ⚠️ `reconstruct_file_from_chunks()` - Not yet implemented

## Known Issues
- Bug in `ToMake.c` line 24: `ChunkSize` should be `chunk_size` (case-sensitive)

## Integration with Distributed Transfer
Once chunks are created:
1. Each chunk can be sent over a socket to different nodes
2. Nodes can receive and save their assigned chunk
3. Reconstruct the original file by combining chunks in order

## License
Part of PBL4 Distributed File Transfer project
