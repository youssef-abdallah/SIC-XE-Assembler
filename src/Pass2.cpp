#include "Pass2.h"
#include <iostream>

Pass2::Pass2()
{
    //ctor
    baseDirective = 0;
}

Pass2::Pass2(unordered_map<string, symValue> symTable)
{
    this->symTable = symTable;
    baseDirective = 0;
}

Pass2::~Pass2()
{
    //dtor
}

void Pass2::execute(string fileName)
{
    for(ListingEntry &instruction : listingTable)
    {
        string mnemonic = instruction.getOpCode();
        string label = instruction.getLabel();
        string operand = instruction.getOperand();
        int format = mnemonic[0] != '+' ? instructionFormat[mnemonic] : instructionFormat[mnemonic.substr(1, mnemonic.length() - 1)];
        programCounter = strToInt(baseConverter(16, 10, instruction.getAddress(), 5)) + 3;
        if (directives.count(mnemonic))
        {
            if (mnemonic == "BASE")
            {
                baseDirective = 1;
                if (symTable.count(operand))
                {
                    baseRegister = strToInt(baseConverter(16, 10, symTable[operand].getAddress(), 6));
                }
            }
            else if (mnemonic == "NOBASE")
            {
                baseDirective = 0;
            }
            else if (mnemonic == "BYTE")
            {
                if (operand[0] == 'X')
                {
                    instruction.setObjectCode(operand.substr(2, operand.length() - 3));
                }
                else if (operand[0] == 'C')
                {
                    string temp = operand.substr(2, operand.length() - 3);
                    string objectCode = "";
                    for(int i = 0; i < (int)temp.length(); i++){
                        objectCode += baseConverter(10, 16, intToStr((int) temp[i]), 2);
                    }
                    instruction.setObjectCode(objectCode);
                }
            }
            else if (mnemonic == "WORD")
            {
                instruction.setObjectCode(baseConverter(10, 16, operand, 6));
            }
            cout << mnemonic << " " << operand << " " << instruction.getObjectCode() << endl;
        }
        switch (format)
        {
        case 1:
            break;
        case 2:
        {
            if (operand[1] == ',')
            {
                vector<string> registers;
                registers.push_back(string(1, operand[0]));
                registers.push_back(string(1, operand[2]));
                if (registers.size() == 2)
                {
                    string objectCode = "";
                    objectCode += opTab[mnemonic];
                    objectCode += intToHex(registerSet[registers[0]], 1);
                    objectCode += intToHex(registerSet[registers[1]], 1);
                    instruction.setObjectCode(objectCode);
                    cout << mnemonic << " " << operand << " " << objectCode << endl;
                }
            }
            else if (mnemonic == "TIXR")
            {
                string objectCode = "";
                objectCode += "B8";
                objectCode += baseConverter(10, 16, intToStr(registerSet[operand]), 1);
                objectCode += baseConverter(10, 16, intToStr(0), 1);
                instruction.setObjectCode(objectCode);
                cout << mnemonic << " " << operand << " " << objectCode << endl;
            }
            else if (mnemonic == "CLEAR")
            {
                string objectCode = "";
                objectCode += "B4";
                objectCode += baseConverter(10, 16, intToStr(registerSet[operand]), 1);
                objectCode += "0";
                instruction.setObjectCode(objectCode);
                cout << mnemonic << " " << operand << " " << objectCode << endl;
            }
        }
        break;
        case 3:
        {
            regex hashNumeric("^(#\\d+)$");
            string objectCode = "";
            if (matchRegex(operand, hashNumeric))
            {
                int number = strToInt(operand.substr(1, operand.size() - 1));
                if (number >= 0 && number <= 4095)
                {
                    string flags = "010000";
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += hexDigitToBits(opTab[mnemonic][0], 4);
                    objectCode += hexDigitToBits(opTab[mnemonic][1], 2);
                    objectCode += flags;
                    objectCode += baseConverter(10, 2, operand.substr(1, operand.size() - 1), 12);
                    objectCode = baseConverter(2, 16, objectCode, 6);

                }
                else if (number >= 4096 && number <= 1048575 && mnemonic[0] == '+')
                {
                    string flags = "010001";
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += hexDigitToBits(opTab[mnemonic.substr(1, mnemonic.length() - 1)][0], 4);
                    objectCode += hexDigitToBits(opTab[mnemonic.substr(1, mnemonic.length() - 1)][1], 2);
                    objectCode += flags;
                    objectCode += baseConverter(10, 2, operand.substr(1, operand.size() - 1), 20);
                    objectCode = baseConverter(2, 16, objectCode, 8);
                }
                else
                {
                    instruction.setErrorFlag(true);
                    instruction.setErrorMsg("***Error: Number out of range!***");
                }
            }
            else if (operand != "")
            {
                int targetAddress;
                if (operand[0] == '#' || operand[0] == '@')
                {
                    targetAddress = strToInt(baseConverter(16, 10, symTable[operand.substr(1, operand.size() - 1)].getAddress(), 5));
                }
                else if (operand.substr(operand.length() - 2, 2) == ",X")
                {
                    targetAddress = strToInt(baseConverter(16, 10, symTable[operand.substr(0, operand.size() - 2)].getAddress(), 5));
                }
                else
                {
                    targetAddress = strToInt(baseConverter(16, 10, symTable[operand].getAddress(), 5));
                }
                if (mnemonic[0] == '+')
                {
                    string flags = "110001";
                    adjustFlags(flags, operand);
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += hexDigitToBits(opTab[mnemonic.substr(1, mnemonic.length() - 1)][0], 4);
                    objectCode += hexDigitToBits(opTab[mnemonic.substr(1, mnemonic.length() - 1)][1], 2);
                    objectCode += flags;
                    objectCode += baseConverter(10, 2, intToStr(targetAddress), 20);
                    objectCode = baseConverter(2, 16, objectCode, 8);
                }
                else if (targetAddress - programCounter >= -2048
                         && targetAddress - programCounter <= 2047)
                {
                    string flags = "110010";
                    adjustFlags(flags, operand);
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += hexDigitToBits(opTab[mnemonic][0], 4);
                    objectCode += hexDigitToBits(opTab[mnemonic][1], 2);
                    objectCode += flags;
                    int disp = targetAddress - programCounter >= 0 ? targetAddress - programCounter : getTwosComplement(programCounter - targetAddress);
                    objectCode += baseConverter(10, 2, intToStr(disp), 12);
                    objectCode = baseConverter(2, 16, objectCode, 6);
                }
                else if (baseDirective && targetAddress - baseRegister >= 0
                         && targetAddress - baseRegister <= 4095)
                {
                    string flags = "110100";
                    adjustFlags(flags, operand);
                    bitset<6> bs(flags);
                    int disp = targetAddress - baseRegister;
                    instruction.setFlags(bs);
                    objectCode += hexDigitToBits(opTab[mnemonic][0], 4);
                    objectCode += hexDigitToBits(opTab[mnemonic][1], 2);
                    objectCode += flags;
                    objectCode += baseConverter(10, 2, intToStr(disp), 12);
                    objectCode = baseConverter(2, 16, objectCode, 6);
                }
                else
                {
                    //error instruction addressing error
                    instruction.setErrorFlag(true);
                    instruction.setErrorMsg("***Error: Wrong operand (Addressing Problem)!***");
                }
            }
            else
            {
                string flags = "110000";
                bitset<6> bs(flags);
                instruction.setFlags(bs);
                objectCode = "4F0000";
            }
            instruction.setObjectCode(objectCode);
            cout << mnemonic << " " << operand << " " << objectCode << endl;
        }
        break;

        }
    }
    makeObjectProgram();
    writeListingFile(fileName);
}

