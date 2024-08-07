#include "comparison.h"
#include <vector>
#include <iostream>

void analyse_changes(std::shared_ptr<merkle_node> cloud_mt, std::shared_ptr<merkle_node> local_mt, std::vector<int>& blocks) {
    // If the node hashes are equal we want do to nothing as means all children nodes are correct
    // If not equal
        // If cloud node and local node not at chilren - search children
        // If cloud node is at children but local node is not - add all children of local node (deletion)
        // If local at children and cloud node is not - add all children of cloud node
    if (cloud_mt == nullptr || local_mt == nullptr) {
        if (cloud_mt == nullptr && local_mt == nullptr) return;
        // If cloud is empty but local is not - > add all children of local
        if (cloud_mt == nullptr) {
            for (int i = local_mt->leftmost_block_; i <= local_mt->rightmost_block_; i++) {
                blocks.push_back(i);
            }
        }

        // If local is empty but cloud is not - > add all children of cloud
        if (local_mt == nullptr) {
            for (int i = cloud_mt->leftmost_block_; i <= cloud_mt->rightmost_block_; i++) {
                blocks.push_back(i);
            }
        }
    } else if (cloud_mt->hash_ != local_mt->hash_) {
        // std::cout << "Currently comparing: " << cloud_mt->hash_ << " to " << local_mt->hash_ << "\n";

        // Would be indicate of a minor change
        if (
            cloud_mt->left_child_ == nullptr &&
            cloud_mt->right_child_ == nullptr &&
            local_mt->left_child_ == nullptr &&
            local_mt->left_child_ == nullptr
        ) {
            blocks.push_back(cloud_mt->rightmost_block_);
        }
        // Analyse children
        analyse_changes(cloud_mt->left_child_, local_mt->left_child_, blocks);
        analyse_changes(cloud_mt->right_child_, local_mt->right_child_, blocks);
    }

    // Otherwise do nothing
}

std::vector<int> comparison(merkle_tree cloud_file_mt, const char *filename) {
    merkle_tree local_file_mt = merkle_tree(filename);
    std::vector<int> needed_blocks;

    // Analyse changes
    analyse_changes(cloud_file_mt.root_node_, local_file_mt.root_node_, needed_blocks);

    // Remove duplicates
    // Sort
    std::sort(needed_blocks.begin(), needed_blocks.end());
    // Remove duplicates
    auto it = std::unique(needed_blocks.begin(), needed_blocks.end());
    // Erase
    needed_blocks.erase(it, needed_blocks.end());

    return needed_blocks;
}