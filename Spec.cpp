#include "Spec.h"

Spec::Spec() : func(NULL) { type=SPEC; }

Spec::Spec(Base* _func) : func(_func) { type = SPEC; }

Spec::~Spec() { delete func; }

int Spec::operator == (Base*& b) {
  if (b->type != SPEC) return false;
  return ((Spec*)b)->func == func ? true : false;
}
