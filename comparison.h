#ifndef COMPARISON_H
#define COMPARISON_H

#include <vector>
#include "merkle.h"

// Inputs: Takes in a merkle tree to a file and its filename
// Does: Compares the merkle tree to its own version of the file
// Returns: Vector containing the needed blocks
std::vector<int> comparison(merkle_tree cloud_file_mt, char *filename);

#endif // COMPARISON_H