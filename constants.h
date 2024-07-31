#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

#define HASH_SIZE 32 // 32 bytes is a sha256 hash
#define BLOCK_SIZE 256 // Defined block byte size of file. 256 is large but not too large

std::string request_blocks_file_name(std::vector<int> missing_blocks, char *filename) {
    std::string return_string = std::string{"requestForBlocks"};
    for (int i = 0; i < missing_blocks.size(); i++) {
        return_string += missing_blocks[i];
    }
    return_string = return_string + "ForFile" + filename;
    return return_string;
}

#endif // CONSTANTS_H