#include "api.h"
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <iostream>

constexpr int NUM_CONTEXTS=100; // e.g. 100 ops


class
Context {
public:
  Context() {
    add_attr("strides");
    add_attr("activation");
  }

  void add_attr(const char* name) {
    name_to_attr[name] = table.size();
    table.push_back({});
    AttrTable& attr = table.back();
    attr.is_list=0;
    attr.f=new float[1];
    attr.f[0] = 0.f;
    names.push_back(strdup(name));
    attr.type = Float;
    attr.name_s = names.back();
    attr.name_e = names.back() + strlen(name) + 1;
  }

  std::vector<AttrTable> table;
  std::vector<char*> names;
  std::map<std::string, int> name_to_attr;

};

namespace {
std::vector<Context> contexts;
}

void InitTestData() {
  contexts.resize(NUM_CONTEXTS);
}


// Interface Opaque
bool GetF(Context* context, const char* name, const float** f) {
#if 1
  // Map lookup O(lg n)
  auto it = context->name_to_attr.find(name);
  if (it == context->name_to_attr.end()) return false;
  int index = it->second;
  AttrTable* attr = &context->table[index];

#else
  // List lookup O(n)
  const AttrTable* attr = nullptr;
  for(const auto& it: context->table) {
    if(!strcmp(it.name_s, name)) {
      attr = &it;
    }
  }
#endif
  if(!attr || attr->type != Float || attr->is_list) {
    std::cerr<<"Failed to find right type for "<<name<<std::endl;
    exit(1);
    return false;
  }
  *f = attr->f;
  return true;
}
// bList(Context*, const char* name, float** f);

// Interface transparent
bool Get(Context* context, AttrTable** table, int* size) {
  *size = context->table.size();
  *table = context->table.data();
  return true;
}

void Test(float(*f)(Context*)) {
  for(auto& context: contexts) {
    f(&context);
  }
}
