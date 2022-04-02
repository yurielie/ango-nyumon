#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <boost/format.hpp>

#include "cryptgraphy/caesar_cipher.hpp"
#include "cryptgraphy/simple_substitution_cipher.hpp"

bool execCaesarCipher(char* argv[], std::string message) {
    uint8_t key = std::stoi(argv[3]);
    std::cout << "*** Caesar Cipher ***" << std::endl;

    int m_len = message.length();
    std::cout << "Plain Text: '" << message << "'" << std::endl;
    
    int encrypted = ango::CaesarCipher::Encrypt(message, key);
    if (encrypted < m_len) {
        std::cout << boost::format("failed to encrypt %s at index %d") % message % encrypted << std::endl;
        return false;
    }
    std::cout << "Cipher Text: '" << message << "'" << std::endl;

    int decrypted = ango::CaesarCipher::Decrypt(message, -key);
    if (decrypted < m_len) {
        std::cout << boost::format("failed to decrypt %s at index %d") % message % decrypted << std::endl;
        return false;
    }
    std::cout << "Plain Text: '" << message << "'" << std::endl;

    return true;
}

bool execSimpleSubstitutionCipher(char* argv[], std::string message) {
    std::vector<char> charset = {};
    for (int i = 0; i < 26; ++i) {
        charset.push_back('a' + i);
        charset.push_back('A' + i);
    }
    std::vector<char> substitution = std::vector{charset};

    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(substitution.begin(), substitution.end(), engine);

    using substitutionTable = boost::bimaps::bimap<char, char>;
    using substitutionValue = substitutionTable::value_type;

    substitutionTable sm;
    for (auto it = charset.begin(), it2 = substitution.begin(); it != charset.end() || it2 != substitution.end(); ++it, ++it2) {
        sm.insert(substitutionValue{*it, *it2});
    }

    std::cout << "*** Randomly Generated Substitution Table ***" << std::endl;
    for (auto it = sm.left.begin(); it != sm.left.end(); ++it) {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < sm.size(); ++i) {
        std::cout << "| ";
    }
    std::cout << std::endl;
    for (int i = 0; i < sm.size(); ++i) {
        std::cout << "V ";
    }
    std::cout << std::endl;
    for (auto it = sm.left.begin(); it != sm.left.end(); ++it) {
        std::cout << it->second << " ";
    }
    std::cout << std::endl << std::endl;


    int m_len = message.length();
    std::cout << "Plain Text: '" << message << "'" << std::endl;
    
    int encrypted = ango::SimpleSubstitutionCipher::Encrypt(message, sm);
    if (encrypted < m_len) {
        std::cout << boost::format("failed to encrypt %s at index %d") % message % encrypted << std::endl;
        return false;
    }
    std::cout << "Cipher Text: '" << message << "'" << std::endl;

    int decrypted = ango::SimpleSubstitutionCipher::Decrypt(message, sm);
    if (decrypted < m_len) {
        std::cout << boost::format("failed to decrypt %s at index %d") % message % decrypted << std::endl;
        return false;
    }
    std::cout << "Plain Text: '" << message << "'" << std::endl;

    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "too few argument. required 3 args at least." << std::endl;
    }

    std::string crypt_type = std::string(argv[1]);
    std::string plain_text = std::string(argv[2]);
    bool result = false;
    if (crypt_type == "caesar") {
        result = execCaesarCipher(argv, plain_text);
    } else if (crypt_type == "simpleSubstitution") {
        result = execSimpleSubstitutionCipher(argv, plain_text);
    }

    if (result == false) {
        return 1;
    }

    return 0;
}

