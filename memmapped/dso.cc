#include <iostream>
#include <random>
#include <map>
#include <string>
#include <cstring>
#include <vector>

#include "memmapped/api.h"

using namespace std;

typedef struct Context {
  int size;

  Attr* s;
  Attr* i;
  Attr* f;
  // TODO do lists.
};

// Initialize, not part of the benchmark.
extern Context* InitializeContext(int size) {
  Context* retval = new Context();
  default_random_engine rand;

  retval->s = new Attr[size];
  retval->i = new Attr[size];
  retval->f = new Attr[size];

  for (int i=0;i<size;i++) {
    retval->s[i].type = 1;
    strcpy(retval->s[i].data_, to_string(rand()).c_str());

    retval->i[i].type = 2;
    *reinterpret_cast<int*>(retval->i[i].data_) = rand();

    retval->f[i].type = 3;
    *reinterpret_cast<float*>(retval->f[i].data_) = rand() / 13.0;

    // TODO do lists
    //int rand_size = (rand()% 5) + 3;
    //for (int j=0;j<rand_size; j++) {
    //  retval->s_list["sl" + i].push_back(to_string(rand()).c_str());
    //  retval->i_list["il" + i].push_back(rand());
    //  retval->f_list["fl" + i].push_back(rand() / 12.0);
    //}
  }

  return retval;
}

extern void GetStringAttrs(Context* ctx, int* size, Attr** a) {
  *size = ctx->size;
  *a = ctx->s;
}
