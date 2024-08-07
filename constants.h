#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

#define HASH_SIZE 32 // 32 bytes is a sha256 hash
#define BLOCK_SIZE 256 // Defined block byte size of file. 256 is large but not too large

std::string request_blocks_file_name(std::vector<int> missing_blocks, const char *filename);

#endif // CONSTANTS_H