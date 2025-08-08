#include <iostream>
#include <cstdlib>

using namespace std;

#define N 1024

int main(int argc, char *argv[]){

  srand(42);

  double *a = new double[N*N];
  double *b = new double[N*N];
  double *c = new double[N*N];

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      a[i*N + j] = rand()%10 + 1;
      b[i*N + j] = rand()%10 + 1;
      // a[i * N + j] = i * N + j;
      //   b[i * N + j] = i * N + j + 1;
      c[i*N + j] = 0;
    }
  }

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < N; k++) {
        c[i * N + j] += a[i * N + k] * b[k * N + j];
      }
    }
  }

  for(int i = 0;i<2;i++) {
    for(int j = 0;j<2;j++) {
      cout<<c[i * N + j]<<" ";
    }
    cout<<endl;
  }

  delete[] a;
  delete[] b;
  delete[] c;

  return 0;
}