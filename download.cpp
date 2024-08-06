#include "download.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstring>

FileDownloader::FileDownloader(const std::string& cloudDir, const std::string& localDir, const std::string& logFilePath)
    : cloudDirectory(cloudDir), localDirectory(localDir) {
    logger = std::make_unique<Logger>(logFilePath);
}

FileDownloader::~FileDownloader() {}

void FileDownloader::initializeLogFile(const std::string& logFilePath) {
    std::ofstream logFile(logFilePath);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to initialize log file: " + logFilePath);
    }
    logFile << "Log file initialized" << std::endl;
    logFile.close();
}

bool FileDownloader::downloadFile(const std::string& filename, const std::string& username) {
    logger->log(username, filename, "Starting download");

    if (!fetchFileFromCloud(filename)) {
        logger->log(username, filename, "Failed to fetch file from cloud");
        std::cerr << "Failed to fetch file from cloud: " << filename << std::endl;
        return false;
    }

    if (!verifyFileIntegrity(filename)) {
        logger->log(username, filename, "File integrity check failed");
        std::cerr << "File integrity check failed: " << filename << std::endl;
        return false;
    }

    logger->log(username, filename, "File downloaded and verified successfully");
    std::cout << "File downloaded and verified successfully: " << filename << std::endl;
    return true;
}

bool FileDownloader::verifyFileIntegrity(const std::string& filename) {
    merkle_tree localTree = generateMerkleTree(localDirectory + "/" + filename);
    merkle_tree cloudTree = generateMerkleTree(cloudDirectory + "/" + filename);

    return localTree.root_node_->hash_ == cloudTree.root_node_->hash_;
}

bool FileDownloader::fetchFileFromCloud(const std::string& filename) {
    std::ifstream cloudFile(cloudDirectory + "/" + filename, std::ios::binary);
    if (!cloudFile) {
        std::cerr << "Failed to open cloud file: " << filename << std::endl;
        return false;
    }

    std::vector<char> fileData((std::istreambuf_iterator<char>(cloudFile)),
        std::istreambuf_iterator<char>());

    return saveFileLocally(filename, fileData);
}

bool FileDownloader::saveFileLocally(const std::string& filename, const std::vector<char>& fileData) {
    std::ofstream localFile(localDirectory + "/" + filename, std::ios::binary);
    if (!localFile) {
        std::cerr << "Failed to create local file: " << filename << std::endl;
        return false;
    }

    localFile.write(fileData.data(), fileData.size());
    return localFile.good();
}

merkle_tree FileDownloader::generateMerkleTree(const std::string& filename) {
    char* cFilename = new char[filename.length() + 1];
    std::strcpy(cFilename, filename.c_str());

    merkle_tree tree(cFilename);

    delete[] cFilename;

    return tree;
}