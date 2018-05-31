
#include <iostream>
#include <random>
#include <map>
#include <string>
#include <vector>

#include "opaque/api.h"

using namespace std;

typedef struct Context {
  map<string, string> s;
  map<string, int> i;
  map<string, float> f;
  map<string, vector<const char*> > s_list;
  map<string, vector<int> > i_list;
  map<string, vector<float> > f_list;
};

// Initialize, not part of the benchmark.
extern Context* InitializeContext(int size) {
  Context* retval = new Context();
  default_random_engine rand;
  for (int i=0;i<size;i++) {
    retval->s["s" + i] = to_string(rand());
    retval->i["i" + i] = rand();
    retval->f["f" + i] = rand() / 12.0;

    int rand_size = (rand()% 5) + 3;
    for (int j=0;j<rand_size; j++) {
      retval->s_list["sl" + i].push_back(to_string(rand()).c_str());
      retval->i_list["il" + i].push_back(rand());
      retval->f_list["fl" + i].push_back(rand() / 12.0);
    }
  }

  return retval;
}

// No error checking!!!
extern void GetStringAttr(Context* ctx, const char* name, const char** var) {
  *var = ctx->s[name].c_str();
}

extern void GetIntAttr(Context* ctx, const char* name, int* var) {
  *var = ctx->i[name];
}

extern void GetFloatAttr(Context* ctx, const char* name, float* var) {
  *var = ctx->f[name];
}

extern void GetStringListAttr(Context* ctx, const char* name, int* size, const char*** var) {
  *size = ctx->s_list.size();
  *var = ctx->s_list[name].data();
}

extern void GetIntListAttr(Context* ctx, const char* name, int* size, int** var) {
  *size = ctx->i_list.size();
  *var = ctx->i_list[name].data();
}

extern void GetFloatListAttr(Context* ctx, const char* name, int* size, float** var) {
  *size = ctx->f_list.size();
  *var = ctx->f_list[name].data();
}
