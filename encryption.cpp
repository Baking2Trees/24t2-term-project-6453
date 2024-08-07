#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// Function to load RSA public key from a PEM-formatted string
RSA* load_public_key(const std::string& public_key_str) {
    RSA* rsa = nullptr;
    BIO* bio = BIO_new_mem_buf(public_key_str.data(), public_key_str.size());
    if (bio == nullptr) {
        std::cerr << "Error creating BIO object\n";
        return nullptr;
    }

    rsa = PEM_read_bio_RSA_PUBKEY(bio, &rsa, nullptr, nullptr);
    if (rsa == nullptr) {
        std::cerr << "Error loading public key\n";
    }

    BIO_free(bio);
    return rsa;
}

// Function to encrypt data using RSA public key
std::string encrypt_data(RSA* rsa, const std::string& data) {
    // Determine the maximum size of the data that can be encrypted
    int rsa_size = RSA_size(rsa);
    int padding = RSA_PKCS1_OAEP_PADDING; // Use PKCS#1 OAEP padding
    int encrypted_size = rsa_size;
    std::vector<unsigned char> encrypted_data(encrypted_size);

    // Encrypt the data
    int result = RSA_public_encrypt(data.size(), 
                                   reinterpret_cast<const unsigned char*>(data.c_str()), 
                                   encrypted_data.data(), 
                                   rsa, 
                                   padding);
    
    if (result == -1) {
        char err[130];
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), err);
        std::cerr << "Encryption error: " << err << "\n";
        return "";
    }

    // Resize the vector to the actual encrypted size
    encrypted_data.resize(result);
    return std::string(encrypted_data.begin(), encrypted_data.end());
}
// Function to load RSA private key from a PEM-formatted string
RSA* load_private_key(const std::string& private_key_str) {
    RSA* rsa = nullptr;
    BIO* bio = BIO_new_mem_buf(private_key_str.data(), private_key_str.size());
    if (bio == nullptr) {
        std::cerr << "Error creating BIO object\n";
        return nullptr;
    }

    rsa = PEM_read_bio_RSAPrivateKey(bio, &rsa, nullptr, nullptr);
    if (rsa == nullptr) {
        std::cerr << "Error loading private key\n";
    }

    BIO_free(bio);
    return rsa;
}

// Function to sign data using RSA private key
std::vector<unsigned char> sign_data(RSA* rsa, const std::string& data) {
    std::vector<unsigned char> signature(RSA_size(rsa));
    unsigned int sig_len = 0;

    // Hash the data
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)data.c_str(), data.size(), hash);

    // Sign the hash
    if (RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature.data(), &sig_len, rsa) != 1) {
        char err[130];
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), err);
        std::cerr << "Signing error: " << err << "\n";
        return {};
    }

    signature.resize(sig_len); // Resize to the actual signature size
    return signature;
}

void EncryptAndSend(const std::string& requestedData, 
                    const std::string& requesterPublicKey, 
                    const std::string& senderPrivateKey, 
                    const std::string& encryptedDataFilename, 
                    const std::string& signatureFilename) {
    // Load the requester's public key
    RSA* rsa_public = load_public_key(requesterPublicKey);
    if (rsa_public == nullptr) {
        std::cerr << "Failed to load public key\n";
        return;
    }

    // Encrypt the requested data
    std::string encryptedData = encrypt_data(rsa_public, requestedData);
    if (encryptedData.empty()) {
        std::cerr << "Failed to encrypt data\n";
        RSA_free(rsa_public);
        return;
    }

    // Load the sender's private key
    RSA* rsa_private = load_private_key(senderPrivateKey);
    if (rsa_private == nullptr) {
        std::cerr << "Failed to load private key\n";
        RSA_free(rsa_public);
        return;
    }

    // Sign the encrypted data
    std::vector<unsigned char> senderSignature = sign_data(rsa_private, encryptedData);
    if (senderSignature.empty()) {
        std::cerr << "Failed to sign data\n";
        RSA_free(rsa_public);
        RSA_free(rsa_private);
        return;
    }

    // Write the encrypted data to the file (simulating transmission)
    std::ofstream out(encryptedDataFilename, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file: " << encryptedDataFilename << "\n";
        RSA_free(rsa_public);
        RSA_free(rsa_private);
        return;
    }
    out.write(encryptedData.c_str(), encryptedData.size());
    out.close();

    // Write the signature to a separate file
    std::ofstream sig_out(signatureFilename, std::ios::binary);
    if (!sig_out) {
        std::cerr << "Failed to open signature file: " << signatureFilename << "\n";
        RSA_free(rsa_public);
        RSA_free(rsa_private);
        return;
    }
    sig_out.write(reinterpret_cast<const char*>(senderSignature.data()), senderSignature.size());
    sig_out.close();

    // Clean up
    RSA_free(rsa_public);
    RSA_free(rsa_private);
}
