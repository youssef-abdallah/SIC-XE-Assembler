
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <globals.h>
#include <regex>
#include <unordered_map>
#include <symValue.h>

class Expression
{
    public:
        Expression();
        virtual ~Expression();

        string getExpressionType() { return expressionType; }
        void setExpressionType(string val) { expressionType = val; }
        void setLocctr(int val) { locctr = val; }
        void SetSymTable(unordered_map<string, symValue> val) { symTable = val; }
        string Getexpression() { return expression; }
        void Setexpression(string val) { expression = val; }
        string Getaddress() { return address; }
        void Setaddress(string val) { address = val; }
        bool validate();
        string evaluate();

    protected:

    private:
        string expression;
        string address;
        int locctr;
        unordered_map<string, symValue> symTable;
        string expressionType;
        string baseConverter(int base1, int base2, string s1, int len);
        int calculate(int n1, int n2, string op);
};

#endif // EXPRESSION_H
