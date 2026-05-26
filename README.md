# Distributed File Transfer System

A distributed file transfer system with a self-implemented file compression module written in C.

---

## Modules

### 1. Chunking Module
- Splits a file into fixed-size chunks (size = 4 units).
- Reconstructs the original file from the generated chunks.

### 2. Compression Module
- Compresses each chunk individually.
- Decompresses chunks back to their original form.

### 3. File Transfer Module
- Sends compressed chunks over a network using TCP sockets.
- Supports transfer via IP address and port.

### 4. Terminal Chat Module
- Basic terminal-based chat system.
- Planned for integration with the file transfer workflow.

### 5. HOW TO RUN
- Go to the main folder(Distributed_File_Transfer).
- Compile the main file with the flag main ( gcc main.c -o main ).
- Execute the main file ( ./main ).
 

-**This is just a hardcoded simulation of the actual process which happens behind the curtains on our distributed systems!**
