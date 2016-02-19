#include "Sym.h"

Sym::Sym() : name(NULL) { type=SYM; }

Sym::Sym(const std::string& _name) : name(strdup(_name.c_str())) { type = SYM; }

Sym::~Sym() { ; }

int Sym::operator == (Base*& b) {
  if (b->type != SYM) return false;
  else if (!strcmp(((Sym*)b)->name,name)) return true;
  return false;
}
