#include <string>
#ifndef LISTINGENTRY_H
#define LISTINGENTRY_H
#include "globals.h"
#include <bitset>

using namespace std;


class ListingEntry
{
    public:
        ListingEntry();
        virtual ~ListingEntry();
        int getLineNumber();
        bool getErrorFlag();
        string getLabel();
        string getAddress();
        string getOpCode();
        string getOperand();
        string getComment();
        string getErrorMsg();
        string getObjectCode(){ return objectCode; };
        bitset<6> getFlags(){ return flags; };
        void setAddress(string);
        void setLabel(string);
        void setOpCode(string);
        void setOperand(string);
        void setComment(string);
        void setErrorMsg(string);
        void setErrorFlag(bool);
        void setLineNumber(int);
        void setObjectCode(string val){ this->objectCode = val; };
        void setFlags(bitset<6> val){ this->flags = val; };
    protected:

    private:
        int lineNumber;
        bool errorFlag;
        bitset<6> flags;
        string label, address, opCode, operand, comment, errorMsg, objectCode;
};

#endif // LISTINGENTRY_H
