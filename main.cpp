#include <iostream>
#include "sha256.h"
#include "merkle.h"
#include "delete_file.h"
#include "upload.h"
#include "download.h"

int main() {
    try {
        // initial
        std::string uploadDirectory = "uploaded_files";
        MerkleTreeManager uploadManager(uploadDirectory);
        Downloader downloader;

        while (true) {
            std::cout << "\nChoose an operation:\n";
            std::cout << "1. Upload a file\n";
            std::cout << "2. Create the merkle tree\n";
            std::cout << "3. Copy a file\n";
            std::cout << "4. Delete a file\n";
            std::cout << "5. Exit\n";
            std::cout << "Enter your choice (1-4): ";

            int choice;
            std::cin >> choice;


            switch (choice) {

            case 1: {
                //upload file

                std::string uploadDirectory = "uploaded_files"; // set directory
                MerkleTreeManager manager(uploadDirectory);

                // upload and build merkle tree
                std::string fileToUpload = "exampletexts/t8.shakespeare.txt";
                manager.processFile(fileToUpload);
                break;
            }

            case 2: {
                // Create the merkle tree for a test file
                char fileForTree[] = "exampletexts/t8.shakespeare.txt";
                merkle_tree test(fileForTree);
                std::cout << "root hash: " << test.root_node_->hash_ << "\n";
                break;
            }

            case 3: {
                // Copy the file and update the Merkle tree
                std::string fileToCopy = "exampletexts/t8.shakespeare.txt";
                std::string destinationFile = "exampletexts/t8.shakespeare copy.txt";
                std::string result = copy_file(fileToCopy, destinationFile);
                
                if (!result.empty()) {
                    std::cerr << result << std::endl;
                } else {
                    std::cout << "File copied successfully to " << destinationFile << "\n";
                    // Update or rebuild Merkle tree as needed
                    uploadManager.processFile(destinationFile);
                }
                break;
            }

            case 4: {
                // Delete the file and update the Merkle tree
                std::string fileToDelete = "exampletexts/t8.shakespeare.txt";
                std::string result = delete_file(fileToDelete);
                
                if (!result.empty()) {
                    std::cerr << result << std::endl;
                } else {
                    std::cout << "File deleted successfully.\n";
                    // Remove the file's contribution for the Merkle tree
                }
                break;
            }

            case 5: {
                std::cout << "Exiting program.\n";
                return 0;
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }

        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in main: " << e.what() << std::endl;
    }

    return 0;
}
