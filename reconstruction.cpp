#include "reconstruction.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "constants.h"


// Remebering this is the design of transfer file
// Transfer file is structured in the following way
//      4 bytes - block number
//      4 bytes - size of block in bytes
//      block content

void reconstruct(char *transfer_filename, char *filename) {
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
        bytes_read = std::fread(&block_number, sizeof(uint32_t), 1, transfer_file);
        if (bytes_read != 1) {
            std::cerr << "Error in transfer format\n";
            std::exit(1);
        }

        long byte_index = block_number * BLOCK_SIZE;

        // Move file pointer to correct index
        std::fseek(cloud_file, byte_index, SEEK_SET);
        fwrite(&block_size, 1, 1, cloud_file);

        // move file pointer back to start for safety
        std::fseek(cloud_file, 0, SEEK_SET);
    }
    
    std::fclose(transfer_file);
    std::fclose(cloud_file);
}