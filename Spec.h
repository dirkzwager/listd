/*

Gajus Dirkzwager

Spec.h - Special forms (lambda, quote, if, cond).

 */

#ifndef __SPEC_H__
#define __SPEC_H__

#include "Base.h"

class Spec : public Base {
public:
  Base* func;
  Spec();
  Spec(Base* _func);
  ~Spec();
  virtual int operator == (Base*& b);
};

#endif
