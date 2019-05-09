#include "Expression.h"
#include <iostream>
#include <regex>

Expression::Expression()
{
    //ctor
}

Expression::~Expression()
{
    //dtor
}

bool Expression::validate(){
    string expression = Getexpression();
    regex re("([*]|\\w+)([*+/-])([*]|\\w+)");

    return (matchRegex(expression, re));
}

string Expression::evaluate(){
    string operand1Str, operand2Str, operation;
    int operand1Int, operand2Int, ans;
    symValue val1, val2;
    bool op1 = false;
    bool op2 = false;

    string expression = Getexpression();
    regex re("([*]|\\w+)([*+/-])([*]|\\w+)");
    smatch match;

    if (regex_search(expression, match, re)){
        for (unsigned int j = 0; j < match.size(); ++j)
            cout << match[j] << endl;
    }

    operand1Str = match[1];
    operation = match[2];
    operand2Str = match[3];
    if (operand1Str == "*"){
        operand1Int = locctr; // locctr
    } else if (isNumeric(operand1Str)){
        operand1Int = strToInt(operand1Str);
    } else {
        val1 = symTable[operand1Str];
        operand1Int = strToInt(baseConverter(16, 10, val1.getAddress(), 4));
        cout << "address in hex: " << val1.getAddress() << "  address in decimal : " << baseConverter(16, 10, val1.getAddress(), 4) << endl;
        op1 = true;
    }

    if (operand2Str == "*"){
        operand2Int = locctr; // locctr
    } else if (isNumeric(operand2Str)){
        operand2Int = strToInt(operand2Str);
    } else {
        val2 = symTable[operand2Str];
        operand2Int = strToInt(baseConverter(16, 10, val2.getAddress(), 4));
        op2 = true;
    }


    // flag = 0 relative
    // flag = 1 absolute
    if (op1 && op2 && val1.flag == 0 && val2.flag ==0 && (operation != "-") ){
        // relative op relative (except -)
        return "ERROR";
    } else if ( ( (op1 && val1.flag == 0) || (op2 && val2.flag == 0) ) && (operation == "*" || operation == "/") ){
        // relative */ abs
        return "ERROR";
    }

    if ( ( op1 && val1.flag == 0 && (!op2 || (op2 && val2.flag == 1)) ) || ( op2 && val2.flag == 0 && (!op1 || (op1 && val1.flag == 1))) ){
        setExpressionType("relative");
    }else {
        setExpressionType("absolute");
    }

    cout << "int 1 : " << operand1Int << "  int 2: " << operand2Int << endl;
    ans = calculate(operand1Int, operand2Int, operation);

    return intToStr(ans);
}

bool Expression::matchRegex(string s, regex re)
{
    return regex_match(s, re);
}

bool Expression::isNumeric(string s){
    bool ans = true;
    for (int i = 0; i < s.length(); i++){
        if(s[i] >= '0' && s[i] <= '9'){
            continue;
        }
        ans = false;
    }
    return ans;
}

int Expression::strToInt(string s)
{
    stringstream ss(s);
    int x;
    ss >> x;
    return x;
}

int Expression::calculate(int n1, int n2, string op){
    if (op == "+"){
        return n1 + n2;
    } else if (op == "-"){
        return n1 - n2;
    } else if (op == "*"){
        return n1 * n2;
    } else {
        return n1 / n2;
    }
}

string Expression::intToStr(int x)
{
    stringstream ss;
    ss << x;
    return ss.str();
}

string Expression::baseConverter(int base1, int base2, string s1, int len)
{
    string s2 = "";
    int value = 0;
    for(auto ch:s1)
    {
        value = (base1 * value) + (isalpha(ch) ? (ch - 'A' + 10) : (ch - '0'));
    }
    while(value)
    {
        s2 = static_cast <char> ((value % base2 < 10) ?
                                 (value % base2 + '0') : (value % base2 - 10 + 'A')) + s2;
        value/= base2;
    }
    int resultSize = s2.length();
    for(int i = 0; i < len - resultSize; i++)
    {
        s2 = "0" + s2;
    }
    return s2;
}

