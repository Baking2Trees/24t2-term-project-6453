#ifndef REQUEST_H
#define REQUEST_H

#include <vector>

// Inputs: Vector of ints and filename
// Does: Writes to a new_file with the missing data
// Returns: filename of the file with the missing data
std::string request_blocks(std::vector<int> missing_blocks, const char *filename);
// Transfer file is structured in the following way
//      4 bytes - block number
//      4 bytes - size of block in bytes
//      block content

#endif // REQUEST_H