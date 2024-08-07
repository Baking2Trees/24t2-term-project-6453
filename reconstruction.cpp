#include "reconstruction.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "constants.h"
#include <unistd.h>
#include <cstdio>

// Remebering this is the design of transfer file
// Transfer file is structured in the following way
//      4 bytes - block number
//      4 bytes - size of block in bytes
//      block content

void reconstruct(const char *transfer_filename, const char *filename) {
    FILE *transfer_file = std::fopen(transfer_filename, "rb");
    if (!transfer_file) {
        std::cerr << "Unable to open transfer_file\n";
        std::exit(1);
    }
    
    FILE *cloud_file = std::fopen(filename, "w+");
    if (!cloud_file) {
        // File could be new here - if is this case we need to change some version of code (check with Josh)
        std::cerr << "Unable to open local version of file\n";
        std::exit(1);
    }
    
    // This is important so we dont try writing past the end of the file
    // std::fseek(cloud_file, 0, SEEK_END);
    // long file_size = std::ftell(cloud_file);
    // std::fseek(cloud_file, 0, SEEK_SET);

    // FOR NOW DONT NEED AS WAY BLOCKS ARE PROVIDED SHOULD NOT CREATE ERRORS HERE

    uint32_t block_number;
    size_t bytes_read;
    while ((bytes_read = std::fread(&block_number, sizeof(uint32_t), 1, transfer_file)) == 1) {

        uint32_t block_size;
        bytes_read = std::fread(&block_size, sizeof(uint32_t), 1, transfer_file);
        if (bytes_read != 1) {
            std::exit(1);
        }

        long byte_index = block_number * BLOCK_SIZE;

        if (block_size != 0) {
            // Move file pointer to correct index
            std::fseek(cloud_file, byte_index, SEEK_SET);
            // fwrite(&block_size, 1, 1, cloud_file);

            // Write bytes to file
            for (int i = 0; i < block_size; i++) {
                char byte = fgetc(transfer_file);
                fputc(byte, cloud_file);
            }

            // move file pointer back to start for safety
            std::fseek(cloud_file, 0, SEEK_SET);
        } else {
            // In the event the block size is 0 we need to remove the rest of the file - its deletion
            int fd = fileno(cloud_file);
            ftruncate(fd, byte_index);
            // Delete transfer file
            std::fclose(transfer_file);
            std::remove(transfer_filename);
            return;
        }
    }
    std::fclose(transfer_file);
    std::remove(transfer_filename);
    std::fclose(cloud_file);
}