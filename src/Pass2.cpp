#include "Pass2.h"
#include <iostream>

Pass2::Pass2()
{
    //ctor
}

Pass2::Pass2(unordered_map<string, symValue> symTable){
    this->symTable = symTable;
}

Pass2::~Pass2()
{
    //dtor
}

void Pass2::execute(){
    for(ListingEntry &instruction : listingTable){
        string mnemonic = instruction.getOpCode();
        string label = instruction.getLabel();
        string operand = instruction.getOperand();
        int format = instructionFormat[mnemonic];
        switch (format){
            case 1:
                break;
            case 2:
            {
                regex re("[,]+");
                sregex_token_iterator it(operand.begin(), operand.end(), re, -1);
                sregex_token_iterator reg_end;
                vector<string> registers;
                while(it != reg_end){
                    registers.push_back(it->str());
                    it++;
                }
                if (registers.size() == 2){
                    string objectCode = "";
                    objectCode += opTab[mnemonic];
                    objectCode += intToHex(registerSet[registers[0]], 1);
                    objectCode += intToHex(registerSet[registers[1]], 1);
                    instruction.setObjectCode(objectCode);
                } else {
                    //error
                }
            }
                break;
            case 3:
            {   regex hashNumeric("^(#\\d+)$");
                if (matchRegex(operand, hashNumeric)){
                    int number = strToInt(operand.substr(1, operand.size() - 1));
                    if (number >= 0 && number <= 4095){
                        string flags = "010000";
                        bitset<6> bs(flags);
                        instruction.setFlags(bs);
                        string objectCode = "";
                        objectCode += hexDigitToBits(opTab[mnemonic][0], 4);
                        objectCode += hexDigitToBits(opTab[mnemonic][1], 2);
                        objectCode += flags;
                        objectCode += baseConverter(10, 2, operand.substr(1, operand.size() - 1), 12);
                        objectCode = baseConverter(2, 16, objectCode, 6);
                        //cout << mnemonic << " " << operand << " " << objectCode << endl;

                    } else if (number >= 4096 && number <= 1048575 && mnemonic[0] == '+'){
                        string flags = "010001";
                        bitset<6> bs(flags);
                        instruction.setFlags(bs);
                        string objectCode = "";
                        objectCode += hexDigitToBits(opTab[mnemonic][0], 4);
                        objectCode += hexDigitToBits(opTab[mnemonic][1], 2);
                        objectCode += flags;
                        objectCode += baseConverter(10, 2, operand.substr(1, operand.size() - 1), 20);
                        objectCode = baseConverter(2, 16, objectCode, 6);
                    } else {
                        // error number out of range
                    }
                } else if (operand != ""){
                    if (mnemonic[0] == '+'){
                        string flags = "110001";
                        bitset<6> bs(flags);
                        instruction.setFlags(bs);
                        string objectCode = "";
                        objectCode += hexDigitToBits(opTab[mnemonic][0], 4);
                        objectCode += hexDigitToBits(opTab[mnemonic][1], 2);
                        objectCode += flags;
                        objectCode += baseConverter(10, 2, operand, 20);
                        objectCode = baseConverter(2, 16, objectCode, 6);
                    }
                } else {
                }
            }
                break;

        }
    }
}

string Pass2::baseConverter(int base1, int base2, string s1, int len){
    string s2 = "";
    int value = 0;
    for(auto ch:s1){
        value = (base1 * value) + (isalpha(ch) ? (ch - 'A' + 10) : (ch - '0'));
    }
    while(value){
        s2 = static_cast <char> ((value % base2 < 10) ?
         (value % base2 + '0') : (value % base2 - 10 + 'A')) + s2;
        value/= base2;
    }
    int resultSize = s2.length();
    for(int i = 0; i < len - resultSize; i++){
        s2 = "0" + s2;
    }
    return s2;
}

string Pass2::hexDigitToBits(char hexDigit, int len){
    string ans;
    switch(hexDigit){
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
    if (len == 2){
        return ans.substr(0, 2);
    }
    return ans;
}

string Pass2::intToHex(int integer, int len)
{
    std::stringstream sstream;
    sstream << std::hex << integer;
    string result = sstream.str();
    int resultSize = result.length();
    for(int i = 0; i < len - resultSize; i++){
        result = "0" + result;
    }
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool Pass2::matchRegex(string s, regex re){
    return regex_match(s, re);
}

int Pass2::strToInt(string s){
    stringstream ss(s);
    int x;
    ss >> x;
    return x;
}
