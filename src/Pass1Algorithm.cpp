#include "Pass1Algorithm.h"
#include <iostream>

Pass1Algorithm::Pass1Algorithm()
{
    //ctor
}

Pass1Algorithm::~Pass1Algorithm()
{
    //dtor
}

bool Pass1Algorithm::execute(string fileName, bool freeFormat) {
    ifstream file;
    openFile(file, fileName);
    string s, instruction;
    int locCounter = 0, lineNumber = 0;
    bool firstLine = true;
    while(getline(file, s))
    {
        lineNumber++;
        std::istringstream iss(s);
        string firstWord;
        string comment = "";
        iss >> firstWord;
        if (firstWord[0] != '.')
        {
            Parser parser;
            parser.parse(s);
            string mnemonic = parser.getMnemonic();
            string label = parser.getLabel();
            string operand = parser.getOperand();
            int lineSize = parser.getLineSize();
            string checker;
            InstructionValidator validator;
            ListingEntry entry;
            if (lineSize == 1)
            {
                if (!freeFormat){
                      checker = validator.checkOneField(mnemonic);
                      addComment(checker, comment);
                    if (checker != s){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: misplaced operation mnemonic ***\n");
                    }
                }
            }
            else if (lineSize == 2)
            {
                if (label == "")
                {
                    if (!freeFormat){
                        checker = validator.checkMnemonicAndOperand(mnemonic, operand);
                        addComment(checker, comment);
                        if (checker.substr(9, mnemonic.length()) != s.substr(9, mnemonic.length())){
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: misplaced operation mnemonic ***\n");
                        }
                        if (checker.substr(17, operand.size()) !=  s.substr(17, operand.size())){
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: misplaced operand field ***\n");
                        }
                    }

                }
                else
                {
                    if (!freeFormat){
                        checker = validator.checkLabelAndMnemonic(label, mnemonic);
                        addComment(checker, comment);
                        if (checker.substr(0, label.length()) != s.substr(0, label.length())){
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: misplaced label field ***\n");
                        }
                        if (checker.substr(9, mnemonic.length()) != s.substr(9, mnemonic.length())){
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: misplaced operation mnemonic ***\n");
                        }
                    }
                }
            }
            else if (lineSize == 3)
            {
                if (!freeFormat){
                    checker = validator.checkLabelMnemonicAndOperand(label, mnemonic, operand);
                    addComment(checker, comment);
                    if (checker.substr(0, label.length()) != s.substr(0, label.length())){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: misplaced label field ***\n");
                    }
                    if (checker.substr(9, mnemonic.length()) != s.substr(9, mnemonic.length())){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: misplaced operation mnemonic ***\n");
                    }
                    if (checker.substr(17, operand.size()) !=  s.substr(17, operand.size())){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: misplaced operand field ***\n");
                    }
                }
            }
            else
            {
                entry.setErrorFlag(true);
                entry.setErrorMsg("*** ERROR: this statement has extra fields ***\n");
            }
            if (mnemonic == "END")
            {
                endFlag = true;
                entry.setAddress(incrementLocCounter(locCounter, 0));
                entry.setComment(comment);
                entry.setLineNumber(lineNumber);
                entry.setOpCode("END");
                entry.setOperand(operand);
                entry.setLabel(label);
                if (label != ""){
                    entry.setErrorFlag(true);
                    entry.setErrorMsg("*** ERROR: this statement can't have a label ***\n");
                }
                listingTable.push_back(entry);
                break;
            }
            else if (directives.count(mnemonic))
            {
                entry.setOpCode(mnemonic);
                entry.setAddress(incrementLocCounter(locCounter, 0));
                entry.setComment(comment);
                entry.setLabel(label);
                entry.setLineNumber(lineNumber);
                entry.setOperand(operand);
                if (label != ""){
                    if (symTable.count(label))
                    {
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: duplicate label definition ***\n");
                    }
                    else
                    {
                        symValue value;
                        value.setAddress(incrementLocCounter(locCounter, 0));
                        symTable[label] = value;
                    }
                }
                if (firstLine)
                {
                    if (mnemonic == "START")
                    {
                        if (operand == "")
                        {
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: missing starting address ***\n");
                        }
                        else
                        {
                            std::istringstream(operand) >> std::hex >> locCounter;
                            entry.setAddress(incrementLocCounter(locCounter, 0));
                            entry.setOpCode("START");
                            symTable.erase(label);
                        }
                    }
                    else
                    {
                        //error misplaced start
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: misplaced START ***\n");
                    }
                    firstLine = false;
                } else if (mnemonic == "BASE"){
                    if (operand == ""){
                       entry.setErrorFlag(true);
                       entry.setErrorMsg("*** ERROR: missing operand field ***\n");
                    }
                    if (label != ""){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: this statement can't have a label ***\n");
                    }
                } else if (mnemonic == "NOBASE"){
                    if (label != ""){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: this statement can't have a label ***\n");
                    }
                    if (operand != ""){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: this statement can't have an operand ***\n");
                    }
                } else if (mnemonic == "ORG"){
                    Expression exp;
                    exp.setLocctr(locCounter);
                    exp.SetSymTable(symTable);
                    exp.Setexpression(operand);
                    if (label != ""){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: this statement can't have a label ***\n");
                    }
                    else if (operand == ""){
                       entry.setErrorFlag(true);
                       entry.setErrorMsg("*** ERROR: missing operand field ***\n");
                    } else if (symTable.count(operand) == 0 && operand != "*"){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: undefined symbol in operand ***\n");
                    } else if (exp.validate()){
                        string s = exp.evaluate();
                        if (s == "ERROR"){
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: illegal expression ***\n");
                        } else if (s == "Undefined"){
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: undefined symbol in operand ***\n");
                        } else {
                            string temp = util.baseConverter(10, 16, exp.evaluate(), 4);
                            stringstream ss(temp);
                            ss >> std::hex >> locCounter;
                        }
                    }
                        else if (operand != "*") {
                            stringstream ss(symTable[operand].getAddress());
                            ss >> std::hex >> locCounter;
                        }
                        else if (symTable.count(operand) == 0 && operand != "*"){
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: undefined symbol in operand ***\n");
                        }
                    }
                    else if (mnemonic == "EQU"){
                    Expression exp;
                    exp.setLocctr(locCounter);
                    exp.SetSymTable(symTable);
                    exp.Setexpression(operand);
                    if (label == ""){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: missing label field ***\n");
                    }
                    else if (operand == ""){
                       entry.setErrorFlag(true);
                       entry.setErrorMsg("*** ERROR: missing operand field ***\n");
                    } else if (exp.validate()){
                        symValue newValue;
                        if (exp.validate()){
                            string s = exp.evaluate();
                            if (s == "ERROR"){
                                entry.setErrorFlag(true);
                                entry.setErrorMsg("*** ERROR: illegal expression ***\n");
                            } else if (s == "Undefined"){
                                entry.setErrorFlag(true);
                                entry.setErrorMsg("*** ERROR: undefined symbol in operand ***\n");
                            } else {
                                string temp = util.baseConverter(10, 16, exp.evaluate(), 4);
                                newValue.setAddress(temp);
                                // relative or absolute
                                if (exp.getExpressionType() == "relative"){
                                    newValue.setFlag(0);
                                } else {
                                    newValue.setFlag(1);
                                }
                                symTable[label] = newValue;
                            }
                        }  else if (operand == "*"){
                                newValue.setAddress(incrementLocCounter(locCounter, 0));
                                symTable[label] = newValue;
                        } else {
                                symTable[label] = symTable[operand];
                        }
                    } else if(symTable.count(operand) == 0 && operand != "*") {
                       entry.setErrorFlag(true);
                       entry.setErrorMsg("*** ERROR: undefined symbol in operand ***\n");
                    }
                }
                else if (mnemonic == "WORD" || mnemonic == "BYTE" || mnemonic == "RESW" || mnemonic == "RESB"){
                    entry.setOpCode(mnemonic);
                    if (operand == ""){
                        entry.setErrorFlag(true);
                    }
                    else if (mnemonic == "WORD"){
                        incrementLocCounter(locCounter, 3);
                    }
                    else if (mnemonic == "RESW"){
                        stringstream resw(operand);
                        int x;
                        resw >> x;
                        incrementLocCounter(locCounter, 3 * x);
                    } else if (mnemonic == "RESB"){
                        stringstream resb(operand);
                        int x;
                        resb >> x;
                        incrementLocCounter(locCounter, x);
                    } else if (mnemonic == "BYTE") {
                        int len = operand.length();
                        if (!len){
                            entry.setErrorFlag(true);
                            entry.setErrorMsg("*** ERROR: missing operand field ***\n");
                        }
                        if (len && len < 3){
                            entry.setErrorMsg("*** ERROR: illegal operand ***\n");
                            entry.setErrorFlag(true);
                        }
                        else if (operand[0] == 'X' && operand[1] == '\'' && operand[len - 1] == '\''){
                            if ((len - 3) & 1){
                                // checking for odd length
                                entry.setErrorFlag(true);
                                entry.setErrorMsg("*** ERROR: illegal operand ***\n");
                            } else if (!util.isHexaString(operand.substr(2, len - 3))){
                                entry.setErrorFlag(true);
                                entry.setErrorMsg("*** ERROR: not a hexadecimal string ***\n");
                            }
                            else {
                                incrementLocCounter(locCounter, (len - 3) / 2);
                            }
                        }
                        else if (operand[0] == 'C' && operand[1] == '\'' && operand[len - 1] == '\''){
                            incrementLocCounter(locCounter, (len - 3));
                        }
                        else {
                            entry.setErrorMsg("*** ERROR: illegal operand ***\n");
                            entry.setErrorFlag(true);
                        }
                    }
                }
            }

            else if (instructionFormat.count(mnemonic) || mnemonic[0] == '+')    // If format 4 or operation
            {
                //entry.errorFlag = false;
                entry.setAddress(incrementLocCounter(locCounter, 0));
                entry.setComment(comment);
                entry.setLabel(label);
                if (label != ""){
                    if (symTable.count(label))
                    {
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: duplicate label definition ***\n");
                    }
                    else
                    {
                        symValue value;
                        value.setAddress(incrementLocCounter(locCounter, 0));
                        symTable[label] = value;
                    }
                }
                entry.setLineNumber(lineNumber);
                if (mnemonic != "RSUB" && operand == ""){
                    entry.setErrorFlag(true);
                    entry.setErrorMsg("*** ERROR: missing operand field ***\n");
                }
                entry.setOperand(operand);
                if (mnemonic[0] == '+'){  // if format 4
                    mnemonic = mnemonic.substr(1, mnemonic.length() - 1);
                    entry.setOpCode("+" + mnemonic);
                    if (instructionFormat[mnemonic] != 3){
                        entry.setErrorFlag(true);
                        entry.setErrorMsg("*** ERROR: instruction cannot be format 4 ***\n");
                        listingTable.push_back(entry);
                        continue;
                    }
                    incrementLocCounter(locCounter, 4);
                } else {
                    entry.setOpCode(mnemonic);
                    if (instructionFormat[mnemonic] == 2){
                        if (mnemonic == "TIXR" || mnemonic == "CLEAR"){
                            if (!registerSet.count(operand)){
                                entry.setErrorFlag(true);
                                entry.setErrorMsg("*** ERROR: illegal address for a register ***\n");
                            } else {
                                incrementLocCounter(locCounter, 2);
                            }
                        }
                        else {
                            vector<string> tokens = util.tokenize(operand, ',');
                            if (tokens.size() < 2){
                                entry.setErrorFlag(true);
                                entry.setErrorMsg("*** ERROR: missing comma in operand field ***\n");
                            } else if(!registerSet.count(tokens[0]) || !registerSet.count(tokens[1])) {
                                entry.setErrorFlag(true);
                                entry.setErrorMsg("*** ERROR: illegal address for a register ***\n");
                            } else {
                                incrementLocCounter(locCounter, 2);
                            }
                        }
                    } else if (instructionFormat[mnemonic] == 3){
                        incrementLocCounter(locCounter, 3);
                    }
                }
            } else {
                entry.setErrorFlag(true);
                entry.setLineNumber(lineNumber);
                if (lineSize == 0){
                    entry.setErrorMsg("*** ERROR: missing operation code ***\n");
                } else
                    entry.setErrorMsg("*** ERROR: unrecognized operation code ***\n");
            }
            listingTable.push_back(entry);
        } else {
            // comment line case
            ListingEntry entry;
            comment = s;
            entry.setLineNumber(lineNumber);
            entry.setComment(comment);
            entry.setAddress("");
            entry.setErrorFlag(false);
            listingTable.push_back(entry);
        }
    }
    file.close();
    bool successfullPass1 = true;
    successfullPass1 = writeListingFile(fileName);
    return successfullPass1;
}

void Pass1Algorithm::openFile(ifstream& file, string fileName){
    file.open(fileName, ios::in);
    return;
}
void Pass1Algorithm::addComment(string &s, string comment){
    if (comment != ""){
        util.padTo(comment,35 + comment.size() - s.size());
        s += comment;
    }
}
bool Pass1Algorithm::writeListingFile(string fileName){
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

string Pass1Algorithm::incrementLocCounter(int &locCounter, int inc)
{
    std::stringstream sstream;
    locCounter = locCounter + inc;
    sstream << std::hex << locCounter;
    string result = sstream.str();
    switch ((int) result.size())
    {
    case 1 :
        result = "000" + result;
        break;
    case 2 :
        result = "00" + result;
        break;
    case 3 :
        result ="0" + result;
        break;
    }
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}


