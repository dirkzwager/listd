/*

Gajus Dirkzwager

Listd.h - A Scheme implementation. Provides an extention language to C++ as well as simple interpreter.
Currently listd only 64-bit integers furthermore Scheme code cannot contain any comments... 

Also lambda notation is required for defining functions, for example:

(define curry-mult
  (lambda (y)
    (lambda (x)
      (* x y))))

and not:

(define (curry-mult y) 
   (lambda (x) (* x y)))

 */

#ifndef __LISTD_H__
#define __LISTD_H__

#include "Base.h"
#include "Pair.h"
#include "Int.h"
#include "Pnt.h"
#include "Sym.h"
#include "Str.h"
#include "Prim.h"
#include "Comp.h"
#include "Spec.h"
#include "Buffer.h"
#include "itoa.h"
#include <iostream>

using namespace std;

const static int MAXBUFFER = 128;

//namespace providing access to the listd extention language and interpreter for c++
namespace listd {
  static Buffer input_buffer(MAXBUFFER);
  static Base* NIL   = new Sym("()");;
  static Base* TEE   = NULL;
  static Base* QUOTE = NULL;

  //predicates
  bool isNIL(Base*);
  bool isTEE(Base*);

  //register
  void registerPrimitives();
  bool loadPredefinitions(const char* fname);

  //read eval apply print loop
  Base* eval(Base* sexpr, Base* env);
  Base* evalSeq(Base* seq, Base* env);
  Base* apply(Base* proc, Base* args);

  //constructors
  Base* Cons(Base*, Base*);
  Base* Append(Base*, Base*);

  //selectors
  Base*& Car(Base*);
  Base*& Cdr(Base*);
  Base*& Cadr(Base*);
  Base*& Caddr(Base*);

  //c++->lisp
  Base* c2l_Int(int64);
  Base* c2l_Sym(const char* name);
  Base* c2l_Str(const string& str);
  Base* c2l_Pnt(const char* value);
  Base* c2l_Prim(lFpt* prim);
  Base* c2l_Comp(Base* code, Base* syms, Base* env);
  Base* c2l_Spec(Base* func);

  //lisp->c++
  int64  l2c_Int(Base*);
  char*  l2c_Sym(Base*);
  string l2c_Str(Base*);
  Point  l2c_Pnt(Base*);
  string l2c_Str(Base*);
  lFpt*  l2c_Prim(Base*);

  //lisp->c++ unwrap
  Base*& l2c_CompCode(Base*);
  Base*& l2c_CompSyms(Base*);
  Base*& l2c_CompEnv(Base*);
  Base*& l2c_Spec(Base*);

  //lisp->lisp
  Int*  l2l_Int(Base*);
  Sym*  l2l_Sym(Base*);
  Str*  l2l_Str(Base*);
  Pnt*  l2l_Pnt(Base*);
  Pair* l2l_Pair(Base*);
  Prim* l2l_Prim(Base*);
  Comp* l2l_Comp(Base*);
  Spec* l2l_Spec(Base*);
 
  //specials 
  Base* set(Base* args);
  Base* setCdr(Base*& x, Base*& y);

  //print
  Base* writeInt(Base*);
  Base* writeSym(Base*);

  //c++->lisp bindings
  Base* prmCdr(Base* args);
  Base* prmCons(Base* args);
  Base* prmCar(Base* args);
  Base* prmAppend(Base* args);
  Base* prmDefine(Base* args);
  Base* prmSetCdr(Base* args);
  Base* prmEval(Base* args);
  Base* prmLambda(Base* args);
  Base* prmIf(Base* args);
  Base* prmCond(Base* args);
  Base* prmQuote(Base* args);
  Base* prmList(Base* args);
  Base* prmAnd(Base* args);
  Base* prmOr(Base* args);
  Base* prmNot(Base* args);
  Base* prmNAnd(Base* args);
  Base* prmNOr(Base* args);
  Base* prmXor(Base* args);
  Base* prmAdd(Base* args);
  Base* prmSub(Base* args);
  Base* prmMult(Base* args);
  Base* prmxLookup(Base* args);
  Base* printComp(Base* x);
  Base* prmSum(Base* args);
  Base* prmIsEq(Base* args);
  Base* prmIsMore(Base* args);
  Base* prmIsLess(Base* args);
  Base* prmInt2Str(Base* args);
  Base* prmStrAppend(Base* args);
  Base* prmStr2Sym(Base* args);
  Base* prmSym2Str(Base* args);
  Base* prmIsInt(Base* args);
  Base* prmIsSym(Base* args);
  Base* prmIsStr(Base* args);
  Base* prmIsPrim(Base* args);
  Base* prmIsComp(Base* args);
  Base* prmIsSpec(Base* args);
  Base* prmIsNIL(Base* args);
  Base* prmIsList(Base* args);
  Base* prmGlobalSyms(Base* args);
  Base* prmGlobalEnv(Base* args);
  Base* prmFindBind(Base* args);
  Base* prmTypeOf(Base* args);

  //routines for operating on symbols
  namespace symstd {
    static Base* global_symbol_table = NIL;
    Base* lookup (const char *name, Base*& stable=global_symbol_table);
    Base* xlookup(const char *name, Base*& stable=global_symbol_table);
  }

