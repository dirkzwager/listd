/*

Gajus Dirkzwager

Str.h - Primitive data type string.

 */

#ifndef __STR_H__
#define __STR_H__

#include "Base.h"

class Str : public Base {
public:
  std::string str;
  Str();
  Str(const std::string& _str);
  ~Str();
  virtual int operator == (Base*& b);
};

#endif
