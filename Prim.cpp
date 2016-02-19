#include "Prim.h"

Prim::Prim() : cprim(NULL) { type=PRIM; }

Prim::Prim(lFpt* _cprim) : cprim(_cprim) { type = PRIM; }

Prim::~Prim() { }

int Prim::operator == (Base*& b) {
  if (b->type != PRIM) return false;
  return ((Prim*)b)->cprim == cprim ? true : false;
}
