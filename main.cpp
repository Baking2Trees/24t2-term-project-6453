#include <iostream>
#include "sha256.h"
#include "merkle.h"
#include "copy_file.h" 
#include "delete_file.h"
#include "upload.h"
#include "download.h"

int main() {
    try {
        // Set up file paths and directories
        const std::string uploadDirectory = "uploaded_files";
        const std::string privateKeyPath = "path/to/private/key.pem";
        const std::string publicKeyPath = "path/to/public/key.pem";
        const std::string testFilePath = "exampletexts/t8.shakespeare.txt";

        // Initialize the FileUploader
        FileUploader uploader(uploadDirectory, privateKeyPath, publicKeyPath);
    
        while (true) {
            std::cout << "\nChoose an operation:\n";
            std::cout << "1. Upload a file\n";
            std::cout << "2. Create the merkle tree\n";
            std::cout << "3. Copy a file\n";
            std::cout << "4. Delete a file\n";
            std::cout << "5. Exit\n";
            std::cout << "Enter your choice (1-5): ";

            int choice;
            std::cin >> choice;
            std::cin.ignore(); // To clear the newline character from the input buffer

            switch (choice) {
                case 1: {
                    // Upload file
                    std::string fileToUpload = "exampletexts/t8.shakespeare.txt";
                    if (uploader.uploadFile(fileToUpload)) {
                        std::cout << "File uploaded successfully.\n";
                        // You may want to rebuild or update the Merkle tree here
                    }
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
