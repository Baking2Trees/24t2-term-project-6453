#include "copy_file.h"
#include <fstream>
#include <iostream>

// Function to copy a file from source to destination
std::string copy_file(const std::string& sourceFilename, const std::string& destinationFilename) {
    std::ifstream sourceFile(sourceFilename, std::ios::binary);
    if (!sourceFile) {
        std::cerr << "Error opening source file: " << sourceFilename << std::endl;
        return "Error opening source file: " + sourceFilename;
    }
    
    std::ofstream destinationFile(destinationFilename, std::ios::binary);
    if (!destinationFile) {
        std::cerr << "Error opening destination file: " << destinationFilename << std::endl;
        return "Error opening destination file: " + destinationFilename;
    }
    
    destinationFile << sourceFile.rdbuf();
    
    if (!destinationFile) {
        std::cerr << "Error writing to destination file: " << destinationFilename << std::endl;
        return "Error writing to destination file: " + destinationFilename;
    }
    
    return "";
}
