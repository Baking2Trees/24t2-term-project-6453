#include "constants.h"

std::string request_blocks_file_name(std::vector<int> missing_blocks, const char *filename) {
    std::string return_string = std::string{"requestForBlocks"};
    // for (int i = 0; i < missing_blocks.size(); i++) {
    //     return_string += missing_blocks[i];
    // }
    return_string = return_string + "ForFile" + filename;
    return_string.erase(std::remove(return_string.begin(), return_string.end(), '/'), return_string.end()); // removes any /'s
    return return_string;
}
