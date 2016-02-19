/*

Gajus Dirkzwager

Pair.h - Single cell of a list, also known as a cons. Each pair consists of a pointer to the content address register (head of the list), and the content data register, the tail of the list.

 */



#ifndef __PAIR__H_
#define __PAIR__H_

#include "Base.h"

class Pair : public Base {
 public:
  Base* car;
  Base* cdr;
  Pair();
  Pair(Base* _car, Base* _cdr);
  ~Pair();
  virtual int operator == (Base*& b);
};

#endif
