/*

Gajus Dirkzwager

Pnt.h - Experimental.

 */


#ifndef __PNT_H__
#define __PNT_H__

#include "Base.h"

struct Point {
  int64 x,y;
  Point(int64 _x=0, int64 _y=0);
  ~Point();
};

class Pnt : public Base {
 public:
  Point value;
  Pnt();
  Pnt(const char* token);
  ~Pnt();
  virtual int operator == (Base*& b);
};

#endif
