#pragma once

#include <string>
#include <vector>
#include <boost/bimap/bimap.hpp>

namespace ango {
    class SimpleSubstitutionCipher {
        public:
        static int Encrypt(std::string &plain_text, const boost::bimaps::bimap<char, char> &substituttion_table);
        static int Decrypt(std::string &cipher_text, const boost::bimaps::bimap<char, char> &substituttion_table);
    };
}