CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
LDFLAGS = -lm

SRC_DIR = src

CHUNK = $(SRC_DIR)/Chunking/chunk
RECONSTRUCT = $(SRC_DIR)/Chunking/reconstruct

COMPRESS = $(SRC_DIR)/Compressor/compress
DECOMPRESS = $(SRC_DIR)/Compressor/decompress

SERVER_FILE = $(SRC_DIR)/FileTransfer/server
CLIENT_FILE = $(SRC_DIR)/FileTransfer/client

MAIN = main

CHUNK_SRC = $(SRC_DIR)/Chunking/ActualChunking.c
RECONSTRUCT_SRC = $(SRC_DIR)/Chunking/reconstruct.c

COMPRESS_SRC = $(SRC_DIR)/Compressor/compress.c
DECOMPRESS_SRC = $(SRC_DIR)/Compressor/decompress.c

SERVER_FILE_SRC = $(SRC_DIR)/FileTransfer/serverFileTransfer.c
CLIENT_FILE_SRC = $(SRC_DIR)/FileTransfer/clientFileTransfer.c

MAIN_SRC = main.c

.PHONY: all clean help

all: $(CHUNK) $(RECONSTRUCT) $(COMPRESS) $(DECOMPRESS) $(SERVER_FILE) $(CLIENT_FILE) $(MAIN)
	@echo "Build complete!"

$(CHUNK): $(CHUNK_SRC)
	@echo "Building chunk..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(RECONSTRUCT): $(RECONSTRUCT_SRC)
	@echo "Building reconstruct..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(COMPRESS): $(COMPRESS_SRC)
	@echo "Building compress..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(DECOMPRESS): $(DECOMPRESS_SRC)
	@echo "Building decompress..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(SERVER_FILE): $(SERVER_FILE_SRC)
	@echo "Building server..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(CLIENT_FILE): $(CLIENT_FILE_SRC)
	@echo "Building client..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(MAIN): $(MAIN_SRC)
	@echo "Building main..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	@echo "Cleaning generated files..."

	rm -f $(CHUNK)
	rm -f $(RECONSTRUCT)

	rm -f $(COMPRESS)
	rm -f $(DECOMPRESS)

	rm -f $(SERVER_FILE)
	rm -f $(CLIENT_FILE)

	rm -f $(MAIN)

	rm -f $(SRC_DIR)/Chunking/1.txt
	rm -f $(SRC_DIR)/Chunking/2.txt
	rm -f $(SRC_DIR)/Chunking/3.txt
	rm -f $(SRC_DIR)/Chunking/4.txt

	rm -f $(SRC_DIR)/Chunking/out1.txt
	rm -f $(SRC_DIR)/Chunking/out2.txt
	rm -f $(SRC_DIR)/Chunking/out3.txt
	rm -f $(SRC_DIR)/Chunking/out4.txt

	rm -f $(SRC_DIR)/Chunking/final_output.txt
	rm -f $(SRC_DIR)/Chunking/metadata.txt

	rm -f $(SRC_DIR)/Compressor/*.dat

	rm -f $(SRC_DIR)/FileTransfer/received1.dat
	rm -f $(SRC_DIR)/FileTransfer/received2.dat
	rm -f $(SRC_DIR)/FileTransfer/received3.dat
	rm -f $(SRC_DIR)/FileTransfer/received4.dat

	@echo "Clean complete!"

help:
	@echo "Distributed File Transfer System"
	@echo ""
	@echo "Targets:"
	@echo "  make        - Build everything"
	@echo "  make all    - Build everything"
	@echo "  make clean  - Remove executables and generated files"
	@echo "  make help   - Show this help"



	#This make file is basically useless atp because of the main.c file in the main folder lol.