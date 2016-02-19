#include "Pair.h"

Pair::Pair() : Base(PAIR) {}

Pair::Pair(Base* _car, Base* _cdr) : car(_car), cdr(_cdr) { type=PAIR; }

Pair::~Pair() { delete car; delete cdr; }

int Pair::operator == (Base*& b) {
  if (b->type != PAIR) return false;
  else if (((Pair*)b)->car == car && ((Pair*)b)->cdr) return true;
  return false;
}
