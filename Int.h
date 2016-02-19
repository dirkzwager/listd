/*

Gajus Dirkzwager

Int.h - Primitive data type number (long long int).

 */

#ifndef __INT_H__
#define __INT_H__

#include "Base.h"

class Int : public Base {
 public:
  int64 value;
  Int();
  Int(const int64& _value);
  ~Int();
  virtual int operator == (Base*& b);
};

#endif
