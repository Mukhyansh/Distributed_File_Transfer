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
 

-**Still incomplete, only thing left is linking of all the files and modules through headers(hopefully).**
