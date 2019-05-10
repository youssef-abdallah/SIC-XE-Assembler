#ifndef UTILITIES_H
#define UTILITIES_H
#include <regex>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Utilities
{
    public:
        Utilities();
        virtual ~Utilities();
        string baseConverter(int base1, int base2, string s1, int len);
        void padTo(std::string &str, const size_t num, const char paddingChar = ' ');
        bool isHexaString(std::string const& s);
        vector<string> tokenize(string s, char delimiter);
        string intToHex(int, int);
        bool matchRegex(string, regex);
        int strToInt(string);
        string intToStr(int);
        string hexDigitToBits(char hexDigit, int len);
        int getTwosComplement(int);
        bool isNumeric(string s);

    protected:

    private:
};

#endif // UTILITIES_H
