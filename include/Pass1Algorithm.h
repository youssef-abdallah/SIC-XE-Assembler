#ifndef PASS1ALGORITHM_H
#define PASS1ALGORITHM_H
#include "Parser.h"
#include "globals.h"
#include "symValue.h"
#include "InstructionValidator.h"
#include "ListingEntry.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Pass1Algorithm
{
    public:
        Pass1Algorithm();
        virtual ~Pass1Algorithm();
        void execute(string fileName, bool freeFormat);
        void writeListingFile(string fileName);
        unordered_map<string, symValue> getSymTable() { return symTable; }
        vector<ListingEntry> getListingTable() { return listingTable; }

    protected:

    private:
        bool endFlag;
        void openFile(ifstream& file, string fileName);
        void addComment(string &s, string comment);
        vector<ListingEntry> listingTable;
        vector<string> tokenize(string s, char delimiter);
        bool isHexaString(std::string const& s);
        void writeSymTable();
        string incrementLocCounter(int &locCounter, int inc);
        void padTo(std::string &str, const size_t num, const char paddingChar = ' ');
        unordered_map<string, symValue> symTable;
};

#endif // PASS1ALGORITHM_H
