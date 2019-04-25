#include "InstructionValidator.h"

InstructionValidator::InstructionValidator()
{
    //ctor
}

InstructionValidator::~InstructionValidator()
{
    //dtor
}

string InstructionValidator::checkLabelAndMnemonic(string label, string mnemonic){
    string checker = mnemonic;
    padTo(checker, 9 - label.size() + mnemonic.size());
    checker = label + checker;
    return checker;
}

string InstructionValidator::checkLabelMnemonicAndOperand(string label, string mnemonic, string operand){
    string checker = operand;
    padTo(checker, 8 - mnemonic.size() + operand.size());
    checker = mnemonic + checker;
    padTo(checker, 9 - label.size() + checker.size());
    checker = label + checker;
    return checker;
}

string InstructionValidator::checkMnemonicAndOperand(string mnemonic, string operand){
    string checker = operand;
    padTo(checker, 8 - mnemonic.size() + operand.size());
    checker = mnemonic + checker;
    padTo(checker, 9 + checker.size());
    return checker;
}

string InstructionValidator::checkOneField(string mnemonic){
    string checker = mnemonic;
    padTo(checker, 9 + mnemonic.size());
    return checker;
}

void InstructionValidator::padTo(std::string &str, const size_t num, const char paddingChar){
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
}
