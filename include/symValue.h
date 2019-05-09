#ifndef SYMVALUE_H
#define SYMVALUE_H
#include <string>
#include <globals.h>

using namespace std;


class symValue
{
    public:

        symValue();
        virtual ~symValue();
        //const bool Absolute = 1;
        //const bool Relative = 0;
        bool flag;
        string getAddress() { return address; }
        void setAddress(string val) { address = val; }
        int getLength() { return length; }
        void setLength(int val) { length = val; }
        void setFlag(bool f) {flag = f;}
        bool getFlag() { return flag; }

    protected:

    private:
        string address;
        int length;

};

#endif // SYMVALUE_H
