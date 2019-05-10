#include "File.h"

File::File()
{
    //ctor
}

File::~File()
{
    //dtor
}


void File::openFile(ifstream& file, string fileName){
    file.open(fileName, ios::in);
    return;
}

/*bool File::writeListingFile(string &fileName, vector<ListingEntry> &listingTable, bool &endFlag){
    ofstream file;
    file.open (fileName.substr(0, fileName.length() - 4) + ".asm");
    string commentSpaces = "";
    util.padTo(commentSpaces, 25);
    string spaces = "";
    util.padTo(spaces, 10);
    bool successfulAssembly = true;
    file << "line no.    Address          Label          Mnemonic          Operands          Comment\n"; //35
    for(auto it = listingTable.begin(); it != listingTable.end(); it++) {
        ListingEntry entry = *it;
        string s = entry.getComment();
        util.padTo(s, 18 + s.length() - entry.getOperand().length());
        s = entry.getOperand() + s;
        util.padTo(s, 18 + s.length() - entry.getOpCode().length());
        s = entry.getOpCode() + s;
        util.padTo(s, 18 + s.length() - entry.getLabel().length());
        s = entry.getLabel() + s;
        util.padTo(s, 17 + s.length() - entry.getAddress().length());
        s = entry.getAddress() + s;

        if (entry.getErrorFlag() == false && entry.getAddress() == ""){
            file << entry.getLineNumber() << commentSpaces << entry.getComment() << endl;
        }
        else if(entry.getErrorFlag() == true){
                successfulAssembly = false;
                if (entry.getLineNumber() < 10){
                      file << entry.getLineNumber() << " " << spaces << s << endl;
                      file << commentSpaces << entry.getErrorMsg();
                } else {
                      file << entry.getLineNumber() << spaces << s << endl;
                      file << commentSpaces << entry.getErrorMsg();
                }
        }
        else {
            if (entry.getLineNumber() < 10){
                file << entry.getLineNumber() << " " << spaces << s << endl;
            } else {
                file << entry.getLineNumber() << spaces << s << endl;
            }
        }
    }
    if (!endFlag){
        successfulAssembly = false;
        file << commentSpaces << "*** ERROR: missing end statement ***\n";
    }

    if (successfulAssembly){ // successful assembly
        file << commentSpaces << "*** P A S S   1   E N D E D   S U C C E S S F U L L Y ***\n\n";
    }
    else {
        file << commentSpaces << " *** I N C O M P L E T E    A S S E M B L Y ***\n\n";
    }

    file << spaces << " S Y M B O L  T A B L E" << endl;
    file << spaces << "************************" << endl;
    file << spaces << "NAME  " << spaces << "   VALUE " << endl;
    file << spaces << "************************" << endl;
    for(auto it = symTable.begin(); it != symTable.end(); it++){
            string first = (it->first);
            string second = (it->second).getAddress();
            string s = second;
            util.padTo(s, spaces.length() + spaces.length()  - first.length() + second.length());
            s = (first) + s;
        file << spaces << s << endl;
    }

    file.close();
    return successfulAssembly;
}

