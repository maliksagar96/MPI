#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 1e9

int main() {

  srand(42);
  vector<double> a(N,0);
  vector<double> b(N,0);
  vector<double> c(N,0);

  for(int i = 0;i<N;i++) {
    a[i] = rand()%100 + 1;
    b[i] = rand()%100 + 1;
  }

 clock_t start = clock();

for(int i = 0; i < N; i++) {
    c[i] = a[i] + b[i];
}

clock_t end = clock();
double elapsed = double(end - start) / CLOCKS_PER_SEC;

cout << "Time taken for vector addition: " << elapsed << " seconds" << endl;

  for(int i = N-10;i<N;i++) {
    cout<<"C[i] = "<<c[i]<<endl;
  }

  return 0;
}