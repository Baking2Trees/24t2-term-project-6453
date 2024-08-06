#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <string>
#include <vector>
#include "merkle.h"
#include "logger.h"

class FileDownloader {
public:
    FileDownloader(const std::string& cloudDirectory, const std::string& localDirectory, const std::string& logFilePath);
    ~FileDownloader();

    bool downloadFile(const std::string& filename, const std::string& username);
    bool verifyFileIntegrity(const std::string& filename);
    static void initializeLogFile(const std::string& logFilePath);

private:
    std::string cloudDirectory;
    std::string localDirectory;
    std::unique_ptr<Logger> logger;

    bool fetchFileFromCloud(const std::string& filename);
    bool saveFileLocally(const std::string& filename, const std::vector<char>& fileData);
    merkle_tree generateMerkleTree(const std::string& filename);
};

#endif // DOWNLOAD_H