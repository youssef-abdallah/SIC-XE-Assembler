#include "Expression.h"

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

    return (util.matchRegex(expression, re));
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
    }

    operand1Str = match[1];
    operation = match[2];
    operand2Str = match[3];
    if (operand1Str == "*"){
        operand1Int = locctr; // locctr
    } else if (util.isNumeric(operand1Str)){
        operand1Int = util.strToInt(operand1Str);
    } else {
        if (symTable.find(operand1Str) == symTable.end()){
            return "Undefined";
        } else {
            val1 = symTable[operand1Str];
            operand1Int = util.strToInt(util.baseConverter(16, 10, val1.getAddress(), 4));
            op1 = true;
        }
    }

    if (operand2Str == "*"){
        operand2Int = locctr; // locctr
    } else if (util.isNumeric(operand2Str)){
        operand2Int = util.strToInt(operand2Str);
    } else {
        if (symTable.find(operand2Str) == symTable.end()){
            return "Undefined";
        } else {
            val2 = symTable[operand2Str];
            operand2Int = util.strToInt(util.baseConverter(16, 10, val2.getAddress(), 4));
            op2 = true;
        }
    }
    if (op1 && op2 && val1.flag == symValue::Relative && val2.flag == symValue::Relative && (operation != "-") ){
        // relative op relative (except -)
        return "ERROR";
    } else if ( ( (op1 && val1.flag == symValue::Relative) || (op2 && val2.flag == symValue::Relative) ) && (operation == "*" || operation == "/") ){
        // relative */ abs
        return "ERROR";
    }
    if ( ( op1 && val1.flag == symValue::Relative && (!op2 || (op2 && val2.flag == symValue::Absolute)) ) || ( op2 && val2.flag == symValue::Relative && (!op1 || (op1 && val1.flag == symValue::Absolute))) ){
        setExpressionType("relative");
    }else {
        setExpressionType("absolute");
    }
    ans = calculate(operand1Int, operand2Int, operation);
    return util.intToStr(ans);
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

