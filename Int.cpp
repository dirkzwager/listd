#include "Int.h"

Int::Int() : Base(INT) {}

Int::Int(const int64& _value) : value(_value) { type = INT; }

Int::~Int() {}

int Int::operator == (Base*& b) {
  std::cout << "\nint ==\n";
  if (b->type != INT) return false;
  else if (((Int*)b)->value == value) return true;
  return false;
}
