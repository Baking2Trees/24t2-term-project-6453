#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "merkle.h"
#include "constants.h"

merkle_tree::merkle_tree(char* filename) {
    FILE* file = std::fopen(filename, "rb");
    if (!file) {
        std::cerr << "Could not open the file.\n";
        std::exit(1);
    }
    
    // // Move file pointer to store files size
    // std::fseek(file, 0, SEEK_END);
    // long file_size = std::ftell(file);
    // std::fseek(file, 0, SEEK_SET); // Dont need this atm

    unsigned char data[BLOCK_SIZE];

    // Construct all child nodes
    std::vector<std::shared_ptr<merkle_node>> nodes;
    int bytes_read;
    int block_number = 0;
    while ((bytes_read = fread(data, 1, BLOCK_SIZE, file)) != 0) {
        std::string hash = SHA256_hash_as_string(data, bytes_read);
        
        // New shared pointer to child node
        std::shared_ptr<merkle_node> new_child(new merkle_node(hash, block_number));
        nodes.push_back(new_child);
        block_number++;
    }

    // Merge to root
    while (nodes.size() != 1) {
        // Merge in pairs first
        int i = 0;
        std::vector<std::shared_ptr<merkle_node>> tmp;
        while (i + 1 < nodes.size()) {
            // New node
            std::shared_ptr<merkle_node> new_node(new merkle_node(nodes[i], nodes[i + 1]));
            tmp.push_back(new_node);

            i = i + 2;
        }

        // Merge last if present
        if (nodes.size() % 2 != 0) {
            tmp.push_back(nodes[i]);
        }

        nodes = tmp;
    }

    this->root_node_ = nodes[0];
}