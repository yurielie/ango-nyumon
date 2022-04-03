#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <boost/format.hpp>
#include <boost/program_options.hpp>

#include "cryptgraphy/caesar_cipher.hpp"
#include "cryptgraphy/simple_substitution_cipher.hpp"


bool execCaesarCipher(uint8_t key, std::string message) {
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

bool execSimpleSubstitutionCipher(std::string message) {
    std::vector<char> charset = {};
    for (uint8_t i = 32; i < 127; ++i) {
        charset.push_back(static_cast<char>(i));
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
    int sm_size = sm.size();
    std::cout << std::endl;
    for (int i = 0; i < sm_size; ++i) {
        std::cout << "| ";
    }
    std::cout << std::endl;
    for (int i = 0; i < sm_size; ++i) {
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

    boost::program_options::options_description opt("Ango");
    opt.add_options()
        ("algo,a", boost::program_options::value<std::string>(), "algorithm to en/decrypt")
        ("text,t", boost::program_options::value<std::string>(), "text to en/decrypt")
        ("help,h", "help");
    
    boost::program_options::variables_map vm;
    boost::program_options::parsed_options parse_result = boost::program_options::parse_command_line(argc, argv, opt);
    try {
        boost::program_options::store(parse_result, vm);
    } catch (std::exception &e) {
        std::cerr << "invalid argument: " << e.what() << std::endl << opt << std::endl;
        return 1;
    }
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << opt << std::endl;
        return 1;
    } else if (!vm.count("algo") || !vm.count("text")) {
        std::cout << "required '--algo' and '--text' option to be select." << std::endl;
        return 1;
    }

    std::vector<std::string> args = {};
    for (auto const& s : boost::program_options::collect_unrecognized(parse_result.options, boost::program_options::include_positional)) {
        args.push_back(s);
    }

    std::string crypt_type = vm["algo"].as<std::string>();
    std::string plain_text = vm["text"].as<std::string>();
    bool result = false;
    if (crypt_type == "caesar") {
        uint8_t key = std::stoi(args[0]);
        result = execCaesarCipher(key, plain_text);
    } else if (crypt_type == "simpleSubstitution") {
        result = execSimpleSubstitutionCipher(plain_text);
    }

    if (result == false) {
        return 1;
    }

    return 0;
}

