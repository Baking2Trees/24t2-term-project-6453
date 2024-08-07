#ifndef MERKLE_H
#define MERKLE_H

#include <string>
#include "sha256.h"

class merkle_node {
 public:
    // Class attributes
    std::string hash_;
    std::shared_ptr<merkle_node> left_child_;
    std::shared_ptr<merkle_node> right_child_;
    int leftmost_block_;
    int rightmost_block_;
    
    // Childnode
    merkle_node(std::string hash, int block_number)
    : hash_(hash)
    , left_child_(nullptr)
    , right_child_(nullptr)
    , leftmost_block_(block_number)
    , rightmost_block_(block_number){};

    // Merging of two childnodes
    merkle_node(std::shared_ptr<merkle_node> left_child, std::shared_ptr<merkle_node> right_child)
    : hash_(merkle_node_sha256_hash(left_child->hash_, right_child->hash_))
    , left_child_(left_child)
    , right_child_(right_child)
    , leftmost_block_(left_child->leftmost_block_)
    , rightmost_block_(right_child->rightmost_block_){};
};

class merkle_tree { 
 public:
    // Only valid constructor - creates a merkle tree with a given filename
    merkle_tree(const char *filename);

    std::shared_ptr<merkle_node> root_node_;
};


#endif // MERKLE_H