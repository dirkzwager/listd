/*

Gajus Dirkzwager

Prim.h - Primitive Procedure (*, +, -, /, <, >, car, cdr, eval, etc).

 */

#ifndef __PRIM_H__
#define __PRIM_H__

#include "Base.h"

class Prim : public Base {
public:
  lFpt* cprim;
  Prim();
  Prim(lFpt* _cprim);
  ~Prim();
  virtual int operator == (Base*& b);
};

#endif