string Pass2::baseConverter(int base1, int base2, string s1, int len)
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

string Pass2::hexDigitToBits(char hexDigit, int len)
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

string Pass2::intToHex(int integer, int len)
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

bool Pass2::matchRegex(string s, regex re)
{
    return regex_match(s, re);
}

int Pass2::strToInt(string s)
{
    stringstream ss(s);
    int x;
    ss >> x;
    return x;
}

string Pass2::intToStr(int x)
{
    stringstream ss;
    ss << x;
    return ss.str();
}

void Pass2::adjustFlags(string &flags, string operand)
{
    if (operand[0] == '#')
    {
        flags[0] = '0';
    }
    else if (operand[0] == '@')
    {
        flags[1] = '0';
    }
    if (operand.length() > 2 && operand.substr(operand.length() - 2, 2) == ",X")
    {
        flags[2] = '1';
    }
    return;
}

void Pass2::makeObjectProgram(){
    string H = "H^";
    string T = "";
    string E = "E^";
    int recordLength = 0;
    int totalLength = 0;
    string objectCodes = "";
    string hexaLen;
    bool addressFlag = true;
    string startAddress;
    string endAddress;

    for (ListingEntry &instruction : listingTable){
            string address = "00" + instruction.getAddress();
        if (instruction.getOpCode() == "START"){
                // need to handle spaces and program length
            startAddress = instruction.getAddress();
            endAddress = startAddress;
            string progName = instruction.getLabel();
            progName = addSpaces(progName, 6);
            H += progName + "^" + address + "^" ;
            E += address;
        } else if (instruction.getOpCode() != "BASE" && instruction.getOpCode() != "NOBASE"){
            if (instruction.getObjectCode() == "" && instruction.getOpCode() != "END"){
                continue;
            }
            if (addressFlag){
                T += "T^" + address;
                addressFlag = false;
            }
            recordLength += instruction.getObjectCode().length();
            if (recordLength <= 60 && instruction.getOpCode() != "END"){
                objectCodes += "^" + instruction.getObjectCode();
            } else {
                recordLength -= instruction.getObjectCode().length();
                string s = intToStr(recordLength / 2);
                hexaLen = baseConverter(10, 16, s, 2);
                T += "^" + hexaLen + objectCodes + "\n";
                addressFlag = true;
                recordLength = instruction.getObjectCode().length();
                objectCodes = "^" + instruction.getObjectCode();
            }
        }
        if (instruction.getOpCode() == "END"){
            endAddress = instruction.getAddress();
        }

    }
    totalLength = strToInt(baseConverter(16, 10, endAddress, 5)) - strToInt(baseConverter(16, 10, startAddress, 5)) + 1;
    string temp = intToStr(totalLength);
    temp = baseConverter(10, 16, temp, 6);
    H += temp;
    cout << H  << "\n" << T << E << endl;
}


