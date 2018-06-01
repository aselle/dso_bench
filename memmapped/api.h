

typedef struct Context;
extern Context* InitializeContext(int size);

typedef struct Attr {
  int type;
  char data_[];
} Attr;

extern void GetStringAttrs(Context*, int*, Attr**);

#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))

DLL_LOCAL const char* GetStringAttr(Attr* a) {
  return reinterpret_cast<const char*>(a->data_);
}

DLL_LOCAL int* GetIntAttr(Attr* a) {
  return reinterpret_cast<int*>(a->data_);
}

DLL_LOCAL float* GetFloatAttr(Attr* a) {
  return reinterpret_cast<float*>(a->data_);
}
