
#include "symValue.h"

symValue::symValue()
{
    this->address = "";
    this->length = 0;
    this->flag = Relative;
}

symValue::~symValue()
{
    //dtor
}
