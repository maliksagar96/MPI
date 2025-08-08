#include <iostream>
#include <cstdlib>

using namespace std;

#define N 10

int main(int argc, char *argv[]){

  srand(42);

  double **a = new double*[N];
  double **b = new double*[N];
  double **c = new double*[N];

  for(int i = 0; i < N; i++) {
    a[i] = new double[N];
    b[i] = new double[N];
    c[i] = new double[N];
  }

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      a[i][j] = rand()%10 + 1;
      b[i][j] = rand()%10 + 1;
      c[i][j] = 0;
    }
  }

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < N; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  for(int i = 0;i<2;i++) {
    for(int j = 0;j<2;j++) {
      cout<<c[i][j]<<" ";
    }
    cout<<endl;
  }

  delete[] a;
  delete[] b;
  delete[] c;

  return 0;
}