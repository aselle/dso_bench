
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
  map<string, vector<string> > s_list;
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
      retval->s_list["sl" + i].push_back(to_string(rand()));
      retval->i_list["il" + i].push_back(rand());
      retval->f_list["fl" + i].push_back(rand() / 12.0);
    }
  }
}

// API.
extern void GetStringAttr(Context*, const char*, char**);
extern void GetIntAttr(Context*, const char*, int*);
extern void GetFloatAttr(Context*, const char*, float*);

extern void GetStringListAttr(Context*, const char*, int*, char***);
extern void GetIntListAttr(Context*, const char*, int*, int**);
extern void GetFloatListAttr(Context*, const char*, int*, float**);
