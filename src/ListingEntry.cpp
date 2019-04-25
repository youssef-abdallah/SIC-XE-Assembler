#include "ListingEntry.h"
#include <string>

ListingEntry::ListingEntry()
{
    //ctor
    this->errorFlag = false;
    this->address = "";
    this->errorMsg = "";
    this->label = "";
    this->opCode = "";
    this->operand = "";
    this->lineNumber = 0;
    this->comment = "";
}

ListingEntry::~ListingEntry()
{
    //dtor
}

string ListingEntry::getAddress(){
    return address;
}

string ListingEntry::getComment(){
    return comment;
}

string ListingEntry::getLabel(){
    return label;
}

int ListingEntry::getLineNumber(){
    return lineNumber;
}

string ListingEntry::getErrorMsg(){
    return errorMsg;
}

bool ListingEntry::getErrorFlag(){
    return errorFlag;
}

string ListingEntry::getOpCode(){
    return opCode;
}

string ListingEntry::getOperand(){
    return operand;
}

void ListingEntry::setAddress(string address){
    this->address = address;
}

void ListingEntry::setComment(string comment){
    this->comment = comment;
}
void ListingEntry::setErrorMsg(string errorMsg){
    this->errorMsg += errorMsg;
}

void ListingEntry::setOpCode(string opCode){
    this->opCode = opCode;
}

void ListingEntry::setLabel(string label){
    this->label = label;
}

void ListingEntry::setLineNumber(int lineNumber){
    this->lineNumber = lineNumber;
}

void ListingEntry::setErrorFlag(bool errorFlag){
    this->errorFlag = errorFlag;
}

void ListingEntry::setOperand(string operand){
    this->operand = operand;
}
