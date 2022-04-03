#include "caesar_cipher.hpp"

namespace ango
{
    int CaesarCipher::Encrypt(std::string& plain_text, uint8_t key) {
        if (key % 256 == 0) {
            return 0;
        }
        char k = static_cast<char>(key);
        int i = 0;
        int p_len = plain_text.length();
        while (i < p_len) {
            plain_text[i++] += k;
        }

        return i;
    }

    int CaesarCipher::Decrypt(std::string& cipher_text, uint8_t key) {
        if (key % 256 == 0) {
            return 0;
        }
        char k = static_cast<char>(key);
        int i = 0;
        int c_len = cipher_text.length();
        while (i < c_len) {
            cipher_text[i++] += k;
        }

        return i;
    }
    
}
