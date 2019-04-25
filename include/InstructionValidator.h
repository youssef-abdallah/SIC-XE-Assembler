#ifndef INSTRUCTIONVALIDATOR_H
#define INSTRUCTIONVALIDATOR_H
#include <string>
#include <globals.h>

using namespace std;


class InstructionValidator
{
    public:
        InstructionValidator();
        virtual ~InstructionValidator();
        string checkOneField(string mnemonic);
        string checkMnemonicAndOperand(string mnemonic, string operand);
        string checkLabelAndMnemonic(string label, string mnemonic);
        string checkLabelMnemonicAndOperand(string label, string mnemonic, string operand);
    protected:

    private:
        void padTo(std::string &str, const size_t num, const char paddingChar = ' ');
};

#endif // INSTRUCTIONVALIDATOR_H
