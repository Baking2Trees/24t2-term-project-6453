#ifndef FILE_VERSIONING_H
#define FILE_VERSIONING_H

#include <string>
#include <vector>
#include "merkle.h"

class FileVersioning {
public:
    FileVersioning(const std::string& directory);
    void createNewVersion(const std::string& filename);
    std::vector<std::string> listVersions(const std::string& filename);
    std::string getVersion(const std::string& filename, int versionNumber);
    void restoreVersion(const std::string& filename, int versionNumber);
    bool verifyVersionIntegrity(const std::string& filename, int versionNumber);

private:
    std::string versioningDirectory;
    std::string getVersionFilename(const std::string& filename, int versionNumber);
    int getLatestVersionNumber(const std::string& filename);
    std::string generateHash(const std::string& filename);
    merkle_tree generateMerkleTree(const std::string& filename);
};

#endif // FILE_VERSIONING_H
