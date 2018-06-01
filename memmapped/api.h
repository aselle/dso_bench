

typedef struct Context;
extern Context* InitializeContext(int size);

typedef struct Attr {
  int type;
  char data_[];
} Attr;

extern void GetStringAttrs(Context*, int*, Attr**);

extern const char* GetStringAttr(Attr* a);
extern int* GetIntAttr(Attr* a);
extern float* GetFloatAttr(Attr* a);
