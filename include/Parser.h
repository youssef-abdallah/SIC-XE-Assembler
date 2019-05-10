#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <sstream>
#include "globals.h"
#include <algorithm>
#include <regex>
#include "globals.h"

using namespace std;


class Parser
{
    public:
        Parser();
        virtual ~Parser();

        string getMnemonic() { return mnemonic; }
        string getLabel() { return label; }
        string getOperand() { return operand; }
        string getComment() { return comment; }
        void parse(string);
        int getLineSize() { return lineSize; };
        bool validateLiteral(string s);
        string evaluateLiteral(string s);
        int getLiteralLength(string s);

    protected:

    private:
        string mnemonic;
        string label;
        string operand;
        string comment;
        int lineSize;
};

#endif // PARSER_H
