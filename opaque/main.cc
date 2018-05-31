#include "opaque/api.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

#define BENCHMARK_SIZE 10

int main() {

  Context* ctx = InitializeContext(BENCHMARK_SIZE);

  cout << "Start benchmarking" <<  endl;
  vector<const char*> string_storage(BENCHMARK_SIZE, "");
  auto start = chrono::high_resolution_clock::now();


  for (int i=0 ; i<BENCHMARK_SIZE; i++) {
    const char* tmp;
    GetStringAttr(ctx, "s" + i, &tmp);
    string_storage[i] = tmp;
  }

  auto end = chrono::high_resolution_clock::now();

  cout << "Timing complete!" << endl;
  cout << " \t Number of data: " << BENCHMARK_SIZE << endl;
  cout << " \t Timing  : "
       << chrono::duration <double, nano> (end-start).count() << " ns" << endl;

  return 1;
}
