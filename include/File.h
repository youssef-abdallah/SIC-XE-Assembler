#ifndef FILE_H
#define FILE_H
#include <fstream>
#include <vector>
#include <ListingEntry.h>

using namespace std;

class File
{
    public:
        File();
        virtual ~File();
        void openFile(ifstream& file, string fileName);
        bool writeListingFile(string &fileName, vector<ListingEntry>& listingTable, bool &endFlag);

    protected:

    private:
};

#endif // FILE_H
