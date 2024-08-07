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

## Current Progress

### Files and Their Functions

- **`main.cpp`**
  - **Function:** Entry point of the program. Currently utilising a menu feature for implementation testing.
  - **Status:** Basic implementation to test Merkle tree functionality, file copy, and file deletion.

1. **Data Integrity**

  - **`merkle.cpp` / `merkle.h`**
    - **Function:** Constructs a Merkle tree from file data. Handles tree construction, hashing, and root hash calculation. Access fields of the Merkle Tree nodes down to the children for content differences. 
    - **Functions:** 
      - `merkle_tree(filename);`
    - **Status:** Implemented. 

  - **`sha256.cpp` / `sha256.h`**
    - **Function:** Contains implementation and declarations for SHA-256 hashing, used primarily in Merkle tree construction.
    - **Functions:**
      - `compute_SHA256(data, dataLen, hash);`
      - `SHA256_hash_as_string(data, dataLen);`
      - `merkle_node_sha256_hash(hash1, hash2);`
    - **Status:** Implemented. 

  - **`comparison.cpp` / `comparison.h`**
    - **Function:** Includes functions for comparing Merkle trees between a cloud file and a local file and analyzing changes between them.
    - **Functions:**
      - Main function: `comparison(cloud_file_mt, filename);`
      - Helper function: `analyse_changes(cloud_mt, local_mt, blocks);`
    - **Status:** Implemented. 

2. **Authentication & Authorization**

For this section, user files are based on assumptions that:

a) User authorization is required to access and use any of the functions.  
b) All communication channels, file systems, and storage are secure against unauthorized access and tampering.

  - **`auth_management.cpp` / `auth_management.h`**
    - **Function:** Manage a list of authorized users, including adding, removing, and updating user permissions and listing users in the system.
    - **Functions:**
      - `addUser(user)`
      - `removeUser(user)`
      - `updateUserPermissions(userList)`
      - `listUsers()`
    - **Status:** Implementation needed.

  - **`auth.cpp` / `auth.h`**
    - **Function:** Authenticates a user based on provided username and password.
    - **Functions:**
      - `authenticate(username, password)`
    - **Status:** Implementation needed.

  - **`user_management.cpp` / `user_management.h`**
    - **Function:** Manages user data and access controls within the system, including retrieving and updating user information, managing passwords, and listing user roles and their associated permissions.
    - **Functions:**
      - `getUserInfo(userId)`
      - `updateUserInfo(userId, newInfo)`
      - `changePassword(userId, newPassword)`
      - `listUserRoles()`
    - **Status:** Implementation needed.

  - **`file_permissions.cpp` / `file_permissions.h`**
    - **Function:** Sets and checks permissions of a user on a specific file.
    - **Functions:**
      - `setPermission(fileId, userId, permissionLevel)`
      - `checkPermission(fileId, userId)`
    - **Status:** Implementation needed.

3. **File Operations**

  - **`constants.cpp` / `constants.h`**
    - **Function:** Generates a filename for requesting blocks.
    - **Functions:**
      - `request_blocks_file_name(missing_blocks, filename)`
    - **Status:** Implemented. 

  - **`upload.cpp` / `upload.h`**
    - **Function:** Handles file upload operations, ensuring integration with Merkle Tree to track new files.
    - **Functions:**
      - Public Methods:
        - `FileUploader(directory, privateKeyPath, publicKeyPath)`
        - `~FileUploader()`
        - `uploadFile(filePath)`
      - Private Methods:
        - `encryptData(data)`
        - `signData(data)`
        - `getFileName(filePath)`
      - Static Methods:
        - `loadPrivateKey(keyPath)`
        - `loadPublicKey(keyPath)`
    - **Status:** Implemented. 

  - **`download.cpp` / `download.h`**
    - **Function:** Handles file download operations.
    - **Status:** Implemented. 

  - **`copy_file.cpp` / `copy_file.h`**
    - **Function:** Copies the contents of a source file to a destination file.
    - **Functions:**
      - `copyFile(sourceFilename, destinationFilename)`
    - **Status:** Implemented. 
   
  - **`delete_file.cpp` / `delete_file.h`**
    - **Function:** Provides functionality to delete files and update the Merkle Tree accordingly.
    - **Functions:**
      - `deleteFile(filename)`
    - **Status:** Implemented. 

  - **`modify_file.cpp` / `modify_file.h`**
    - **Function:** Modifies an existing file, including potential changes to contents or metadata.
    - **Functions:**
      - `modify(filename)`
    - **Status:** Implementation needed.

  - **`file_versioning.cpp` / `file_versioning.h`**
    - **Function:** Manages file versions.
    - **Functions:**
      - `file_versioning(filename)`
    - **Status:** New feature. Further implementation required.

