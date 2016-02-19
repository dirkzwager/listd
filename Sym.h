/*

Gajus Dirkzwager

Sym.h - Primitive datatype representing a lisp symbol.

 */

#ifndef __SYM_H__
#define __SYM_H__

#include "Base.h"

class Sym : public Base {
public:
  char* name;
  Sym();
  Sym(const std::string& _name);
  ~Sym();
  virtual int operator == (Base*& b);
};

#endif
