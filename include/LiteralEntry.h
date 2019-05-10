#ifndef LITERALENTRY_H
#define LITERALENTRY_H
#include <string>

using namespace std;

class LiteralEntry
{
    public:
        LiteralEntry();
        virtual ~LiteralEntry();

        string Getvalue() { return value; }
        void Setvalue(string val) { value = val; }
        int Getlength() { return length; }
        void Setlength(int val) { length = val; }
        string Getname() { return name; }
        void Setname(string val) { name = val; }
        string Getaddress() { return address; }
        void Setaddress(string val) { address = val; }

    protected:

    private:
        string value;
        int length;
        string name;
        string address;
};

#endif // LITERALENTRY_H
