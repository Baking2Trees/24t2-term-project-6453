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

void createMerkleTree(const std::string& filename);
void copyFile(const std::string& sourceFile, const std::string& destinationFile);
void deleteFile(const std::string& filename);
void uploadFile(const std::string& sourceFile, const std::string& destinationFile);

int main() {
    try {
        while (true) {
            const char *users[] = {"Alice", "Bob", "Charlie"};
            
            std::cout << "Choose a user:\n";
            std::cout << "1. Alice\n";
            std::cout << "2. Bob\n";
            std::cout << "3. Charlie\n";
            std::cout << "User number: ";

            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Clear the newline character from the input buffer

            int user_num = choice - 1;
            std::string user = std::string{users[user_num]};
            

            std::cout << "\nChoose an operation:\n";
            std::cout << "1. Add a new file (this will create an empty file in the users drive)\n";
            std::cout << "2. Upload changes you have made (note here you should have already made changes to the file in the users directory)\n";
            std::cout << "3. Remove a file from all directories\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter your choice (0-4): ";

            std::cin >> choice;
            std::cin.ignore(); // Clear the newline character from the input buffer

            switch(user_num) {
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
                            std::vector<int> missing_blocks = comparison(altered_file_mt, user_specific_filename.c_str());
                            std::string transfer_file = request_blocks(missing_blocks, updated_file_user_filename.c_str());

                            // Encryption

                            // Decryption

                            // Construction
                            reconstruct(transfer_file.c_str(), user_specific_filename.c_str());
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

            // switch (choice) {
            //     case 1: {
            //         // Upload a file
            //         /*
            //         std::string uploadDirectory = "uploaded_files"; // set directory
            //         MerkleTreeManager manager(uploadDirectory);

            //         // upload and build merkle tree
            //         std::string fileToUpload = "exampletexts/t8.shakespeare.txt";
            //         manager.processFile(fileToUpload);
            //         */
            //         break;
            //     }

            //     case 2: {
            //         // Create the Merkle tree for a test file
            //         std::string fileForTree = "exampletexts/t8.shakespeare.txt";
            //         createMerkleTree(fileForTree);
            //         break;
            //     }

            //     case 3: {
            //         // Copy the file and update the Merkle tree
            //         std::string fileToCopy = "exampletexts/t8.shakespeare.txt";
            //         std::string destinationFile = "exampletexts/t8.shakespeare copy.txt";
            //         copyFile(fileToCopy, destinationFile);
            //         break;
            //     }

            //     case 4: {
            //         // Delete the file and update the Merkle tree
            //         std::string fileToDelete = "exampletexts/t8.shakespeare.txt";
            //         deleteFile(fileToDelete);
            //         break;
            //     }

            //     case 0: {
            //         std::cout << "Exiting program.\n";
            //         return 0; // Exit the program
            //     }

            //     default:
            //         std::cout << "Invalid choice. Please try again.\n";
            //         break; // Return to the menu
            // }
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