#include "Str.h"

Str::Str() : str("") { type=STR; }

Str::Str(const std::string& _str) : str(_str) { 
  type = STR; 
  if (str[0] == '\"' && str[str.length()-1] == '\"') {
    str.erase(0,1);
    str.erase(str.length()-1,1);
  }
}

Str::~Str() { ; }

int Str::operator == (Base*& b) {
  if (b->type != STR) return false;
  return (((Str*)b)->str == str) ? true : false;
}
