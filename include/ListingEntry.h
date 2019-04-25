#include <string>
#ifndef LISTINGENTRY_H
#define LISTINGENTRY_H
#include "globals.h"

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
        void setAddress(string);
        void setLabel(string);
        void setOpCode(string);
        void setOperand(string);
        void setComment(string);
        void setErrorMsg(string);
        void setErrorFlag(bool);
        void setLineNumber(int);
    protected:

    private:
        int lineNumber;
        bool errorFlag;
        string label, address, opCode, operand, comment, errorMsg;
};

#endif // LISTINGENTRY_H
