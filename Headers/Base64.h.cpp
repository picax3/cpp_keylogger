#ifndef BASE64_H
#define BASE64_H

#include <cstdint>
#include <cstring>
#include <array>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <sstream>
#include <iostream>
//#include <openssl/sha.h>

namespace Base64
{
    // encoding function prototype
    std::string base64_encode(const std::string &);
    /* create 3 salts
    const std::string &SALT1 = "LM::TB::BB";
    const std::string &SALT2 = "_:/_77";
    const std::string &SALT3 = "line=wowC++"; */
    // function to generate a secure random salt
    std::string generate_salt(size_t length) {
        const std::string chars="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
        std::string salt;
        std::random_device rd;
        std::mt19937 generator(rd()); // seed the generator.  Mersenne Twister pseudo-random number generator. from <random> library
        // encrypt func with more complex salts
        std::uniform_int_distribution<> distribution(0, chars.size() - 1);
        for (size_t i = 0; i < length; ++i) {
            salt += chars[distribution(generator)];
            }
            return salt;
        }

/* if target machine has no openssl/sha installed -> wont work 
        // func to compute SHA-256 hash
        std::string sha256(const std::string &data) {
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256((unsigned char*)data.c_str(), data.size(), hash);
            std::stringstream ss;
            for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
                ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
                // std::hex converts int to hexadecimal 255 to ff
                // std:setw(2) set width to output to at least 2 char, if shorter -> padded
                // setfill(0) set char for padding. 0 instead of empty spaces ' '
            }
        } */

    std::string EncryptB64(std::string s) {
        // generating dynamic salts
        std::string salt1 = generate_salt(12); //gen 12 char salt
        std::string salt2 = generate_salt(10);
        std::string salt3 = generate_salt(15);
        // build the string with salts
        s = base64_encode(s  + salt2 + salt3 + salt1);
        s = base64_encode(s);
        // add under salt
        s.insert(7, salt3);
        s += salt1;
        s = base64_encode(s);
        s = salt2 + salt3 + salt1;
        s = base64_encode(s);
        s.insert(1, "L");
        s.insert(7, "M");
        return s; 
        }

        static const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        std::string base64_encode (const std::string &s) // const reference to a string. parameter passed to a function
        {
            std::string ret; // output string. fill it with encoded char characters
            int val = 0;
            // standard way of encrypting base64
            int bits = -6; // number of bits in a sub group. groups of 6
            const unsigned int b63 = 0x3F; // 63 = 3F, 0x says its a hexidecimal
            // for each loop. itirate thru string s.
            for(const auto &c : s) // use auto when u dont know the type of variable. c will b assigned every character from s tring
            {
                val = (val << 8) + c; // resulting numbers are shifted left by 8 places
                // val = val * 2^8 // statemen is the same
                bits += 8; // base64 works with octates when working with string
                while(bits >= 0)
                {
                    ret.push_back(BASE64_CODES[(val >> bits) & 63]);
                    bits -= 6; // decreasing number of bits by six. 
                }  
            }
        
            if (bits > -6) {// if one character inserted
                ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);
                // if ret size not aligned we have padding
            }

            while(ret.size() % 4) {
                ret.push_back('=');
            }

            return ret;
        }
}
#endif
// BASE64 algorithm research transfer bytes to string
// 64 characters 62 and 63 plus and slash starts with 0 padding sign equal transferred via email w/out losing data
// for <openssl/sha.h> use MSYS2 pacman -S mingw-w64-x86_64-openssl
