#include "Comp.h"

Comp::Comp() : code(NULL), syms(NULL), env(NULL) { type=COMP; }

Comp::Comp(Base* _code, 
	   Base* _syms, 
	   Base* _env) 
: code(_code), syms(_syms), env(_env) { type = COMP; } 

Comp::~Comp() { delete code; delete syms; delete env; }

int Comp::operator == (Base*& b) {
  if (b->type != COMP) return false;
  return (((Comp*)b)->code == code &&
	  ((Comp*)b)->syms == syms &&
	  ((Comp*)b)->env  == env) ? true : false;
}
