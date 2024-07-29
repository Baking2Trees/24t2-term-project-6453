#ifndef MERKLE_H
#define MERKLE_H

#include <string>

class merkle_node {

};

class merkle_tree { 
    // Only valid constructor - creates a merkle tree with a given filename
    explicit merkle_tree(char *filename);

    std::string root_hash;
};


#endif // MERKLE_H