#include <iostream>
#include <cstring> // For std::strcpy
#include "sha256.h"
#include "merkle.h"
#include "upload.h"
#include "copy_file.h"
#include "delete_file.h"

void createMerkleTree(const std::string& filename);
void copyFile(const std::string& sourceFile, const std::string& destinationFile);
void deleteFile(const std::string& filename);
void uploadFile(const std::string& sourceFile, const std::string& destinationFile);

int main() {
    try {
        while (true) {
            std::cout << "\nChoose an operation:\n";
            std::cout << "1. Upload a file\n";
            std::cout << "2. Create the Merkle tree\n";
            std::cout << "3. Copy a file\n";
            std::cout << "4. Delete a file\n";
            std::cout << "5. Exit\n";
            std::cout << "Enter your choice (1-5): ";

            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Clear the newline character from the input buffer

            switch (choice) {
                case 1: {
                    // Upload a file
                    /*
                    std::string uploadDirectory = "uploaded_files"; // set directory
                    MerkleTreeManager manager(uploadDirectory);

                    // upload and build merkle tree
                    std::string fileToUpload = "exampletexts/t8.shakespeare.txt";
                    manager.processFile(fileToUpload);
                    */
                    break;
                }

                case 2: {
                    // Create the Merkle tree for a test file
                    std::string fileForTree = "exampletexts/t8.shakespeare.txt";
                    createMerkleTree(fileForTree);
                    break;
                }

                case 3: {
                    // Copy the file and update the Merkle tree
                    std::string fileToCopy = "exampletexts/t8.shakespeare.txt";
                    std::string destinationFile = "exampletexts/t8.shakespeare copy.txt";
                    copyFile(fileToCopy, destinationFile);
                    break;
                }

                case 4: {
                    // Delete the file and update the Merkle tree
                    std::string fileToDelete = "exampletexts/t8.shakespeare.txt";
                    deleteFile(fileToDelete);
                    break;
                }

                case 5: {
                    std::cout << "Exiting program.\n";
                    return 0; // Exit the program
                }

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break; // Return to the menu
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