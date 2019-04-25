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

        string getAddress() { return address; }
        void setAddress(string val) { address = val; }
        int getLength() { return length; }
        void setLength(int val) { length = val; }

    protected:

    private:
        string address;
        int length;
};

#endif // SYMVALUE_H
