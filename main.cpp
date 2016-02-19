/*

A simple listd shell for evaluating Scheme spells.

-> optional argument: file containing Scheme definitions.

Gajus Dirkzwager

 */

#include "Listd.h"

using namespace listd;

using sexprstd::writeSexpr;
using sexprstd::readSexpr;

int main(int argc, char* argv[]) {
  cout << endl;
  
  //register primitive functions to the global environment.
  registerPrimitives();

  //check input file.
  if (argc == 2)
    listd::loadPredefinitions(argv[1]);

  listd::input_buffer.setInputStream(stdin);

  //listd Read Eval Print Loop;
  while (1) {
    cout << "% ";
    writeSexpr(stdout,eval(readSexpr(),NIL));
    cout << endl;
  }

  cout << endl << "Later.." << endl << endl;
  return 0;
}
