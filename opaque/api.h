typedef struct Context;

// Initialize, not part of the benchmark.
extern Context* InitializeContext(int size);

// API.
extern void GetStringAttr(Context*, const char*, char**);
extern void GetIntAttr(Context*, const char*, int*);
extern void GetFloatAttr(Context*, const char*, float*);

extern void GetStringListAttr(Context*, const char*, int*, char***);
extern void GetIntListAttr(Context*, const char*, int*, int**);
extern void GetFloatListAttr(Context*, const char*, int*, float**);
