#ifndef AUTH_MANAGEMENT_H
#define AUTH_MANAGEMENT_H

#include <string>
#include <vector>
#include "merkle.h"

class AuthManagement {
public:
    AuthManagement(const std::string& user_file);
    
    void addUser(const std::string& user);
    void removeUser(const std::string& user);
    void updateUserPermissions(const std::vector<std::pair<std::string, std::string>>& user_permissions);
    std::vector<std::string> listUsers() const;

private:
    merkle_tree merkle_tree_; 
    std::string user_file_;   
    std::vector<std::string> users_;
    
    void updateMerkleTree();
    std::vector<std::string> getUserList() const;
};

#endif // AUTH_MANAGEMENT_H
