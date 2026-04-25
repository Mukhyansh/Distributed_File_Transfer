CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
LDFLAGS = -lm

# Directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

# Create bin directory if it doesn't exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

# Targets
COMPRESS = $(BIN_DIR)/compress
DECOMPRESS = $(BIN_DIR)/decompress
SERVER_CHAT = $(BIN_DIR)/server_chat
CLIENT_CHAT = $(BIN_DIR)/client_chat
SERVER_FILE = $(BIN_DIR)/server_file
CLIENT_FILE = $(BIN_DIR)/client_file

# Source files
COMPRESS_SRC = $(SRC_DIR)/Compressor/compress.c
DECOMPRESS_SRC = $(SRC_DIR)/Compressor/decompress.c
SERVER_CHAT_SRC = $(SRC_DIR)/TerminalChat/ServerSocket.c
CLIENT_CHAT_SRC = $(SRC_DIR)/TerminalChat/ClientSocket.c
SERVER_FILE_SRC = $(SRC_DIR)/FileTransfer/serverFileTransfer.c
CLIENT_FILE_SRC = $(SRC_DIR)/FileTransfer/clientFileTransfer.c

# Phony targets
.PHONY: all clean help

all: $(COMPRESS) $(DECOMPRESS) $(SERVER_CHAT) $(CLIENT_CHAT) $(SERVER_FILE) $(CLIENT_FILE)
	@echo "All targets built successfully!"

$(COMPRESS): $(COMPRESS_SRC)
	@echo "Building compress..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(DECOMPRESS): $(DECOMPRESS_SRC)
	@echo "Building decompress..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(SERVER_CHAT): $(SERVER_CHAT_SRC)
	@echo "Building server_chat..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(CLIENT_CHAT): $(CLIENT_CHAT_SRC)
	@echo "Building client_chat..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(SERVER_FILE): $(SERVER_FILE_SRC)
	@echo "Building server_file..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(CLIENT_FILE): $(CLIENT_FILE_SRC)
	@echo "Building client_file..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	@echo "Cleaning up..."
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	rm -f *.o *.dat *.bin
	@echo "Clean complete!"

help:
	@echo "Distributed File Transfer System - Build Help"
	@echo "=============================================="
	@echo "Targets:"
	@echo "  make all          - Build all programs"
	@echo "  make clean        - Remove all built files"
	@echo "  make help         - Show this help message"
	@echo ""
	@echo "Programs Built:"
	@echo "  compress          - File compression utility"
	@echo "  decompress        - File decompression utility"
	@echo "  server_chat       - Terminal chat server"
	@echo "  client_chat       - Terminal chat client"
	@echo "  server_file       - File transfer server"
	@echo "  client_file       - File transfer client"
