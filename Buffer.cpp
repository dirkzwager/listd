#include "Buffer.h"

/*
DATA::DATA() {

}

DATA::DATA(const int _size) {
  size=_size;
  rpt = wpt = 0;
  data = new char[size];
  for (int i=0; i<size; i++) data[i]=0;
  //fill("(define x 1);");
}

char DATA::getc() {
  if (!(rpt<size-1)) return 0;
  return data[rpt++];
}

int DATA::ungetc() {
  rpt--;
}

int DATA::putc(char c) {
  data[wpt++] = c;
}

int DATA::unputc() {
  wpt--;
}

void DATA::fill(const char* _data) {
  wpt=0;
  int i=0;
  while (_data[i] != ';') putc(_data[i++]);
}

void DATA::print() {
  cout << "Buffer# ";
  for (int i=0; i<wpt; i++) cout << data[i];
  cout << endl;
}


Buffer::Buffer() : max_size(0), ifp(NULL), 
                   la_valid(false), token_la(0), 
                   buffer(NULL), buffer_idx(0) { }

Buffer::Buffer(const unsigned int64 _max_size) : max_size(_max_size), ifp(NULL), 
                                                 la_valid(false), token_la(0), 
                                                 buffer(new char[_max_size]), buffer_idx(0) { }

Buffer::~Buffer() {}

void Buffer::setInputStream(FILE* fp) {
  ifp = fp;
  buffer_type = 0;
}

void Buffer::setInputStream(const char* _data) {
  idp = new DATA(512);
  idp->fill(_data);
  buffer_type = 1;
}

void Buffer::pushBuffer(char ch) {
  if (buffer_idx<max_size-1)
    buffer[buffer_idx++] = ch;
  else fprintf(stderr,"Warning buffer overflow..\n");
}

char* Buffer::buffer2string() {
  buffer[buffer_idx++] = '\0';
  return strdup(buffer);
}

void Buffer::putbackToken(char* token) {
  token_la = token; 
  la_valid=true; 
}

char* Buffer::getToken() {
  const int filebuffer = 0;
  const int databuffer = 1;
  if (buffer_type == filebuffer)
    return getToken1();
  else if (buffer_type == databuffer)
    return getToken2();
  else fprintf(stderr,"buffer error\n");
}

char* Buffer::getToken2() {
  int ch;
  buffer_idx = 0;

  if (la_valid) { 
    la_valid = false; 
    return token_la; 
  }  
  do {
    if ((ch=idp->getc()) == EOF) exit(0);
  } while (isspace(ch));
  pushBuffer(ch);
  if (strchr("()\'",ch)) return buffer2string();
  for (;;) {
    if ((ch=idp->getc()) == EOF) exit(0);
    if (strchr("()\'",ch) || isspace(ch)) {
      idp->ungetc();
      return buffer2string();
    }
    pushBuffer(ch);
  }
}

char* Buffer::getToken1() {
  int ch;
  buffer_idx = 0;

  if (la_valid) { 
    la_valid = false; 
    return token_la; 
  }  
  do {
    if ((ch=getc(ifp)) == EOF) exit(0);
  } while (isspace(ch));
  pushBuffer(ch);
  if (strchr("()\'",ch)) return buffer2string();
  for (;;) {
    if ((ch=getc(ifp)) == EOF) exit(0);
    if (strchr("()\'",ch) || isspace(ch)) {
      ungetc(ch,ifp);
      return buffer2string();
    }
    pushBuffer(ch);
  }
}

void Buffer::setBuffer(const char* expr) {
  int i=0;
  while (expr[i] != ';') {
    buffer[i]=expr[i];
    i++;
  }
}

void Buffer::printBuffer() {
  cout << "Buffer: " << endl;
  for (int i=0; i<buffer_idx; i++) cout << buffer[i] << " ";
  cout << endl;
}
*/



Buffer::Buffer() : max_size(0), ifp(NULL), 
                   la_valid(false), token_la(0), 
                   buffer(NULL), buffer_idx(0) { }

Buffer::Buffer(const unsigned int64 _max_size) : max_size(_max_size), ifp(NULL), 
                                                 la_valid(false), token_la(0), 
                                                 buffer(new char[_max_size]), buffer_idx(0) { }

Buffer::~Buffer() {}

void Buffer::setInputStream(FILE* fp) {
  ifp = fp;
}

void Buffer::pushBuffer(char ch) {
  if (buffer_idx<max_size-1)
    buffer[buffer_idx++] = ch;
  else fprintf(stderr,"Warning buffer overflow..\n");
}

char* Buffer::buffer2string() {
  buffer[buffer_idx++] = '\0';
  return strdup(buffer);
}

void Buffer::putbackToken(char* token) {
  token_la = token; 
  la_valid=true; 
}

char* Buffer::getToken() {
  int ch;
  buffer_idx = 0;

  if (la_valid) { 
    la_valid = false; 
    return token_la; 
  }  
  do {
    if ((ch=getc(ifp)) == EOF) exit(0);
  } while (isspace(ch));
  pushBuffer(ch);
  if (strchr(",",ch)) {
    ch=getc(ifp);
  }
  if (strchr("()\'",ch)) return buffer2string();
  for (;;) {
    if ((ch=getc(ifp)) == EOF) exit(0);
    if (strchr(",",ch)) {
      ch=getc(ifp);
    }
    if (strchr("()\'",ch) || isspace(ch)) {
      ungetc(ch,ifp);
      return buffer2string();
    }
    pushBuffer(ch);
  }
}

