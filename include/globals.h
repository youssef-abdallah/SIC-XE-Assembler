#ifndef INCLUDED_GLOBALS_H
#define INCLUDED_GLOBALS_H

#include <unordered_map>
#include <unordered_set>
#include "symValue.h"

using namespace std;
extern unordered_map<string, string> opTab;
extern unordered_map<string, int> instructionFormat;
extern unordered_set<string> directives, registerSet;

#endif /* INCLUDED_GLOBALS_H */
