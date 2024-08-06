#include "delete_file.h"
#include <iostream>
#include <cstdio>  // For file operations

std::string delete_file(const std::string& filename) {
    if (std::remove(filename.c_str()) != 0) {
        return "Error deleting file: " + filename;
    } else {
        return "File deleted successfully: " + filename;
    }
}
