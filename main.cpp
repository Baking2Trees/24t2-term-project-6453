#include <iostream>
#include "sha256.h"
#include "merkle.h"
#include "delete_file.h"

int main() {
    // Create the merkle tree for a test file
    char fileForTree[] = "exampletexts/t8.shakespeare.txt";
    merkle_tree test(fileForTree);
    std::cout << "root hash: " << test.root_node_->hash_ << "\n";

    // Delete the file and update the Merkle tree
    std::string fileToDelete = "example_file.txt";
    deleteFile(fileToDelete);

    return 0;
}
