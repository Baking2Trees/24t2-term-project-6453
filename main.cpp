#include <iostream>

#include "sha256.h"
#include "merkle.h"

int main (void) {
    // Create the merkle tree for a test file
    char filename[] = "exampletexts/t8.shakespeare.txt";
    merkle_tree test(filename);
    std::cout << "root hash: " << test.root_node_->hash_ << "\n";

    return 0;
}