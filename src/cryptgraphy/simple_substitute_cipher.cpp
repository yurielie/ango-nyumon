#include "simple_substitution_cipher.hpp"

namespace ango {
    
    int SimpleSubstitutionCipher::Encrypt(std::string &plain_text, const boost::bimaps::bimap<char, char> &substituttion_table) {
        int i = 0;
        int p_len = plain_text.length();
        while (i < p_len) {
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
        int c_len = cipher_text.length();
        while (i < c_len) {
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