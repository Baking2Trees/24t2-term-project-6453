#include <iostream>
#include <cstring> // For std::strcpy
#include "sha256.h"
#include "merkle.h"
#include "upload.h"
#include "copy_file.h"
#include "delete_file.h"
#include <fstream>
#include <cstdio>
#include "comparison.h"
#include "reconstruction.h"
#include "request.h"
#include <filesystem>

void createMerkleTree(const std::string& filename);
void copyFile(const std::string& sourceFile, const std::string& destinationFile);
void deleteFile(const std::string& filename);
void uploadFile(const std::string& sourceFile, const std::string& destinationFile);

int main() {
    try {
        while (true) {
            const char *users[] = {"alice", "bob", "charlie"};
            
            std::cout << "Choose a user:\n";
            std::cout << "1. alice\n";
            std::cout << "2. bob\n";
            std::cout << "3. charlie\n";
            std::cout << "User number: ";

            int user_num;
            std::cin >> user_num;
            std::cin.ignore(); // Clear the newline character from the input buffer

            user_num = user_num - 1;
            std::string user = std::string{users[user_num]};
            

            std::cout << "\nChoose an operation:\n";
            std::cout << "1. Add a new file (this will create an empty file in the users drive)\n";
            std::cout << "2. Upload changes you have made (note here you should have already made changes to the file in the users directory)\n";
            std::cout << "3. Remove a file from all directories\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter your choice (0-3): ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Clear the newline character from the input buffer

            switch(choice) {
                case 1: {
                    std::cout << "new filename: ";
                    std::string filename;
                    std::getline(std::cin, filename);

                    // Create empty file
                    for (int i = 0; i < 3; i++) {
                        std::string full_filename = std::string{users[i]} + std::string{'/'} + std::string{filename};
                        std::ofstream outfile(full_filename);
                        if (!outfile) {
                            std::cerr << "Error: Couldn't create new empty file" << std::endl;
                            std::exit(1);
                        }
                    }
                    break;
                }

                case 2: {
                    std::cout << "File with updated changes (this changes should already have been made): ";
                    std::string filename;
                    std::getline(std::cin, filename);

                    const std::string updated_file_user_filename = std::string{users[user_num]} + std::string{'/'} + std::string{filename};
                    merkle_tree altered_file_mt = merkle_tree(updated_file_user_filename.c_str());

                    for (int i = 0; i < 3; i++) {
                        std::string user_specific_filename = std::string{users[i]} + std::string{'/'} + std::string{filename};
                        if (i != user_num) {
                            // Request for needed data
                            std::vector<int> missing_blocks = comparison(altered_file_mt, user_specific_filename.c_str());
                            std::string transfer_filename = request_blocks(missing_blocks, updated_file_user_filename.c_str());

                            // James this is where need your implemention 
                            //       - purpose is just to demonstrate that we have an encryption and decryption protocol
                            //       - the keys are included in the directories for alice, bob and charlie - see users[i] to see who we are sending too and which keys to use
                            // Encryption

                            // Decryption

                            // Construction
                            reconstruct(transfer_filename.c_str(), user_specific_filename.c_str());
                        }
                    }
                    break;
                }

                case 3: {
                    std::cout << "file to remove: ";
                    std::string filename;
                    std::getline(std::cin, filename);
                    for (int i = 0; i < 3; i++) {
                        std::string full_filename = std::string{users[i]} + std::string{'/'} + std::string{filename};
                        if(std::remove(full_filename.c_str()) != 0) {
                            std::cerr << "Error: Couldn't remove file" << std::endl;
                            std::exit(1);
                        }
                    }

                    break;
                }

                case 0: {
                    return 0;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

void createMerkleTree(const std::string& filename) {
    char fileForTree[256]; // Ensure this is large enough for your filenames
    std::strcpy(fileForTree, filename.c_str());
    merkle_tree test(fileForTree);
    std::cout << "Root hash: " << test.root_node_->hash_ << "\n";
}

void copyFile(const std::string& sourceFile, const std::string& destinationFile) {
    std::string copyResult = copy_file(sourceFile, destinationFile);

    if (!copyResult.empty()) {
        std::cerr << copyResult << std::endl;
    } else {
        std::cout << "File copied successfully to " << destinationFile << "\n";
    }
}

void deleteFile(const std::string& filename) {
    std::string deleteResult = delete_file(filename);

    if (!deleteResult.empty()) {
        std::cerr << deleteResult << std::endl;
    } else {
        std::cout << "File deleted successfully.\n";
    }
}

void uploadFile(const std::string& sourceFile, const std::string& destinationFile) {
    /*
    std::string uploadResult = upload_file(sourceFile, destinationFile);

    if (!uploadResult.empty()) {
        std::cerr << uploadResult << std::endl;
    } else {
        std::cout << "File uploaded successfully to " << destinationFile << "\n";
    }
    */
}