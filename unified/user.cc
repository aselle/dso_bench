
#include "api.h"
#include <cstring>
#include <cstdio>
#include <chrono>
#include <iostream>

constexpr int RUNS = 100;

template<class T>
struct RangeWrapper {
  const T *b;
  const T *e;
  RangeWrapper(const T* b, const T* e) : b(b), e(e) {}
  const T* begin() const {return b;}
  const T* end() const {return e;}
};


inline bool InlinedLookup(const AttrTable* table, int size, const char* name, const float** out) {
   for (const AttrTable* attr = table, *attr_end = table + size; attr < attr_end; attr++) {
     if(!strcmp(attr->name_s, name)) {
       if(attr->type == Float && attr->is_list == 0) {
         *out = attr->f;
         return true;
       }
     }
   }
   return false;
}

int main(int argc, char *argv[]) {
  InitTestData();
  auto start = std::chrono::high_resolution_clock::now();

  static bool do_sum = !strcmp(argv[2], "1");

  if(!strcmp(argv[1], "empty")) {
    for(int i = 0; i < RUNS; i++) {
      Test([](Context* context) {
        float sum =0.f;
        if(do_sum) {
          for(int k=0; k <1024;k ++)
            sum += .1f;
        }else return sum;
        return sum;
      });
    }
  }
  else if(!strcmp(argv[1], "opaque")) {
    for(int i = 0; i < RUNS; i++) {
      Test([](Context* context) {
        const float* strides;
        const float* activation;
        GetF(context, "strides", &strides);
        GetF(context, "activation", &activation);
        float sum =0.f;
        if(do_sum) {
          for(int k=0; k <1024;k ++)
            sum += .1f;
        }
        return *strides + *activation + sum;
      });
    }
  }
  else if(!strcmp(argv[1], "transparent")) {
    for(int i = 0; i < RUNS; i++) {
      Test([](Context* context) {
        AttrTable* table;
        int size;
        Get(context, &table, &size);
        float dummy_stride=0.f, dummy_act=0.f;
        const float* strides = &dummy_stride, *activation = &dummy_act;
        #if 0
        // One way
        for (AttrTable* attr = table, *attr_end = table + size; attr < attr_end; attr++) {
          // auto attr: RangeWrapper<AttrTable>(table, table + size)) {
          if(!strcmp(attr->name_s, "strides")) {
            if(attr->type == Float && attr->is_list == 0)
              strides = attr->f;
          }
          else if(!strcmp(attr->name_s, "activation")) {
            if(attr->type == Float && attr->is_list == 0)
              activation = attr->f;
          } else {
            std::cerr<<"Couldn't find place for "<<attr->name_s<<std::endl;
            exit(1);
          }
        }
        #else
        // another way
        InlinedLookup(table, size, "strides", &strides);
        InlinedLookup(table, size, "activation", &activation);
        #endif
        float sum = 0.f;
        if(do_sum) {
          for(int k=0; k <1024;k ++)
            sum += .1f;
        }
        return *strides + *activation + sum;
      });
    }
  } else {
    fprintf(stderr,"Need to provide 'opaque' or 'transparent' as argument\n");
    return 1;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Timing complete!" << std::endl;
  std::cout << " \t Timing  : "
       << std::chrono::duration <double, std::nano> (end-start).count()
       << " ns" << std::endl;

  return 0;
}