string Pass2::addSpaces(string s, int n){
    string s2 = s;
    for (int i = 0; i < (int)(n - s.length()); i++){
        s2 += " ";
    }
    return s2;
}

int Pass2::getTwosComplement(int x){
    x = (~x) + 1;
    x &= 4095;
    return x;
}

void Pass2::writeListingFile(string fileName){
    string spaces = "";
    string s="";
    bool successfullyAssembled=true;
    padTo(spaces, 25);
    fstream file;
    file.open ((fileName.substr(0, fileName.length() - 4) + ".asm"),std::fstream::app);
    file << spaces<<"**************************************************"<<endl;
    file << spaces<<"********** S t a r t  o f  P a s s  II ***********"<<endl;
    s="LC        Code      Label     Opcode    Operand     Flags\n";
    file<<s<<endl;
    for(auto it = listingTable.begin(); it != listingTable.end(); it++) {
        ListingEntry entry = *it;
        if(entry.getAddress()!=""&&!entry.getErrorFlag()){
            string fl=entry.getFlags().to_string<char,std::string::traits_type,std::string::allocator_type>();;
            s="n=";
            s+=fl[0];
            s+=" i=";
            s+=fl[1];
            s+=" x=";
            s+=fl[2];
            s+="   b=";
            s+=fl[3];
            s+=" p=";
            s+=fl[4];
            s+=" e=";
            s+=fl[5];
            padTo(s,12+s.length()-entry.getOpCode().length());
            s=entry.getOpCode()+s;
            padTo(s,10+s.length()-entry.getOperand().length());
            s=entry.getOperand()+s;
            padTo(s,10+s.length()-entry.getLabel().length());
            s=entry.getLabel()+s;
            padTo(s,10+s.length()-entry.getObjectCode().length());
            s=entry.getObjectCode()+s;
            padTo(s,10+s.length()-entry.getAddress().length());
            s=entry.getAddress()+s;
            //padTo(s,s.length()-3);
            //s=entry.getLineNumber().to_string()+s;
        file<<s<<endl;
        file<<endl;}
        if(entry.getErrorFlag()){
            successfullyAssembled=false;
            file << spaces<<entry.getErrorMsg()<<endl;
        }
    }
    if(successfullyAssembled){
        file << spaces<<"***** S U C C E S S F U L L Y  A S S E M B L E D ****"<<endl;
    }else{
        file << spaces<<"***** U N S U C C E S S F U L L Y  A S S E M B L Y ****"<<endl;
    }
    file.close();
}

void Pass2::padTo(std::string &str, const size_t num, const char paddingChar){
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
}
