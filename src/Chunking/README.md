### `README.md`

```md
# Distributed File Chunking System (C)

## Overview
This project demonstrates a basic file chunking and reconstruction system written in C. It splits a file into multiple parts (chunks), stores metadata about those chunks, and reconstructs the original file using that metadata.

This is a prototype intended for academic demonstration of file handling and system design concepts.

---

## Features

- Splits a file into multiple chunks
- Stores metadata for reconstruction
- Reconstructs original file from chunks
- Works for both text and binary files
- Simple and modular design

---

## How It Works

### 1. Chunking (`chunk_the_file`)
- Reads the input file
- Divides it into `MAX_CHUNKS` equal parts
- Writes each part into separate files:
```

1.txt, 2.txt, 3.txt, 4.txt

```
- Stores metadata in `metadata.txt`:
```

filename:input.txt
filesize:1234
chunks:4
chunk0:1.txt
chunk1:2.txt
chunk2:3.txt
chunk3:4.txt

```

---

### 2. Reconstruction (`reconstruct_from_metadata`)
- Reads `metadata.txt`
- Extracts chunk filenames
- Reads each chunk sequentially
- Writes data into reconstructed output file

---

## File Structure

```

.
├── main.c
├── file_chunks.h
├── chunking.c
├── metadata.txt
├── 1.txt
├── 2.txt
├── 3.txt
├── 4.txt
└── output.txt

````

---

## Compilation

```bash
gcc main.c chunking.c -o program
````

---

## Usage

### Step 1: Chunk the file

```c
chunk_the_file("input.txt");
```

### Step 2: Reconstruct the file

```c
reconstruct_from_metadata();
```

---

## Notes

* Uses binary-safe file operations (`rb`, `wb`)
* Handles remainder bytes in last chunk
* Metadata ensures correct reconstruction order
* Chunk files must not be modified before reconstruction

---

## Limitations

* Fixed number of chunks (`MAX_CHUNKS`)
* No checksum or integrity validation
* No networking (local system only)
* Metadata parsing is basic

---

## Future Improvements

* Dynamic chunk sizing
* Checksum/hash validation
* Network-based distributed transfer
* Parallel chunk processing

---

## Purpose

This project demonstrates:

* File handling in C
* Use of metadata for system design
* Basic idea of distributed file systems

---

## Author

Mukhyansh

