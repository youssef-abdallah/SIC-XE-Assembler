#include "symValue.h"

symValue::symValue()
{
    this->address = "";
    this->length = 0;
    this->flag = false; // 0 --> relative
}

symValue::~symValue()
{
    //dtor
}
