#include "Utilities.h"

Utilities::Utilities()
{
    //ctor
}

Utilities::~Utilities()
{
    //dtor
}

string Utilities::baseConverter(int base1, int base2, string s1, int len)
{
    string s2 = "";
    int value = 0;
    for(auto ch:s1)
    {
        value = (base1 * value) + (isalpha(ch) ? (ch - 'A' + 10) : (ch - '0'));
    }
    while(value)
    {
        s2 = static_cast <char> ((value % base2 < 10) ?
                                 (value % base2 + '0') : (value % base2 - 10 + 'A')) + s2;
        value/= base2;
    }
    int resultSize = s2.length();
    for(int i = 0; i < len - resultSize; i++)
    {
        s2 = "0" + s2;
    }
    return s2;
}

string Utilities::intToHex(int integer, int len)
{
    std::stringstream sstream;
    sstream << std::hex << integer;
    string result = sstream.str();
    int resultSize = result.length();
    for(int i = 0; i < len - resultSize; i++)
    {
        result = "0" + result;
    }
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool Utilities::matchRegex(string s, regex re)
{
    return regex_match(s, re);
}


bool Utilities::isNumeric(string s){
    bool ans = true;
    for (int i = 0; i < (int) s.length(); i++){
        if(s[i] >= '0' && s[i] <= '9'){
            continue;
        }
        ans = false;
    }
    return ans;
}

int Utilities::strToInt(string s)
{
    stringstream ss(s);
    int x;
    ss >> x;
    return x;
}

string Utilities::intToStr(int x)
{
    stringstream ss;
    ss << x;
    return ss.str();
}

void Utilities::padTo(std::string &str, const size_t num, const char paddingChar){
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
}

int Utilities::getTwosComplement(int x){
    x = (~x) + 1;
    x &= 4095;
    return x;
}

vector<string> Utilities::tokenize(string s, char delimiter){
    vector<string> tokens;
    stringstream check1(s);
    string intermediate;
    while(getline(check1, intermediate, ','))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

bool Utilities::isHexaString(std::string const& s)
{
  return std::all_of(s.begin(), s.end(), ::isxdigit);
}

string Utilities::hexDigitToBits(char hexDigit, int len)
{
    string ans;
    switch(hexDigit)
    {
    case '0':
        ans = "0000";
        break;
    case '1':
        ans = "0001";
        break;
    case '2':
        ans = "0010";
        break;
    case '3':
        ans = "0011";
        break;
    case '4':
        ans = "0100";
        break;
    case '5':
        ans = "0101";
        break;
    case '6':
        ans = "0110";
        break;
    case '7':
        ans = "0111";
        break;
    case '8':
        ans = "1000";
        break;
    case '9':
        ans = "1001";
        break;
    case 'A':
        ans = "1010";
        break;
    case 'B':
        ans = "1011";
        break;
    case 'C':
        ans = "1100";
        break;
    case 'D':
        ans = "1101";
        break;
    case 'E':
        ans = "1110";
        break;
    case 'F':
        ans = "1111";
        break;
    }
    if (len == 2)
    {
        return ans.substr(0, 2);
    }
    return ans;
}
