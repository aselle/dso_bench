
// TODO: make this C
class Context;

typedef enum {
  Int,
  Float
} Type;


typedef struct {
public:
  const char *name_s, *name_e; // essentially a string piece
  Type type;
  int is_list;
  union {
    float* f;
  };
} AttrTable;

// Interface Opaque
bool GetF(Context*, const char* name, const float** f);
// GetFList(Context*, const char* name, float** f);

// Interface transparent
bool Get(Context*, AttrTable**, int* size);


void InitTestData();
void Test(float(*f)(Context*));


