#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

#include <vector>
#include <string>

namespace Base64
{
    std::string base64_encode(const std::string &);

    // Encryption/Decryption Keys
    const std::string &SALT1 = "LM::TB::BB";
    const std::string &SALT2 = "_:/_77";
    const std::string &SALT3 = "line=wowC++";

    /* Encryption process; must be reversed exactly to get correct string
     * By adding letters/strings each time, we scramble the base64 encoding
     * to make it extremely difficult for it to be decrypted because
     * there is no way others will know what we added to the original string. */
    std::string EncryptB64 (std::string s)
    {
        s = SALT1 + s + SALT2 + SALT3;
        s = base64_encode (s);
        s.insert (7, SALT3);
        s += SALT1;
        s = base64_encode (s);
        s = SALT2 + SALT3 + s + SALT1;
        s = base64_encode (s);
        s.insert (1, "L");
        s.insert (7, "M");
        return s;
    }

    // These are base64 codes used for encryption with A being 0 and / being 63
    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Base 64 encryption function
    std::string base64_encode(const std::string &s)
    {
        std::string ret;
        int val = 0;
        int bits = -6;
        const unsigned int b63 = 0x3F;

        for(const auto &C : s)
        {
            val = (val << 8) + C;
            bits += 8;
            while(bits >= 0)
            {
                ret.push_back(BASE64_CODES[(val >> bits) & b63]);
                bits -= 6;
            }
        }

        if(bits > -6)
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);

        while(ret.size() % 4)
            ret.push_back('=');

        return ret;
    }
}

#endif // BASE64_H_INCLUDED
