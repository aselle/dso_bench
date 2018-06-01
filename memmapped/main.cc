#include "memmapped/api.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

#define BENCHMARK_SIZE 10

int main() {
  Context* ctx = InitializeContext(BENCHMARK_SIZE);
  vector<const char*> string_storage(BENCHMARK_SIZE, "");

  cout << "Start benchmarking" <<  endl;
  auto start = chrono::high_resolution_clock::now();


  Attr* attr;
  int attr_size;
  GetStringAttrs(ctx, &attr_size, &attr);

  for (int i=0 ; i<BENCHMARK_SIZE; i++) {
    string_storage[i] = GetStringAttr(attr + i);
  }

  auto end = chrono::high_resolution_clock::now();

  cout << "Timing complete!" << endl;
  cout << " \t Number of data: " << BENCHMARK_SIZE << endl;
  cout << " \t Timing  : "
       << chrono::duration <double, nano> (end-start).count() << " ns" << endl;

  return 0;
}
