#include<stdint.h>
#include<stdio.h>
#include<time.h>
#define PRINTF(X) printf("Size of %s: %lu\n",name[i],sizeof(X))

int main(){
  char name[20][20]={"char","short","short int","int","long int","unsigned int","void*","size_t",
                      "float","double","int8_t","int16_t","int32_t","int64_t","time_t","clock_t","struct tm",
                    "NULL"};
  int i=0;
  char a;
  short b=0;
  short int c=0;
  int d=0;
  long int e=0;
  unsigned int f=0;
  void* g;
  size_t h;
  float j;
  double k;
  int8_t l;
  int16_t m;
  int32_t n;
  int64_t o;
  time_t p;
  clock_t r;
  struct tm s;
  char* t=NULL;
  PRINTF(a);i++;
  PRINTF(b);i++;
  PRINTF(c);i++;
  PRINTF(d);i++;
  PRINTF(e);i++;
  PRINTF(f);i++;
  PRINTF(g);i++;
  PRINTF(h);i++;
  PRINTF(j);i++;
  PRINTF(k);i++;
  PRINTF(l);i++;
  PRINTF(m);i++;
  PRINTF(n);i++;
  PRINTF(o);i++;
  PRINTF(p);i++;
  PRINTF(r);i++;
  PRINTF(s);i++;
  PRINTF(t);i++;
  return 0;
}
