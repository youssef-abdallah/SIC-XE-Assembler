#include "Parser.h"

Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}

void Parser::parse(string s){
    vector<string> instructions;
    bool commentFlag = false;
    std::istringstream iss(s);
    string instruction;
    commentFlag = false;
    while(iss >> instruction)
    {
        int quotesCount = 0;
        for(int i = 0; i < (int) instruction.length(); i++){
            if (instruction[i] == '\''){
                quotesCount++;
            }
        }
        if (commentFlag || instruction[0] == '.')
        {
            commentFlag = 1;
            comment += instruction + " ";
        } else if (quotesCount == 1){
            string restOfInstruction;
            while(iss >> restOfInstruction){
                instruction += " " + restOfInstruction;
                if (restOfInstruction.back() == '\''){
                    break;
                }
            }
            instructions.push_back(instruction);
        } else if (quotesCount == 2){
            instructions.push_back(instruction);
        }
        else
        {
            std::transform(instruction.begin(), instruction.end(), instruction.begin(), ::toupper);
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

bool Parser::validateLiteral(string s){
    if (s == "=*") return true;
    if (s.length() < 4 || s[0] != '=')
        return false;
    regex re("=((c|C)\'((\\s){0,1}(\\w){0,1})+\')|=((x|X)[\']([A-F]|\\d)+[\'])|=((w|W)[\'](\\d+)[\'])");
    return util.matchRegex(s, re);
}

string Parser::evaluateLiteral(string s){
    char type = s[1];
    int len = s.length();
    s = len > 4 ? s.substr(3, len - 4) : s;
    string value;
    if (type == 'X' || type == 'x'){
        value = s;
    } else if (type == 'C' || type == 'C'){
        for(int i = 0; i < (int)s.length(); i++){
            value += util.baseConverter(10, 16, util.intToStr((int) s[i]), 2);
        }
    } else if (type == 'W' || type == 'w'){
        value = util.baseConverter(10, 16, s, 6);
    }
    return value;
}

int Parser::getLiteralLength(string s){
    char type = s[1];
    int len = s.length();
    s = len > 4 ? s.substr(3, len - 4) : s;
    int ans = 0;
    if (type == 'X' || type == 'x'){
        ans = (len - 4) / 2;
    } else if (type == 'C' || type == 'C'){
        ans = len - 4;
    } else if (type == 'W' || type == 'w'){
        ans = 3;
    }
    return ans;
}
