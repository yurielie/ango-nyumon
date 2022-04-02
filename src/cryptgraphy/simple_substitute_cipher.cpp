#include "simple_substitution_cipher.hpp"

namespace ango {
    
    int SimpleSubstitutionCipher::Encrypt(std::string &plain_text, const boost::bimaps::bimap<char, char> &substituttion_table) {
        int i = 0;
        while (i < plain_text.length()) {
            auto it = substituttion_table.left.find(plain_text[i]);
            if (it != substituttion_table.left.end()) {
                plain_text[i] = it->second;
            } else {
                return i;
            }
            i++;
        }

        return i;
    }

    int SimpleSubstitutionCipher::Decrypt(std::string &cipher_text, const boost::bimaps::bimap<char, char> &substituttion_table) {
        int i = 0;
        while (i < cipher_text.length()) {
            auto it = substituttion_table.right.find(cipher_text[i]);
            if (it != substituttion_table.right.end()) {
                cipher_text[i] = it->second;
            } else {
                return i;
            }
            i++;
        }
        
        return i;
    }
}