4. **Encryption & Decryption**

  - **`encryption.cpp` / `encryption.h`**
    - **Function:** Verifies the requester is a trusted party, encrypts the required data, and transmits it over a public network.
    - **Functions:**
      - `load_private_key(private_key_str);`
      - `sign_data(rsa, data);`
      - `EncryptAndSend(requestedData, requesterPublicKey, senderPrivateKey, encryptedDataFilename, signatureFilename);`
    - **Status:** Implemented, not tested.

  - **`decryption.cpp` / `decryption.h`**
    - **Function:** Verifies the sender is a trusted party by verifying signatures to ensure integrity and authenticity, decrypts the data using the receiver's private key.
    - **Functions:**
      - `load_private_key(private_key_str);`
      - `load_encrypted_data(filename);`
      - `verify_signature(data, signature, sender_public_key);`
      - `rsa_decrypt(encrypted_bytes, private_key);`
      - `ReceiveAndDecrypt(encryptedDataFilename, senderSignature, senderPublicKeyStr, receiverPrivateKeyStr, decryptedData);`
    - **Status:** Implemented, not tested.

5. **Network Security** 
  - **`request.cpp` / `request.h`**
    - **Function:** Handles the request for missing data blocks from a cloud file. This file can then be used to reconstruct the data in the local system.
    - **Functions:**
      - `requestblock(missingBlocks, filename)`
    - **Status:** Implemented.

  - **`reconstruction.cpp / reconstruction.h`**
    - **Function:** Manages the downloading of requested data blocks and reconstructs the original file from these blocks. It ensures data integrity and authenticity by verifying the provided signature and properly reconstructing the file from the downloaded blocks.
    - **Functions:**
      - `downloadAndReconstruct(requestedBlocks, signature, filename)`
    - **Status:** Implemented.
   
  - **`network.cpp` / `network.h`**
    - **Function:** Logic system that integrates functionalities, simulating a cloud environment on a local drive and handling network operations such as establishing connections and managing data transfers.
    - **Functions:**
      - `network()`
    - **Status:** Implementation required. Additional components may be required for further details.

6. **Error Handling**
  - **Function:** Error handling should be integrated into all relevant functions, including file operations, network security, and Merkle Tree operations.
  - **Status:** To be implemented across all relevant files.

## To Do

- **Complete Implementation**
  - Refer to the [Code Tracker](https://docs.google.com/spreadsheets/d/1dv-hqRM0pZDpCi_d-IG2j-KdyvS5IpuQRsORF4tX5NY/edit?usp=sharing) for progress details and tasks outlined.

- **Enhance Error Handling**
  - Improve handling for file operations and network issues.

- **Testing and Validation:**
  - Conduct comprehensive testing of all functionalities.
  - Ensure that the Merkle Tree correctly tracks changes and verifies data integrity.

- **Code Styling and Refactoring:**
  - Review and apply consistent coding styles and formatting.
    - Ensure proper use of const.
    - Review error handling methods and return statements.
    - Standardize file and header naming conventions.
  - Enhance comments and documentation within the code.

- **Security Analysis:**
  - **1. Data Integrity:**
    - Ensure that Merkle Trees are correctly implemented and updated to verify data integrity across operations. Any changes to files should be reflected in the corresponding Merkle trees to detect tampering or corruption.
  - **2. Authentication and Authorization:**
    - Implement and verify user authentication and access control measures by ensuring that only authorized users can perform file operations.
  - **3. File Operations:**
    - Validate secure handling of file addition, deletion, and modifications. Ensure proper management of authorized users and update Merkle trees accordingly to maintain data integrity.
  - **4. Encryption & Decryption:**
    - Verify that encryption and decryption processes are secure and correctly implemented.
  - **5. Network Security:**
    - Assess and implement security measures for data transmission and network communication. Ensure that data is protected from interception and tampering during transit.
  - **6. Error Handling:**
    - Implement robust error handling mechanisms to manage and recover from issues related to security operations and maintain overall system reliability. Ensure that any errors in file operations or Merkle tree updates are properly logged and addressed.
   
- **Documentation**
  - Keep the README up-to-date with detailed explanations and usage examples.

- **Additional Features**
  - Consider implementing:
    - File versioning
    - User management
    - Authentication
  - (This is an expansion to our group's original term project abstract)
