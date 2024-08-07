#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "request.h"
#include "constants.h"

std::string request_blocks(std::vector<int> missing_blocks, const char *filename) {
    std::string transfer_data_filename = request_blocks_file_name(missing_blocks, filename);

    FILE* cloud_file = std::fopen(filename, "rb");
    if (!cloud_file) {
        std::cerr << "Cant open the cloud file\n";
        std::exit(1);
    }

    FILE* transfer_file = std::fopen(transfer_data_filename.c_str(), "w");
    if (!transfer_file) {
        std::cerr << "Cant write transfer file\n";
        std::exit(1);
    }

    // Calculate size of cloud file
    std::fseek(cloud_file, 0, SEEK_END);
    long file_size = std::ftell(cloud_file);
    std::fseek(cloud_file, 0, SEEK_SET); // Dont need this atm


    for (int i = 0; i < missing_blocks.size(); i++) {
        int block_number = missing_blocks[i];
        
        // Write block number to file
        fwrite(&block_number, sizeof(int), 1, transfer_file);

        // Calculate byte index
        long byte_index = block_number * BLOCK_SIZE;

        // Write size to file
        int size;
        if (byte_index > file_size) {
            size = 0;
        } else if (byte_index + BLOCK_SIZE > file_size) {
            size = file_size - byte_index;
        } else {
            size = BLOCK_SIZE;
        }
        fwrite(&size, sizeof(int), 1, transfer_file);
        
        // Move file pointer
        std::fseek(cloud_file, byte_index, SEEK_SET);
        
        // Move (size) num bytes
        for (int i = 0; i < file_size; i++) {
            char byte = fgetc(cloud_file);
            fputc(byte, transfer_file);
        }

        // Set file pointer to end of file
        std::fseek(cloud_file, 0, SEEK_END);
    }

    std::fclose(transfer_file);
    std::fclose(cloud_file);

    return transfer_data_filename;
}