# Distributed_File_Transfer

A Distributed File transfer System with self-implemented File compressor written in C.

#Modules

-First is the chunking module which obv chunk the files into a constant fixed size of 4 and then the reconstruct method reconstructs the file with the broken chunks of the file.
-Second is the Compressor module which compresses those chunks and then the decompress method comes into play and decompresses the compressed files.
-Third is the File Transfer module which sends the chunked and compressed file to another port/ip through sockets and tcp.
-Fourth is the terminal chat, not sure how this will come into place but will try my best to integrate it to the system.
 

-**Still incomplete, only thing left is linking of all the files and modules through headers(hopefully).**
