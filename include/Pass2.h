#ifndef PASS2_H
#define PASS2_H
#include <unordered_map>
#include <sstream>
#include "symValue.h"
#include <vector>
#include <regex>
#include "ListingEntry.h"
#include "globals.h"

class Pass2
{
    public:
        Pass2();
        Pass2(unordered_map<string, symValue> symTable);
        virtual ~Pass2();
        void SetSymTable(unordered_map<string, symValue> val) { symTable = val; }
        void SetListingTable(vector<ListingEntry> val) { listingTable = val; }
        void execute();

    protected:

    private:
        unordered_map<string, symValue> symTable;
        vector<ListingEntry> listingTable;
        string hexToBinary(string);
        string intToHex(int, int);
        bool matchRegex(string, regex);
        int strToInt(string);
        string intToStr(int);
        string baseConverter(int base1, int base2, string s1, int len);
        string hexDigitToBits(char hexDigit, int len);
        int programCounter, baseRegister;
        bool baseDirective;
        void adjustFlags(string &flags, string operand);
        void makeObjectProgram();
        string addSpaces(string, int);
};

#endif // PASS2_H