  //routines for operating on environments.
  namespace envstd {
    static Base* global_environment = Cons(Cons(NIL,NIL),NIL);
    Base* find(const char* key, Base* env=global_environment);
    Base* find(Base* key, Base* env=global_environment);
    Base* lookup(Base* key, Base* env=global_environment);
    void  extend(Base* sym, Base* val, Base*& env=global_environment);
    Base* multExtend(Base* sym, Base* val, Base* env);
  }

  //routines for casting spells
  namespace sexprstd {
    static FILE* rfile_pt = stdin;
    static FILE* wfile_pt = stdout;
    void  writeSexpr(FILE*, Base*);
    Base* readSexpr();
    Base* readList();
    //predicates
    bool  isRightParens(const char* ch); 
    bool  isLeftParens(const char* ch); 
    bool  isDot(const char* ch); 
    bool  isQuote(const char* ch); 
    bool  isNumber(const char* ch);
    bool  isPoint(const char* ch); 
    bool  isString(const char* ch);
    bool  isBind(const char* ch);
  }

  //A* algoritm
  namespace astarstd {
    static Base* oqueue = NIL;//open queue
    static Base* cqueue = NIL;//closed queue

    Base* Astar(Base* start, Base* goal, Base* map);
    Base* makeNode(Base* link, Base* mp, int64 c=0);
    Base* expandNode(Base*& node, Base* map);
    Base* push(Base* node, Base*& lst);
    Base* pop(string key, Base* lst);
    Base* del(string key, Base*& lst);
    Base* poptop(Base*& lst);
    Base* update(Base* key, Base* lst);
    Base* nodeSymbol(Base* node);
    Base* nodeFunction(Base* node);
    Base* funcValue(Base* func);
    Base* costValue(Base* func);
    Base* nodeLinks(Base* node);
    Base* linkSymbol(Base* node);
    Base* linkCost(Base* node);
    int64& cfuncValue(Base* func);
    int64& ccostValue(Base* func);
    string cnodeSymbol(Base* node);  
    Base* prmAstar(Base* args);
  }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//predicates
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool listd::isNIL(Base* X) {
  return X == NIL;
}

bool listd::isTEE(Base* X) {
  return X == TEE;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//REPL
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Base* listd::eval(Base* sexpr, Base* env) {
  Base* tmp = NULL;
  switch (sexpr->type) {
  case PAIR:
    tmp = eval(Car(sexpr),env);
    if (tmp->type == SPEC) 
      return apply(l2c_Spec(tmp),Cons(Cdr(sexpr),Cons(env,NIL)));
    else 
      return apply(tmp,evalSeq(Cdr(sexpr),env));
  case SYM:
    tmp = envstd::lookup(sexpr,env);
    if (isNIL(tmp)) 
      tmp = envstd::lookup(sexpr);
    if (isNIL(tmp)) {
      fprintf(stderr,"unbound symbol\n");
      return NIL;
    }
    else return Cdr(tmp);
  case INT:
  case STR:
  case PNT:
  case PRIM:
  case COMP:
  case SPEC:
    return sexpr;
  default: 
    fprintf(stderr,"Unknown type to eval\n");
  }
}

Base* listd::evalSeq(Base* seq, Base* env) {
  if (isNIL(seq)) return NIL;
  else return Cons(eval(Car(seq),env),evalSeq(Cdr(seq),env));
}

Base* listd::apply(Base* proc, Base* args) {
  Base* b;
  switch (proc->type) {
  case PRIM: 
    return l2c_Prim(proc)(args);
  case COMP:
    if (isNIL(l2c_CompSyms(proc)) || l2c_CompSyms(proc)->type == PAIR) 
      return eval(l2c_CompCode(proc),
		  envstd::multExtend(l2c_CompSyms(proc),
				     args,
				     l2c_CompEnv(proc)));
    else if (l2c_CompSyms(proc)->type == SYM) 
      return eval(l2c_CompCode(proc),
		  Cons(Cons(l2c_CompSyms(proc),args),
		       l2c_CompEnv(proc)));
    else {
      fprintf(stderr,"incorrect compound procedure to apply\n");
      exit(1);   
    } 
  default:
    fprintf(stderr,"unknown procedrue to apply\n");
    exit(1);
  }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Register
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//register primitive procedures and special forms to the global environment
void listd::registerPrimitives() {
  envstd::extend(symstd::xlookup("#f"),NIL);
  TEE = symstd::xlookup("#t");
  envstd::extend(TEE,TEE);
  envstd::extend(symstd::xlookup("cons"), 
		 c2l_Prim(prmCons));
  envstd::extend(symstd::xlookup("append"), 
		 c2l_Prim(prmAppend));
  envstd::extend(symstd::xlookup("list"), 
		 c2l_Prim(prmList));
  envstd::extend(symstd::xlookup("car"),  
		 c2l_Prim(prmCar));
  envstd::extend(symstd::xlookup("cdr"),  
		 c2l_Prim(prmCdr));
  envstd::extend(symstd::xlookup("+"),    
		 c2l_Prim(prmAdd));
  envstd::extend(symstd::xlookup("-"),    
		 c2l_Prim(prmSub));
  envstd::extend(symstd::xlookup("*"),    
		 c2l_Prim(prmMult));
  envstd::extend(symstd::xlookup("eval"), 
		 c2l_Prim(prmEval));
  envstd::extend(symstd::xlookup("lookup"), 
		 c2l_Prim(prmxLookup));
  envstd::extend(symstd::xlookup("set!"), 
		 c2l_Prim(set));
  envstd::extend(symstd::xlookup("setcdr!"), 
		 c2l_Prim(prmSetCdr));
  envstd::extend(symstd::xlookup("sum"), 
		 c2l_Prim(prmSum));
  envstd::extend(symstd::xlookup(">"), 
		 c2l_Prim(prmIsMore));
  envstd::extend(symstd::xlookup("<"), 
		 c2l_Prim(prmIsLess));
  envstd::extend(symstd::xlookup("eq?"), 
		 c2l_Prim(prmIsEq));
  envstd::extend(symstd::xlookup("int->string"), 
		 c2l_Prim(prmInt2Str));
  envstd::extend(symstd::xlookup("string-append"), 
  		 c2l_Prim(prmStrAppend));
  envstd::extend(symstd::xlookup("string->symbol"), 
		 c2l_Prim(prmStr2Sym));
  envstd::extend(symstd::xlookup("symbol->string"), 
		 c2l_Prim(prmSym2Str));
  envstd::extend(symstd::xlookup("number?"), 
		 c2l_Prim(prmIsInt));
  envstd::extend(symstd::xlookup("symbol?"), 
		 c2l_Prim(prmIsSym));
  envstd::extend(symstd::xlookup("string?"), 
		 c2l_Prim(prmIsStr));
  envstd::extend(symstd::xlookup("null?"), 
		 c2l_Prim(prmIsNIL));
  envstd::extend(symstd::xlookup("global-symbols"), 
		 c2l_Prim(prmGlobalSyms));
  envstd::extend(symstd::xlookup("global-environment"), 
		 c2l_Prim(prmGlobalEnv));
  envstd::extend(symstd::xlookup("find-bind"), 
 		 c2l_Prim(prmFindBind));
  envstd::extend(symstd::xlookup("not"), 
 		 c2l_Prim(prmNot));
  envstd::extend(symstd::xlookup("and"), 
 		 c2l_Prim(prmAnd));
  envstd::extend(symstd::xlookup("or"), 
 		 c2l_Prim(prmOr));
  envstd::extend(symstd::xlookup("nand"), 
 		 c2l_Prim(prmNAnd));
  envstd::extend(symstd::xlookup("nor"), 
 		 c2l_Prim(prmNOr));
  envstd::extend(symstd::xlookup("xor"), 
 		 c2l_Prim(prmXor));
  envstd::extend(symstd::xlookup("type-of"), 
 		 c2l_Prim(prmTypeOf));
  envstd::extend(symstd::xlookup("list?"), 
 		 c2l_Prim(prmIsList));
  envstd::extend(symstd::xlookup("A*"), 
 		 c2l_Prim(astarstd::prmAstar));
 
  envstd::extend(symstd::xlookup("quote"),  
		 c2l_Spec(c2l_Prim(prmQuote)));
  envstd::extend(symstd::xlookup("lambda"), 
		 c2l_Spec(c2l_Prim(prmLambda)));
  envstd::extend(symstd::xlookup("if"),     
		 c2l_Spec(c2l_Prim(prmIf)));
  envstd::extend(symstd::xlookup("cond"),     
		 c2l_Spec(c2l_Prim(prmCond)));
  envstd::extend(symstd::xlookup("define"), 
		 c2l_Spec(c2l_Prim(prmDefine)));

  QUOTE = symstd::xlookup("quote");
}

//load definitions from file
bool listd::loadPredefinitions(const char* fname) {
  int ch;
  FILE* input_file = fopen(fname,"r");
  input_buffer.setInputStream(input_file);
  if (input_file != NULL) {
    do {
      eval(sexprstd::readSexpr(),NIL);
      do ch = getc(input_file);
      while (isspace(ch) && ch != EOF);
      ungetc(ch,input_file);
    }
    while (ch != EOF);
    fclose(input_file);
    return true;
  }
  else {
    fprintf(stderr,"\nError opening file..\n");
    return false;
  }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Cons(tructors)
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Base* listd::Cons(Base* areg, Base* dreg) {
  Pair* X = new Pair;
  X->car = areg;
  X->cdr = dreg;
  return (Base*)X;
}

Base* listd::Append(Base* head, Base* tail) {
  if (isNIL(head)) return tail;
  return Cons(Car(head),Append(Cdr(head),tail));
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//selectors
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

inline Base*& listd::Car(Base* P) {
  return l2l_Pair(P)->car;
}

inline Base*& listd::Cdr(Base* P) {
  return l2l_Pair(P)->cdr;
}

inline Base*& listd::Cadr(Base* P) {
  return l2l_Pair(l2l_Pair(P)->cdr)->car;
}

inline Base*& listd::Caddr(Base* P) {
  return l2l_Pair((l2l_Pair((l2l_Pair(P)->cdr))->cdr))->car;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//c++->lisp
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Base* listd::c2l_Int(int64 value) {
  Int* I = new Int;
  I->value = value;
  return (Base*)I;
}

Base* listd::c2l_Sym(const char* name) {
  Sym* X = new Sym;
  X->name = strdup(name);
  return (Base*)X;
}

Base* listd::c2l_Str(const std::string& str) {
  Str* X = new Str(str);
  return (Base*)X;
}

Base* listd::c2l_Pnt(const char* value) {
  cout << "\nPnt\n";
  Pnt* X = new Pnt(value);
  return (Base*)X;
}

Base* listd::c2l_Prim(lFpt* prim) {
  Prim* X = new Prim;
  X->cprim = prim;
  return (Base*)X;
}

Base* listd::c2l_Comp(Base* code, Base* syms, Base* env) {
  Comp* X = new Comp;
  X->code = code;
  X->syms = syms;
  X->env  = env;
  return (Base*)X;
}

Base* listd::c2l_Spec(Base* func) {
  Spec* X = new Spec;
  X->func = func;
  return (Base*)X;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//lisp->c++
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

inline int64 listd::l2c_Int(Base* I) {
  return l2l_Int(I)->value;
}

inline char* listd::l2c_Sym(Base* C) {
  return l2l_Sym(C)->name;
}

inline string listd::l2c_Str(Base* S) {
  return l2l_Str(S)->str;
}

inline Point listd::l2c_Pnt(Base* P) {
  return l2l_Pnt(P)->value;
}
  
lFpt* listd::l2c_Prim(Base* P) {
  return l2l_Prim(P)->cprim;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//lisp->c++ unwrap
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

inline Base*& listd::l2c_CompCode(Base* C) {
  return l2l_Comp(C)->code;
}

inline Base*& listd::l2c_CompSyms(Base* C){
  return l2l_Comp(C)->syms;
}

inline Base*& listd::l2c_CompEnv(Base* C) {
  return l2l_Comp(C)->env;
}

inline Base*& listd::l2c_Spec(Base* S) {
  return l2l_Spec(S)->func;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//lisp->lisp
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	  
inline Int* listd::l2l_Int(Base* I) {
  return I->type == INT ? (Int*)I : NULL;
}

inline Sym* listd::l2l_Sym(Base* S) {
  return S->type == SYM ? (Sym*)S : NULL;
}

inline Str* listd::l2l_Str(Base* S) {
  return S->type == STR ? (Str*)S : NULL;
}

inline Pnt* listd::l2l_Pnt(Base* P) {
  return P->type == PNT ? (Pnt*)P : NULL;
}

inline Pair* listd::l2l_Pair(Base* P) {
  return P->type == PAIR ? (Pair*)P : NULL;
}

inline Prim* listd::l2l_Prim(Base* P) {
  return P->type == PRIM ? (Prim*)P : NULL;
}

inline Comp* listd::l2l_Comp(Base* C) {
  return C->type == COMP ? (Comp*)C : NULL;
}

inline Spec* listd::l2l_Spec(Base* S) {
  return S->type == SPEC ? (Spec*)S : NULL;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//specials
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Base* listd::set(Base* args) {
  if (Car(args)->type == Cadr(args)->type) {
    switch (Car(args)->type) {
    case INT:
      l2l_Int(Car(args))->value = l2l_Int(Cadr(args))->value;
      break;
    case SYM:
      l2l_Sym(Car(args))->name = strdup(l2l_Sym(Cadr(args))->name);
      break;
    default:
      fprintf(stderr,"type unimplemented\n");
      break;
    }
  }
  return Car(args);
}

Base* listd::setCdr(Base*& x, Base*& y) {
  if (isNIL(x)) 
    return y;
  else return Cons(Car(x),setCdr(Cdr(x),y));
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//print
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


Base* listd::writeInt(Base* I) {
  fprintf(stdout,"type:%d value:%lld\n",
	  ((Int*)I)->type,((Int*)I)->value);
}

Base* listd::writeSym(Base* S) {
  fprintf(stdout,"type:%i value:%s\n",
	  ((Sym*)S)->type,((Sym*)S)->name);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//c++->lisp bindings
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Base* listd::prmQuote(Base* args) {
  Base* sexpr = Car(args);
  return Car(sexpr);
}

Base* listd::prmList(Base* args) {
  return args;
}

Base* listd::prmLambda(Base* args) {
  Base* sexpr = Car(args);
  Base* env   = Cadr(args); 
  return c2l_Comp(Cadr(sexpr),Car(sexpr),env);
}

Base* listd::prmIf(Base* args) {
  Base* sexpr = Car(args);
  Base* env   = Cadr(args);
  return env;
  if (!isNIL(eval(Car(sexpr),env)))
    return eval(Cadr(sexpr),env);
  else return eval(Caddr(sexpr),env);
}

Base* listd::prmCond(Base* args) {
  Base* Cnd = Car(args);
  Base* env = Cadr(args);
  for (Cnd; !isNIL(Cnd); Cnd=Cdr(Cnd)) {
    if (!isNIL(eval(Car(Car(Cnd)),env)))
      return eval(Car(Cdr(Car(Cnd))),env);
  }
  return NIL;
}

Base* listd::prmDefine(Base* args) {
  Base* sexpr = Car(args);
  Base* env   = Cadr(args);
  Base* tmp   = NULL;

  if (Car(sexpr)->type != SYM)
    fprintf(stderr," not a Symbol.\n");
  tmp = envstd::lookup(Car(sexpr));
  if (isNIL(tmp)) 
    envstd::extend(Car(sexpr),eval(Cadr(sexpr),env));
  else Cdr(tmp) = eval(Cadr(sexpr),env);
  return Car(sexpr);  
}

Base* listd::prmSetCdr(Base* args) {
  setCdr(Car(args),Cdr(args));
}

Base* listd::prmEval(Base* args) {
  return eval(Car(args),Cadr(args));
}

Base* listd::prmCar(Base* args) {
  return Car(Car(args));
}

Base* listd::prmCdr(Base* args) {
  return Cdr(Car(args));
}

Base* listd::prmCons(Base* args) {
  return Cons(Car(args),Cadr(args));
}

Base* listd::prmAppend(Base* args) {
 Base* head = Car(args);
 Base* tail = Cadr(args);
 return Append(head,tail);
}

Base* listd::prmAnd(Base* args) {
  if (isNIL(args)) return TEE;
  else return (Car(args) == TEE && prmAnd(Cdr(args)) == TEE) ? TEE : NIL;
}

Base* listd::prmOr(Base* args) {
  if (isNIL(args)) return NIL;
  else return (Car(args) == TEE || prmOr(Cdr(args)) == TEE) ? TEE : NIL;
}

Base* listd::prmNot(Base* args) {
  return isNIL(Car(args)) ? TEE : isTEE(Car(args)) ? NIL : NIL;
}

Base* listd::prmNAnd(Base* args) {
  return isNIL(prmAnd(args)) ? TEE : NIL;
}

Base* listd::prmNOr(Base* args) {
  return isNIL(prmOr(args)) ? TEE : NIL;
}

Base* listd::prmXor(Base* args) {
  if (isNIL(args)) return TEE;
return 
  ((Car(args) == TEE) && (prmXor(Cdr(args)) == NIL)) 
    ? TEE :
  ((Car(args) == NIL) && (prmXor(Cdr(args)) == TEE)) ? TEE : NIL;
}

Base* listd::prmxLookup(Base* args) {
  return envstd::lookup(Car(args),Cadr(args));
}

Base* listd::prmAdd(Base* args) {
  int sum;
  for (sum=0; !isNIL(args); args=Cdr(args)) 
    sum += l2c_Int(Car(args));
  return c2l_Int(sum);
}

Base* listd::prmSub(Base* args) {
  int sum;
  if (isNIL(args)) return c2l_Int(0);
  sum = l2c_Int(Car(args));
  for (args=Cdr(args); !isNIL(args); args=Cdr(args))
    sum -= l2c_Int(Car(args));
  return c2l_Int(sum);
}

Base* listd::prmMult(Base* args) {
  Int* X = new Int;
  int a1 = ((Int*)Car(args))->value;
  int a2 = ((Int*)Cadr(args))->value;
  X->value = a1*a2;
  return X;
}

Base* listd::prmSum(Base* args) {
  int64 sum=0;
  if (isNIL(args)) return c2l_Int(sum);
  for (sum=0; !isNIL(args); sum+=l2c_Int(Car(args)), args = Cdr(args));
  return c2l_Int(sum);
}

Base* listd::prmIsEq(Base* args) {
  Base* a = Car(args);
  Base* b = Cadr(args);
  if (a->type != b->type) return NIL;
  else {
    switch (a->type) {
    case INT: return ((Int*)a)->value == ((Int*)b)->value ? TEE : NIL;
    case SYM: return ((Sym*)a)->name == ((Sym*)b)->name ? TEE : NIL;
    default: NIL;
    }
  }
}

Base* listd::prmIsLess(Base* args) {
  Base* a = Car(args);
  Base* b = Cdr(args);
  if (a->type != b->type) return NIL;
  else {
    switch (a->type) {
    case INT: return ((Int*)a)->value < ((Int*)b)->value ? TEE : NIL;
    case SYM: return ((Sym*)a)->name < ((Sym*)b)->name ? TEE : NIL;
    default: return NIL;
    }
  }
}

Base* listd::prmIsMore(Base* args) {
 Base* a = Car(args);
  Base* b = Cdr(args);
  if (a->type != b->type) return NIL;
  else 
    switch (a->type) {
    case INT: return ((Int*)a)->value > ((Int*)b)->value ? TEE : NIL;
    case SYM: return ((Sym*)a)->name > ((Sym*)b)->name ? TEE : NIL;
    default: return NIL;
    }
  
}

Base* listd::prmInt2Str(Base* args) {
  args = Car(args);
  if (args->type != INT) return NIL;

  char* str = new char;
  itoa(l2c_Int(args),str,10);
  return c2l_Str(str);
}

Base* listd::prmStrAppend(Base* args) {
  string str = l2l_Str(Car(args))->str;
  str.append(l2l_Str(Cadr(args))->str);
  Str* S = new Str(str);
  return (Base*)S;  
}

Base* listd::prmStr2Sym(Base* args) {
  Sym* S = new Sym(l2l_Str(Car(args))->str.c_str());
  return (Base*)S;
}

Base* listd::prmSym2Str(Base* args) {
  Str* S = new Str(string(l2l_Sym(Car(args))->name));
  return (Base*)S;
}

Base* listd::prmIsInt(Base* args) {
  return Car(args)->type == INT ? TEE : NIL;
}

Base* listd::prmIsSym(Base* args) {
  return Car(args)->type == SYM ? TEE : NIL;
}

Base* listd::prmIsStr(Base* args) {
  return Car(args)->type == STR ? TEE : NIL;
}

Base* listd::prmIsPrim(Base* args) {
  return Car(args)->type == PRIM ? TEE : NIL;
}

Base* listd::prmIsComp(Base* args) {
  return Car(args)->type == COMP ? TEE : NIL;
}

Base* listd::prmIsSpec(Base* args) {
  return Car(args)->type == INT ? TEE : NIL;
}

Base* listd::prmIsNIL(Base* args) {
  return isNIL(Car(args)) ? TEE : NIL;
}

Base* listd::prmIsList(Base* args) {
  return isNIL(Car(args)) || Car(args)->type == PAIR ? TEE : NIL;
}

Base* listd::prmGlobalSyms(Base* args) {
  return symstd::global_symbol_table;
}

Base* listd::prmGlobalEnv(Base* args) {
  return envstd::global_environment;
}

Base* listd::prmFindBind(Base* args) {
  Base* X = Car(args);
  if (X->type != SYM) return Cons(NIL,NIL);
  return envstd::find(Car(args));
}

Base* listd::prmTypeOf(Base* args) {
  return c2l_Int(Car(args)->type);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//symbol table
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Base* listd::symstd::lookup(const char *name, Base*& stable) {
  Base *el = stable;
  for(el; !isNIL(el); el = Cdr(el))
    if(!strcmp(name, l2c_Sym(Car(el))))
      return el;
  return NIL;
}

Base* listd::symstd::xlookup(const char *name, Base*& stable) {
  Base *el = lookup(name,stable);
  if(!isNIL(el)) return Car(el);
  el = c2l_Sym(name);
  stable = Cons(el,stable);
  return el;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//environment
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Base* listd::envstd::find(const char* key, Base* env) {
  Base* entry = NULL;//env;
  for (entry=env; !isNIL(Car(entry)); entry = Cdr(entry)) {
    if (!strcmp(key, ((Sym*)Car(Car(entry)))->name))
      break;
  }
  if (isNIL(entry)) return Cons(NIL,NIL);
  return Car(entry);
}

Base* listd::envstd::lookup(Base* key, Base* env) {
  Base* entry = env;
  for (entry; !isNIL(entry) && key != Car(Car(entry)); entry = Cdr(entry));
  if (isNIL(entry)) return NIL;
  return Car(entry);
}

Base* listd::envstd::find(Base* key, Base* env) {
  Base* entry = global_environment;
  const char* ch = ((Sym*)key)->name;
  for (entry; !isNIL(entry); entry = Cdr(entry)) {
    if (!strcmp(ch,l2l_Sym(Car(Car(entry)))->name))
      break;
  }
  if (isNIL(entry)) return Cons(NIL,NIL);
  return Car(entry);
}

Base* listd::envstd::multExtend(Base* syms, Base* vals, Base* env) {
  if (isNIL(vals) && isNIL(syms)) 
    return env;
  else if (!isNIL(vals) && isNIL(syms)) {
    fprintf(stderr,"Binding error: values > variables.\n");
    exit(1);
  }
  else if (isNIL(vals) && !isNIL(syms)) {
    fprintf(stderr,"Binding error: values < variables.\n");
    exit(1);
  }
  else return Cons(Cons(Car(syms),Car(vals)),
  		   multExtend(Cdr(syms),Cdr(vals),env));
}

//binds a Int to a Sym & adds this to an environment.
void listd::envstd::extend(Base* sym, Base* val, Base*& env) {
  Base* tmp = env;
  for (tmp; !isNIL(Cdr(tmp)); tmp=Cdr(tmp));
  Cdr(tmp) = Cons(Cons(sym,val),NIL);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//S-Expressions
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void listd::sexprstd::writeSexpr(FILE* out, Base* sexpr) {
  switch (sexpr->type) {
  case PAIR:
    fprintf (stderr, "(");
    writeSexpr(stderr,Car(sexpr));
    sexpr = Cdr(sexpr);
    while (sexpr->type == PAIR) {
      fprintf (stderr, " ");
      writeSexpr(stderr, Car(sexpr));
      sexpr = Cdr(sexpr);
    }
    if (sexpr == NIL)
	fprintf (stderr, ")");
    else {
      fprintf (stderr, " . ");
      writeSexpr(stderr, sexpr);
      fprintf (stderr, ")");
    }
    break;
  case INT: 
    fprintf (stderr, "%lld", l2c_Int(sexpr));
    break;
  case SYM:
    fprintf (stderr, "%s", l2c_Sym(sexpr));
    break;
  case STR:
    fprintf (stderr, "\"%s\"", l2c_Str(sexpr).c_str());
    break;
  case PNT: 
    fprintf (stderr, "[%lld %lld]", l2c_Pnt(sexpr).x, l2c_Pnt(sexpr).y);
    break;
  case PRIM:
    fprintf (stderr, "#<primitive function>");
    break;
  case COMP:
    fprintf (stderr, "#<compound function>");
    break;
  case SPEC:
    fprintf (stderr, "#<special form>");
    break;
  default:
    fprintf (stderr, "Error, invalid S-expression..");
  }
}

Base* listd::sexprstd::readSexpr () {
  char* token = input_buffer.getToken();
  if (isLeftParens(token)) return readList();
  if (isQuote(token))      return Cons(QUOTE,Cons(readSexpr(),NIL));
  if (isNumber(token))     return c2l_Int(atoi(token));
  if (isString(token))     return c2l_Str(string(token));
  return symstd::xlookup(token,symstd::global_symbol_table);
}

Base* listd::sexprstd::readList() {
  char* token = input_buffer.getToken();
  Base* tmp;
  if (isRightParens(token)) return NIL;  
  if (isDot(token)) {
    tmp = readSexpr();
    if (!isRightParens(input_buffer.getToken())) {
      fprintf(stderr,"eol");
      exit(1);
    }
    return tmp;
  }
  input_buffer.putbackToken(token);
  tmp = readSexpr();
  return Cons(tmp,readList());
}

inline bool listd::sexprstd::isRightParens(const char* ch) { 
  return !strcmp(ch,")"); 
}

inline bool listd::sexprstd::isLeftParens(const char* ch) { 
  return !strcmp(ch,"("); 
}

inline bool listd::sexprstd::isDot(const char* ch) { 
  return !strcmp(ch,"."); 
}

inline bool listd::sexprstd::isQuote(const char* ch) { 
  return !strcmp(ch,"\'"); 
}

inline bool listd::sexprstd::isNumber(const char* ch) {
  return ch[0] == '-' ? strspn(ch+1,"0123456789") : strspn(ch,"0123456789");
}

inline bool listd::sexprstd::isPoint(const char* ch) {
  if (ch[0] != '[') return false;
  int spn = strspn(ch+1," 0123456789");
  if (ch[spn+1] != ']') 
    return false;
  return true;
}

inline bool listd::sexprstd::isString(const char* ch) { 
  if (ch[0] != '\"') return false;
  int i=1;
  while (ch[i] != '\0' && ch[i] != '\"') i++;
  if (ch[i] != '\"') return false;
  return true;  
}

inline bool listd::sexprstd::isBind(const char* ch) {
  return !strcmp(ch,"&");
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  namespace astarstd uses the lisp primitives from namespace listd to implement a 
  compiled A* algoritm.
  Basically the c++ function "prmAstar" is registered to the global lisp environment
  as "A*". 

  so:
  % A*
  #<primitive function>

  and:
  (A* 'start-node 'goal-node map) -> Base* listd::astarstd::prmAstar(Base* args);

    *functions named prm..... are primitives through which lisp acesses the 
    compiled primitives. prmAstar therefore passes on its arguments to function Astar.

  A* is computed by first defining a map, as an example the map of romania is used.
  each element in the list specifies a template for a node in the following order.
  
    (symbol heuristic ((linkA cost) (linkB cost) ()))

  !!!!!!!!!!!MAKE SURE TO END THE LIST OF LINKS WITH: NIL, ie: () !!!!!!!!!!!!
  is nog een of ander bugje dat meer tijd en moeite gaat costen..

  (define romania '((A 374 ((B  71) (X  75) ()))
		    (B 380 ((A  71) (C 151) ()))
		    (C 253 ((B 151) (X 140) (E  99) (F  80) ()))
		    (D 329 ((X 118) (I 111) ()))
		    (E 176 ((C  99) (Y 211) ()))
		    (F 193 ((C  80) (G  97) (H 146) ()))
		    (G 100 ((F  97) (Y 101) (H 138) ()))
		    (H 160 ((K 120) (F 146) (G 138) ())) 
		    (I 244 ((D 111) (J  70) ()))
		    (J 241 ((I  70) (K  75) ()))
		    (K 242 ((J  75) (H 120)))
		    (L  77 ((Y  90) ()))
		    (M  80 ((Y  85) ()))
		    (X 366 ((A  75) (C 140) (D 118) ()))
		    (Y   0 ((E 211) (G 101) (L  90) (M  85) ()))))

  (je kunt het bovenstaande plakken in de interpreter of laden door een bestand als argument
  naar het programma gebruiken, bijv: ./listd map.scm)

  Shortest distance from X to Y is then computed with:
  
    (A* '(X 0) 'Y map)
    result: (Y (418 418 0) ((E 211) (G 101) (L 90) (M 85) ()))


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//A* algorithm. Takes 2 symbols eg. 'S 'G and a map
Base* listd::astarstd::Astar(Base* start_node, Base* goal_node, Base* map) {
  string goal = string(l2c_Sym(goal_node));
  Base* current_node = makeNode(start_node,map);

  current_node = expandNode(current_node,map);

  while (!isNIL(oqueue)) {
    current_node = poptop(oqueue);
    if (cnodeSymbol(current_node) == goal) 
      return current_node;
    current_node = expandNode(current_node,map);
  }
  return NIL;
}

//constructs a node from a link, eg. '(C 140), a map and cost of the parent node
Base* listd::astarstd::makeNode(Base* link, Base* mp, int64 c) {
  Base* symbol = linkSymbol(link);
  Base* g = (Base*)(new Int((((Int*)linkCost(link))->value+c)));
  Base* h = Cadr(pop(l2c_Sym(symbol),mp));
  int64 f = l2c_Int(g) + l2c_Int(h);

  Base* func = Cons((Base*)(new Int(f)),Cons(g,Cons(h,NIL)));
  Base* links = nodeLinks(pop(l2c_Sym(symbol),mp));
  return Cons(symbol,Cons(func,Cons(links,NIL)));
}

//updates the open & closed queues by extending the links of a node
Base* listd::astarstd::expandNode(Base*& node, Base* map) {
  Base* links = nodeLinks(node);
  for (links; !isNIL(Car(links)); links=Cdr(links)) 
    oqueue = update(makeNode(Car(links),map,ccostValue(node)),oqueue);
  cqueue = update(node,cqueue);
  return node;
}

//pushes a node onto a list ordered by the nodes f-value
Base* listd::astarstd::push(Base* node, Base*& lst) {
  if (isNIL(lst)) return Cons(node,NIL);
  else {
    if (cfuncValue(node) < cfuncValue(Car(lst))) 
      return Cons(node,Cons(Car(lst),Cdr(lst)));
    else 
      return Cons(Car(lst),push(node,Cdr(lst)));
  }
}

//pops a node from a list according to its id.
Base* listd::astarstd::pop(string key, Base* lst) {
  Base* entry = NULL;;
  for (entry=lst; !isNIL(Car(entry)); entry = Cdr(entry)) {
    if (key == string(((Sym*)Car(Car(entry)))->name))
      break;
  }
  if (isNIL(entry)) return NIL;
  return Car(entry);
}

//deletes a node from a list according to its id
Base* listd::astarstd::del(string key, Base*& lst) {
  if (isNIL(lst)) return NIL;
  else {
    if (key == cnodeSymbol(Car(lst)))
      return Cdr(lst);
    else 
      return Cons(Car(lst),del(key,Cdr(lst)));
  }
}

//pops the top node off a list and sets list 2 the cdr of list
Base* listd::astarstd::poptop(Base*& lst) {
  Base* top = Car(lst);
  lst = Cdr(lst);
  return top;
}

//maintains best-node on a list
Base* listd::astarstd::update(Base* key, Base* lst) {
  Base* tmp = listd::envstd::lookup(nodeSymbol(key),lst);
  if (isNIL(tmp)) {
    lst = push(key,lst);
    return lst;
  }
  else {
    int64 fkey = cfuncValue(key);
    int64 ftmp = cfuncValue(tmp);
    if (fkey <= ftmp) {
      lst = del(cnodeSymbol(tmp),lst);
      lst = push(key,lst);
      return lst;
    }
    else return lst;
  }
}

//returns the identifier of a node (A (10 0 10) ((B 20) (C 30))) -> A
inline Base* listd::astarstd::nodeSymbol(Base* node) { 
  return Car(node); 
}

//returns the node function  (A (10 0 10) ((B 20) (C 30))) -> (10 0 10)
inline Base* listd::astarstd::nodeFunction(Base* node) { 
  return Cadr(node); 
}

//returns cost-value of a function (10 0 10) -> 0
inline Base* listd::astarstd::funcValue(Base* func) { 
  return Car(nodeFunction(func)); 
}

//returns the node-links of a node (A (10 0 10) ((B 20) (C 30))) -> ((B 20) (C 30))
inline Base* listd::astarstd::costValue(Base* func) { 
  return Cadr(nodeFunction(func)); 
}

//returns function value of a function (10 0 10) -> 10
inline int64& listd::astarstd::cfuncValue(Base* func) {
  return ((Int*)Car(nodeFunction(func)))->value;
}

//returns the identifier of a link (B 20) -> B
inline int64& listd::astarstd::ccostValue(Base* func) {
  return ((Int*)Cadr(nodeFunction(func)))->value;
}

//returns the cost of a link (B 20) -> 20
inline string listd::astarstd::cnodeSymbol(Base* node) {
  return string(((Sym*)Car(node))->name);
}

//returns function value of a function (10 0 10) -> 10 as a 64-bit integer
inline Base* listd::astarstd::nodeLinks(Base* node) {
  return Caddr(node);
}

//returns cost-value of a function (10 0 10) -> 0 as a 64-bit integer
inline Base* listd::astarstd::linkSymbol(Base* link) {
  return Car(link);
}

//returns cost-value of a function (10 0 10) -> 0 as a string
inline Base* listd::astarstd::linkCost(Base* link) {
  return Car(Cdr(link));
}

//function providing lisp access to the c++ A* algorithm
Base* listd::astarstd::prmAstar(Base* args) {
  Base* start_node = Car(args);
  Base* goal_node = Cadr(args);
  Base* map = Caddr(args);

  return Astar(start_node,goal_node,map);
}

#endif
