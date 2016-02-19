/*
#ifndef __BUFFER_H__
#define __BUFFER_H__

#define int64 long long int

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <cctype>

#include <iostream>
using namespace std;

struct DATA {
  int size;
  int rpt, wpt;
  char* data;
  DATA();
  DATA(const int _size);
  char getc();
  int ungetc();
  int putc(char c);
  int unputc();
  void fill(const char* _data);
  void print();
};

struct Buffer {
  unsigned int64 max_size;
  DATA*   idp;
  FILE*   ifp;
  bool    la_valid;
  char*   token_la;
  char*   buffer;
  int     buffer_idx;
  int     buffer_type;
  
  Buffer();
  Buffer(const unsigned int64 _max_size);
  ~Buffer();

  void  setInputStream(FILE* fp);
  void  setInputStream(const char* _data);
  void  pushBuffer(char ch);
  char* buffer2string();
  void  putbackToken(char* token);
  char* getToken();
  char* getToken1();
  char* getToken2();
  void  setBuffer(const char* expr);
  void  printBuffer();
};

#endif
*/

///*
#ifndef __BUFFER_H__
#define __BUFFER_H__

#define int64 long long int

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <cctype>


struct Buffer {
  unsigned int64 max_size;
  FILE*   ifp;
  bool    la_valid;
  char*   token_la;
  char*   buffer;
  int     buffer_idx;
  
  Buffer();
  Buffer(const unsigned int64 _max_size);
  ~Buffer();

  void  setInputStream(FILE* fp);
  void  closeInputStream() { fclose(ifp); }
  void  pushBuffer(char ch);
  char* buffer2string();
  void  putbackToken(char* token);
  char* getToken();
};



#endif
//*/

