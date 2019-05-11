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
        programCounter = util.strToInt(util.baseConverter(16, 10, instruction.getAddress(), 5)) + 3;
        if (directives.count(mnemonic))
        {
            if (mnemonic == "BASE")
            {
                baseDirective = 1;
                if (symTable.count(operand))
                {
                    baseRegister = util.strToInt(util.baseConverter(16, 10, symTable[operand].getAddress(), 6));
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
                        objectCode += util.baseConverter(10, 16, util.intToStr((int) temp[i]), 2);
                    }
                    instruction.setObjectCode(objectCode);
                }
            }
            else if (mnemonic == "WORD")
            {
                instruction.setObjectCode(util.baseConverter(10, 16, operand, 6));
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
                    objectCode += util.intToHex(registerSet[registers[0]], 1);
                    objectCode += util.intToHex(registerSet[registers[1]], 1);
                    instruction.setObjectCode(objectCode);
                    cout << mnemonic << " " << operand << " " << objectCode << endl;
                }
            }
            else if (mnemonic == "TIXR")
            {
                string objectCode = "";
                objectCode += "B8";
                objectCode += util.baseConverter(10, 16, util.intToStr(registerSet[operand]), 1);
                objectCode += util.baseConverter(10, 16, util.intToStr(0), 1);
                instruction.setObjectCode(objectCode);
                cout << mnemonic << " " << operand << " " << objectCode << endl;
            }
            else if (mnemonic == "CLEAR")
            {
                string objectCode = "";
                objectCode += "B4";
                objectCode += util.baseConverter(10, 16, util.intToStr(registerSet[operand]), 1);
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
            if (util.matchRegex(operand, hashNumeric))
            {
                int number = util.strToInt(operand.substr(1, operand.size() - 1));
                if (number >= 0 && number <= 4095)
                {
                    string flags = "010000";
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += util.hexDigitToBits(opTab[mnemonic][0], 4);
                    objectCode += util.hexDigitToBits(opTab[mnemonic][1], 2);
                    objectCode += flags;
                    objectCode += util.baseConverter(10, 2, operand.substr(1, operand.size() - 1), 12);
                    objectCode = util.baseConverter(2, 16, objectCode, 6);

                }
                else if (number >= 4096 && number <= 1048575 && mnemonic[0] == '+')
                {
                    string flags = "010001";
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += util.hexDigitToBits(opTab[mnemonic.substr(1, mnemonic.length() - 1)][0], 4);
                    objectCode += util.hexDigitToBits(opTab[mnemonic.substr(1, mnemonic.length() - 1)][1], 2);
                    objectCode += flags;
                    objectCode += util.baseConverter(10, 2, operand.substr(1, operand.size() - 1), 20);
                    objectCode = util.baseConverter(2, 16, objectCode, 8);
                }
                else
                {
                    instruction.setErrorFlag(true);
                    instruction.setErrorMsg("***Error: Number out of range!***");
                }
            }
            else if (operand != "")
            {
                symValue val;
                int targetAddress = -1;
                Parser parser;
                if (parser.validateLiteral(operand)){
                    targetAddress = util.strToInt(util.baseConverter(16, 10, literalTable[parser.evaluateLiteral(operand)].Getaddress(), 5));
                }
                if (operand[0] == '#' || operand[0] == '@')
                {
                    if(!symTable.count((operand.substr(1, operand.size() - 1)))){
                            instruction.setErrorFlag(true);
                        instruction.setErrorMsg("***Undefined Operand!***");
                    }
                    else{
                        val = symTable[operand.substr(1, operand.size() - 1)];
                        targetAddress = util.strToInt(util.baseConverter(16, 10, symTable[operand.substr(1, operand.size() - 1)].getAddress(), 5));
                    }
                }
                else if (operand.substr(operand.length() - 2, 1) == ",")
                {
                    if(operand.substr(operand.length() - 1, 1) == "X"){
                    targetAddress = util.strToInt(util.baseConverter(16, 10, symTable[operand.substr(0, operand.size() - 2)].getAddress(), 5));
                    cout<<targetAddress<<endl;
                    cout<<programCounter<<endl;
                    }else{
                        instruction.setErrorFlag(true);
                        instruction.setErrorMsg("***Undefined Register!***");
                    }
                }
                else if (targetAddress == -1)
                {
                    if(!symTable.count(operand)){
                        instruction.setErrorFlag(true);
                        instruction.setErrorMsg("***Undefined Operand!***");
                    }
                    else {
                        val = symTable[operand];
                        targetAddress = util.strToInt(util.baseConverter(16, 10, symTable[operand].getAddress(), 5));
                    }
                }
                if (mnemonic[0] == '+')
                {
                    string flags = "110001";
                    adjustFlags(flags, operand);
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += util.hexDigitToBits(opTab[mnemonic.substr(1, mnemonic.length() - 1)][0], 4);
                    objectCode += util.hexDigitToBits(opTab[mnemonic.substr(1, mnemonic.length() - 1)][1], 2);
                    objectCode += flags;
                    objectCode += util.baseConverter(10, 2, util.intToStr(targetAddress), 20);
                    objectCode = util.baseConverter(2, 16, objectCode, 8);
                }
                else if (val.flag == val.Absolute){
                    string flags = "110000";
                    adjustFlags(flags, operand);
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += util.hexDigitToBits(opTab[mnemonic][0], 4);
                    objectCode += util.hexDigitToBits(opTab[mnemonic][1], 2);
                    objectCode += flags;
                    objectCode += util.baseConverter(10, 2, util.intToStr(targetAddress), 12);
                    objectCode = util.baseConverter(2, 16, objectCode, 6);
                }
                else if (targetAddress - programCounter >= -2048
                         && targetAddress - programCounter <= 2047)
                {
                    string flags = "110010";
                    adjustFlags(flags, operand);
                    bitset<6> bs(flags);
                    instruction.setFlags(bs);
                    objectCode += util.hexDigitToBits(opTab[mnemonic][0], 4);
                    objectCode += util.hexDigitToBits(opTab[mnemonic][1], 2);
                    objectCode += flags;
                    int disp = targetAddress - programCounter >= 0 ? targetAddress - programCounter : util.getTwosComplement(programCounter - targetAddress);
                    objectCode += util.baseConverter(10, 2, util.intToStr(disp), 12);
                    objectCode = util.baseConverter(2, 16, objectCode, 6);
                }
                else if (baseDirective && targetAddress - baseRegister >= 0
                         && targetAddress - baseRegister <= 4095)
                {
                    string flags = "110100";
                    adjustFlags(flags, operand);
                    bitset<6> bs(flags);
                    int disp = targetAddress - baseRegister;
                    instruction.setFlags(bs);
                    objectCode += util.hexDigitToBits(opTab[mnemonic][0], 4);
                    objectCode += util.hexDigitToBits(opTab[mnemonic][1], 2);
                    objectCode += flags;
                    objectCode += util.baseConverter(10, 2, util.intToStr(disp), 12);
                    objectCode = util.baseConverter(2, 16, objectCode, 6);
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
    //makeObjectProgram();
    writeListingFile(fileName);
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

string Pass2::makeObjectProgram(){
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
                string s = util.intToStr(recordLength / 2);
                hexaLen = util.baseConverter(10, 16, s, 2);
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
    totalLength = util.strToInt(util.baseConverter(16, 10, endAddress, 5)) - util.strToInt(util.baseConverter(16, 10, startAddress, 5)) + 1;
    string temp = util.intToStr(totalLength);
    temp = util.baseConverter(10, 16, temp, 6);
    H += temp;
    cout << H  << "\n" << T << E << endl;
    string s=H;
    s=s+"\n";
    s=s+T;
    s=s+E;
    return s;
}


string Pass2::addSpaces(string s, int n){
    string s2 = s;
    for (int i = 0; i < (int)(n - s.length()); i++){
        s2 += " ";
    }
    return s2;
}

void Pass2::writeListingFile(string fileName){
    string spaces = "";
    string s = "";
    bool successfullyAssembled = true;
    padTo(spaces, 25);
    fstream file;
    file.open((fileName.substr(0, fileName.length() - 4) + ".asm"), std::fstream::app);
    file << spaces << "**************************************************" << endl;
    file << spaces << "********** S t a r t  o f  P a s s  II ***********" << endl;
    s = "LC        Code      Label     Opcode    Operand     Flags\n";
    file << s << endl;
    for(auto it = listingTable.begin(); it != listingTable.end(); it++) {
        ListingEntry entry = *it;
        if (entry.getAddress() != ""){
            s = "";
            if (!entry.getErrorFlag()){
                string fl = entry.getFlags().to_string<char,std::string::traits_type,std::string::allocator_type>();
                s = "n=";
                s += fl[0];
                s += " i=";
                s += fl[1];
                s += " x=";
                s += fl[2];
                s += "   b=";
                s += fl[3];
                s += " p=";
                s += fl[4];
                s += " e=";
                s += fl[5];
            }
            if(entry.getErrorFlag()){
                successfullyAssembled = false;
                s = entry.getErrorMsg();
            }
            padTo(s, 12 + s.length() - entry.getOperand().length());
            s = entry.getOperand() + s;
            padTo(s, 10 + s.length() - entry.getOpCode().length());
            s = entry.getOpCode() + s;
            padTo(s, 10 + s.length() - entry.getLabel().length());
            s = entry.getLabel() + s;
            padTo(s, 10 + s.length() - entry.getObjectCode().length());
            s = entry.getObjectCode() + s;
            padTo(s, 10 + s.length() - entry.getAddress().length());
            s = entry.getAddress() + s;
            file << s << endl;
            file << endl;
            if(entry.getErrorFlag()){
                break;
            }
        }
    }
    if(successfullyAssembled){
        file << spaces << "***** S U C C E S S F U L L Y  A S S E M B L E D *****" << endl;
    }else{
        file << spaces << "***** U N S U C C E S S F U L L   A S S E M B L Y *****" << endl;
    }
    file.close();
    if(successfullyAssembled){
        ofstream objFile;
        objFile.open (fileName.substr(0, fileName.length() - 4) + ".obj");
        s=makeObjectProgram();
        objFile<<s<<endl;
        objFile.close();
    }

}

void Pass2::padTo(std::string &str, const size_t num, const char paddingChar){
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
}
