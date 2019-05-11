#ifndef PASS2_H
#define PASS2_H
#include <unordered_map>
#include <sstream>
#include "symValue.h"
#include <vector>
#include <regex>
#include "ListingEntry.h"
#include "globals.h"
#include "Utilities.h"
#include <fstream>
#include "LiteralEntry.h"
#include "Parser.h"

class Pass2
{
    public:
        Pass2();
        Pass2(unordered_map<string, symValue> symTable);
        virtual ~Pass2();
        void SetSymTable(unordered_map<string, symValue> val) { symTable = val; }
        void SetLiteralTable(unordered_map<string, LiteralEntry> val) { literalTable = val; }
        void SetListingTable(vector<ListingEntry> val) { listingTable = val; }
        void execute(string);

    protected:

    private:
        unordered_map<string, symValue> symTable;
        unordered_map<string, LiteralEntry> literalTable;
        vector<ListingEntry> listingTable;
        int programCounter, baseRegister;
        bool baseDirective;
        void adjustFlags(string &flags, string operand);
        string makeObjectProgram();
        string addSpaces(string, int);
        void writeListingFile(string);
        void padTo(std::string &str, const size_t num, const char paddingChar = ' ');
};

#endif // PASS2_H
