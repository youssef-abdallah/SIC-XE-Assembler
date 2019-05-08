#include <iostream>
#include <string>
#include "ListingEntry.h"
#include <unordered_map>
#include <unordered_set>
#include "Pass1Algorithm.h"
#include "symValue.h"
#include "Pass2.h"

using namespace std;
unordered_map<string, symValue> symTable;
unordered_map<string, string> opTab;
unordered_map<string, int> instructionFormat;
unordered_set<string> directives;
unordered_map<string, int> registerSet;

void initializeOpTabAndInstructionFormat()
{
    opTab["START"] = "24654";
    opTab["ADD"] = "18";
    opTab["ADDR"] = "90";
    opTab["CLEAR"] = "B4";
    opTab["COMP"] = "28";
    opTab["COMPR"] = "A0";
    opTab["DIV"] = "24";
    opTab["DIVR"] = "9C";
    opTab["J"] = "3C";
    opTab["JEQ"] = "30";
    opTab["JGT"] = "34";
    opTab["JLT"] = "38";
    opTab["JSUB"] = "48";
    opTab["LDA"] = "00";
    opTab["LDB"] = "68";
    opTab["LDCH"] = "50";
    opTab["LDL"] = "08";
    opTab["LDS"] = "6C";
    opTab["LDT"] = "74";
    opTab["LDX"] = "04";
    opTab["MUL"] = "20";
    opTab["MULR"] = "98";
    opTab["RD"] = "D8";
    opTab["RMO"] = "AC";
    opTab["RSUB"] = "4C";
    opTab["STA"] = "0C";
    opTab["STB"] = "78";
    opTab["STCH"] = "54";
    opTab["STL"] = "14";
    opTab["STS"] = "7C";
    opTab["STT"] = "84";
    opTab["STX"] = "10";
    opTab["SUB"] = "1C";
    opTab["SUBR"] = "94";
    opTab["TD"] = "E0";
    opTab["TIX"] = "2C";
    opTab["TIXR"] = "B8";
    opTab["WD"] = "DC";
    instructionFormat["ADD"] = 3;
    instructionFormat["ADDR"] = 2;
    instructionFormat["CLEAR"] = 2;
    instructionFormat["COMP"] = 3;
    instructionFormat["COMPR"] = 2;
    instructionFormat["DIV"] = 3;
    instructionFormat["DIVR"] = 2;
    instructionFormat["J"] = 3;
    instructionFormat["JEQ"] = 3;
    instructionFormat["JGT"] = 3;
    instructionFormat["JLT"] = 3;
    instructionFormat["JSUB"] = 3;
    instructionFormat["LDA"] = 3;
    instructionFormat["LDB"] = 3;
    instructionFormat["LDCH"] = 3;
    instructionFormat["LDL"] = 3;
    instructionFormat["LDS"] = 3;
    instructionFormat["LDT"] = 3;
    instructionFormat["LDX"] = 3;
    instructionFormat["MUL"] = 3;
    instructionFormat["MULR"] = 2;
    instructionFormat["RD"] = 3;
    instructionFormat["RMO"] = 2;
    instructionFormat["RSUB"] = 3;
    instructionFormat["SHIFTL"] = 2;
    instructionFormat["SHIFTR"] = 2;
    instructionFormat["STA"] = 3;
    instructionFormat["STB"] = 3;
    instructionFormat["STCH"] = 3;
    instructionFormat["STL"] = 3;
    instructionFormat["STS"] = 3;
    instructionFormat["STT"] = 3;
    instructionFormat["STX"] = 3;
    instructionFormat["SUB"] = 3;
    instructionFormat["SUBR"] = 2;
    instructionFormat["TD"] = 3;
    instructionFormat["TIX"] = 3;
    instructionFormat["TIXR"] = 2;
    instructionFormat["WD"] = 3;
    directives.insert("START");
    directives.insert("END");
    directives.insert("BASE");
    directives.insert("NOBASE");
    directives.insert("BYTE");
    directives.insert("WORD");
    directives.insert("RESW");
    directives.insert("RESB");
    directives.insert("ORG");
    directives.insert("EQU");
    registerSet["A"] = 0;
    registerSet["X"] = 1;
    registerSet["L"] = 2;
    registerSet["B"] = 3;
    registerSet["S"] = 4;
    registerSet["T"] = 5;
    registerSet["PC"] = 8;
    registerSet["SW"] = 9;

}



int main(int argc, char *argv[])
{
    initializeOpTabAndInstructionFormat();
    Pass1Algorithm pass1;
    string freeFormat(argv[2]);
    pass1.execute(argv[1], freeFormat == "free");
    Pass2 pass2;
    pass2.SetListingTable(pass1.getListingTable());
    pass2.SetSymTable(pass1.getSymTable());
    pass2.execute(argv[1]);
    return 0;
}
