#include "Parser.h"
#include <algorithm>

Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}

void Parser::parse(string s){
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    vector<string> instructions;
    bool commentFlag = false;
    std::istringstream iss(s);
    string instruction;
    commentFlag = false;
    while(iss >> instruction)
    {
        if (commentFlag || instruction[0] == '.')
        {
            commentFlag = 1;
            comment += instruction + " ";
        }
        else
        {
            instructions.push_back(instruction);
        }
    }
    lineSize = instructions.size();
    string checker;
    if (lineSize == 1)
    {
        mnemonic = instructions[0];
    }
    else if (lineSize == 2)
    {
        string temp;
        temp = instructions[0];
        if (opTab.count(temp) || directives.count(temp) || temp[0] == '+')
        {
            mnemonic = temp;
            operand = instructions[1];
        }
        else
        {
            label = temp;
            mnemonic = instructions[1];
        }
    }
    else if (lineSize == 3)
    {
        label = instructions[0];
        mnemonic = instructions[1];
        operand = instructions[2];
    }
}
