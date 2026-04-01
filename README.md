# Distributed_File_Transfer

A Distributed File transfer System with self-implemented File compressor written in C.

## Features

- **File Transfer Protocol**: Transfer files over the network between clients and servers using standard C sockets.
- **Custom Compressor**: Implements a file compression utility utilizing a Trie data structure to reduce payload size.
- **Socket Programming Basics**: Includes foundational implementations for establishing robust client-server communication.

## Repository Structure

- `Basics/`
  - `ServerSocket.c` & `ClientSocket.c`: Basic examples of setting up socket communication.
  - `serverFileTransfer.c` & `clientFileTransfer.c`: Programs to transfer files across the network.
- `Compressor/`
  - `compress.c` & `trie.c`: The core custom compression tool. Includes an executable and a sample `1.txt` file.

## Getting Started

### Prerequisites

- GCC compiler
- POSIX-compliant operating system (Linux/macOS) for the C socket libraries.

### Compiling and Running the File Transfer

1. Navigate to the `Basics` directory:
   ```bash
   cd Basics
   ```
2. Compile the server and client:
   ```bash
   gcc serverFileTransfer.c -o serverFileTransfer
   gcc clientFileTransfer.c -o clientFileTransfer
   ```
3. Start the server (it will listen for incoming connections):
   ```bash
   ./serverFileTransfer
   ```
4. In another terminal, start the client to connect and transfer:
   ```bash
   ./clientFileTransfer
   ```

### Using the Compressor

1. Navigate to the `Compressor` directory:
   ```bash
   cd Compressor
   ```
2. Compile the compression utility (if not already compiled):
   ```bash
   gcc compress.c trie.c -o compress
   ```
3. Run the executable:
   ```bash
   ./compress
   ```