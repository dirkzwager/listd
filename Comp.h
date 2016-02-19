/*

Gajus Dirkzwager

Comp.h - Compound procedures, provides means for abstration in a language. 

For example:

% (define square (lambda (x) (* x x)))
square
% square
#<compound function>

 */

#ifndef __COMP_H__
#define __COMP_H__

#include "Base.h"

class Comp : public Base {
public:
  Base* code;
  Base* syms;
  Base* env;
  Comp();
  Comp(Base* _code, Base* _syms, Base* env);
  ~Comp();
  virtual int operator == (Base*& b);
};

#endif
