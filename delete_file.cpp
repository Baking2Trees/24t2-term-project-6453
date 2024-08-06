#include "delete_file.h"
#include <iostream>
#include <cstdio>  // For file operations

void delete_file(const std::string& filename) {
    if (std::remove(filename.c_str()) != 0) {
        std::cerr << "Error deleting file: " << filename << std::endl;
    } else {
        std::cout << "File deleted successfully: " << filename << std::endl; // Is the Merkle tree updated?
    }
}
