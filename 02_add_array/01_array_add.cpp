#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define N 1000000000

int main() {

  srand(42);

  double *array = new double[N];
  double sum = 0;

  for(int i = 0;i<N;i++) {
    // array[i] = rand()%100 + 1;
    array[i] = i/1000;
  }

  auto start = high_resolution_clock::now();
  for(int i = 0;i<N;i++) {
    sum += array[i];
  }

  auto end = high_resolution_clock::now();

  duration<double> diff = end - start;

  cout<<"Total time taken = "<<diff.count()<<endl;
  cout<<"Sum = "<<sum<<endl;

  return 0;
}