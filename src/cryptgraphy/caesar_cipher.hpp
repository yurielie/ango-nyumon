#pragma once

#include <string>

namespace ango {
    class CaesarCipher {
        public:
        static int Encrypt(std::string &plain_text, uint8_t key);
        static int Decrypt(std::string &cipher_text, uint8_t key);
    };

}