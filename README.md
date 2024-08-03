# Secure and Efficient File Sharing System Using Merkle Trees

## Project Overview

**COMP6453 Applied Cryptography Term Project**

### Problem Statement

In modern file-sharing systems, users face several challenges including:

- **Ensuring Consistency:** Making sure all users have the most current version of a file.
- **Efficient Data Transfer:** Transferring only necessary changes rather than entire file copies between computers. 
- **Security:** Ensuring that files are shared securely, preventing unauthorized access and maintaining data integrity.

Our project addresses these challenges by simulating a file-sharing system on a local drive. Each directory represents a different user. When a file is altered, a Merkle tree of the file is created and sent to other directories. These directories identify missing parts, request this data, and receive it securely.

### Motivation

With increasing data breaches and integrity concerns, secure file sharing is crucial. This project aims to demonstrate the practical use of Merkle trees to improve file sharing efficiency and security. By simulating this solution locally, we can showcase its efficiency and viability in a cloud-like environment.

This project implements a secure and efficient file-sharing system using Merkle Trees. The goal is to simulate file sharing on a local drive, where directories represent users, and use Merkle Trees to track changes and ensure data integrity. The project involves file operations (addition, deletion, and uploading) and uses cryptographic hashing to ensure consistency and security.

## Current Progress

### Files and Their Functions

- **`main.cpp`**
  - **Function:** Entry point of the program. Creates a Merkle tree for a test file and performs file operations (e.g., deleting a file).
  - **Status:** Basic implementation to test Merkle tree functionality and file deletion.

- **`sha256.cpp` / `sha256.h`**
  - **Function:** Contains implementation and declarations for SHA-256 hashing, used primarily in Merkle tree construction.
  - **Status:** Currently under development. Requires linking with OpenSSL for hashing functions.

- **`merkle.cpp` / `merkle.h`**
  - **Function:** Implements the Merkle Tree data structure. Handles tree construction, hashing, and root hash calculation. You can access fields of the Merkle Tree nodes down to the children for content differences.
  - **Status:** Basic functionality implemented. Further testing and integration required.

- **`comparison.cpp` / `comparison.h`**
  - **Function:** Provides functions to compare Merkle Trees and check for differences.
  - **Status:** Implementation needed to ensure proper comparison of trees.

- **`request.cpp` / `request.h`**
  - **Function:** Manages file requests, including handling missing blocks and reconstructing files.
  - **Status:** Basic functionality implemented. May need enhancements based on further testing.

- **`constants.cpp` / `constants.h`**
  - **Function:** Contains constants used throughout the project.
  - **Status:** Implemented.

- **`delete_file.cpp` / `delete_file.h`**
  - **Function:** Provides functionality to delete files and update the Merkle Tree accordingly.
  - **Status:** Basic implementation completed. Error handling needed.

## To Do

- **File Addition/Upload:**
  - Implement functionality for adding and uploading files.
  - Ensure integration with Merkle Tree to track new files.

- **Enhance Error Handling:**
  - Improve error handling for file operations and network issues.

- **Testing and Validation:**
  - Test all functionalities thoroughly.
  - Ensure that the Merkle Tree correctly tracks changes and verifies data integrity.

- **Security Analysis:**
  - **Authentication and Authorization:** Implement and verify user authentication and access control measures.
  - **Data Integrity:** Ensure that Merkle Trees are correctly implemented and verify data integrity across operations.
  - **Network Security:** Assess and implement security measures for data transmission and network communication.
  - **Encryption & Decryption:** Verify that encryption and decryption processes are secure and correctly implemented.
  - **File Operations:** Validate secure handling of file addition, deletion, and modifications. Ensure proper management of authorized users.
  - **Error Handling:** Implement robust error handling mechanisms to manage and recover from issues related to security operations and maintain overall system reliability.

- **Documentation:**
  - Update the README with more detailed explanations and usage examples (along with newly made progress).
  - Provide examples of how to run and test the application.

- **Additional Features:**
  - Consider adding features such as file versioning, user management, and authentication.

### Functions

- **`Upload(filename)`**
  - Sender generates a Merkle tree of its altered files and sends this to other users on the drive.

- **`RequestBlocks(missingBlocks, senderID)`**
  - Handles the request for missing blocks identified in the comparison phase.

- **`EncryptAndSend(requestedData, requesterPublicKey)`**
  - Verifies the requester is a trusted party, encrypts the required data, and transmits it over a public network.

- **`ReceiveAndDecrypt(encryptedData, senderSignature)`**
  - Verifies the sender is a trusted party, decrypts the data using the receiver's private key.

- **`Download(requestedData, signature)`**
  - Verifies the sender is a trusted party, decrypts the data, and updates the local file with the decrypted data.

- **`ManageAuthorizedUsers(userList)`**
  - Manages and maintains a centralized list of authorized users. Ensures that file access permissions are enforced and updated as necessary.

- **`Network()`**
  - A logic system that integrates the above functionalities, simulating a cloud environment on a local drive.

## Getting Started

### Prerequisites

- Install OpenSSL:
  ```bash
  brew install openssl

### Building the project

1. Clone this repository using (either HTTPS/SSH/CLI):
   ```bash
   // SSH
    git clone https://github.com/Baking2Trees/24t2-term-project-6453.git
   
2. Navigate to the project directory:
    ```bash
    cd <repository-directory>

3. Run make to build the project:
    ```bash
    make

### Running the application

- Execute the following command to run the application:
   ```bash
    ./merkle
