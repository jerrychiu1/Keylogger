#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string &SALT1 = "LM::TB::BB";
const std::string &SALT2 = "__:/__77";
const std::string &SALT3 = "line=wowC++";
const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string base64_decode(const std::string &s);
std::string DecryptB64(std::string s);

int main(int argc, char *argv[])
{
    // Check if there are parameters in command line
    if(argc != 3)
        return std::cout << "Program needs TWO arguments!" << std::endl, 2;  //Print out error code 2

    // Set up string 'in' to be argv[1] and string 'out' to be argv[2]
    std::string in (argv[1]), out (argv[2]);
    std::ifstream fi (in);       // File stream string 'in' into variable 'fi'

    // Check if 'fi' is null, then return error message if true
    if(!fi)
        return std::cout << "Cannot read input file '" << in << "'" << std::endl, 3; //Print out error code 3

    std::string data;
    fi >> data;         // Set file input of 'fi' into string 'data'

    // Check if 'fi' is null again, then return error message if true
    if(!fi)
        return std::cout << "Input file '" << in << "' corrupted!" << std::endl, 4; //Print out error code 4

    // Pass in the data to DecryptB64 function, and return the decrypted strings back into 'data'
    data = DecryptB64("XLzovXzMc3bGluZT13b3dDKytMTTo6VEI6OkJC");
    std::cout << data << std::endl;
    std::ofstream fo (out);

    // Check if the file output is null, then if true return error message
    if(!fo)
        return std::cout << "Cannot write output file '" << out << "'" << std::endl, 5; //Print out error code 5
    fo << data;         // Set 'data' into the output file 'fo'

    std::cout << "Decoding was successful" << std::endl;

    return 0;
}

/* Input: string
 * Output: string
 * Takes in a reference string and decodes the string with the base64 algorithm.
 */

std::string base64_decode(const std::string &s)
    {
        std::string ret;
        std::vector<int> vec(256, -1);
        for (int i = 0; i < 64; i++)
            vec [BASE64_CODES[i]] = i;
        int val = 0, bits = -8;
        for (const auto &c : s)
            {
                if (vec[c] == -1) break;
                val = (val << 6) + vec[c];
                bits += 6;

                if (bits >= 0)
                    {

                        ret.push_back(char((val >> bits) & 0xFF));
                        bits -= 8;
                    }
            }

        return ret;
    }

/* Input: string
 * Output: string
 * Takes in a string as a parameter and decrypts the string in base64
 * and returns the decrypted string back
 */
std::string DecryptB64 (std::string s)
{
        s = s.erase (7, 1);
        s = s.erase (1, 1);
        s = base64_decode (s);
        s = s.substr (SALT2.length() + SALT3.length());
        s = s.substr (0, s.length() - SALT1.length());
        s = base64_decode (s);
        s = s.substr (0, s.length() - SALT1.length());
        s = s.erase (7, SALT3.length());
        s = base64_decode (s);
        s = s.substr (SALT1.length());
        s = s.substr (0, s.length() - SALT2.length() - SALT3.length());
        return s;
}
