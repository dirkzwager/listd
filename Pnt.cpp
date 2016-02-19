#include "Pnt.h"

Point::Point(int64 _x, int64 _y) : x(_x), y(_y) {}

Point::~Point() {}

Pnt::Pnt() : Base(PNT) {

}

Pnt::Pnt(const char* token) { 
  
  type = PNT; 

  int space = strspn(token+1,"0123456789");
  int end   = strspn(token+space+2,"0123456789");

  char* buff = new char[space+end-1];
  
  strncpy(buff,token+1,space);
  value.x = atoi(buff);

  strncpy(buff,token+space+2,end);
  value.y = atoi(buff);

  delete[] buff;
}

Pnt::~Pnt() {}

int Pnt::operator == (Base*& b) {
  if (b->type != PNT) return false;
  else if (((Pnt*)b)->value.x == value.x && 
	   ((Pnt*)b)->value.y == value.y) return true;
  return false;
}
