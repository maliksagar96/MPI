/*
  int MPI_Scatterv(const void *sendbuf, const int *sendcounts, const int *displs,
                 MPI_Datatype sendtype, void *recvbuf, int recvcount,
                 MPI_Datatype recvtype,
                 int root, MPI_Comm comm)

  
  int MPI_Bcast( void *buffer, int count, MPI_Datatype datatype, int root, 
               MPI_Comm comm )

  int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
  void *recvbuf, const int *recvcounts, const int *displs,
  MPI_Datatype recvtype, int root, MPI_Comm comm)
               
*/

#include <iostream>
#include <cstdlib>
#include <mpi.h>

using namespace std;
#define N 1024

int main(int argc, char *argv[]) {

  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  srand(42);

  double *a = nullptr;
  double *b = new double[N * N];
  double *c = nullptr;

  int *sendcounts = new int[size];
  int *disp = new int[size];

  // compute sendcounts and displacements first
  int base = N / size;
  int rem = N % size;

  for (int i = 0; i < size; i++) {
    sendcounts[i] = N * (base + (i < rem ? 1 : 0));
  }

  disp[0] = 0;
  for (int i = 1; i < size; i++) {
    disp[i] = disp[i - 1] + sendcounts[i - 1];
  }

  // now it's safe to calculate local_rows
  int local_rows = sendcounts[rank] / N;
  double *local_a = new double[local_rows * N];
  double *local_c = new double[local_rows * N];

  if (rank == 0) {
    a = new double[N * N];
    c = new double[N * N];

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        a[i * N + j] = rand() % 10 + 1;
        b[i * N + j] = rand() % 10 + 1;
        // a[i * N + j] = i * N + j;
        // b[i * N + j] = i * N + j + 1;
        c[i * N + j] = 0;
      }
    }
  }

  MPI_Scatterv(a, sendcounts, disp, MPI_DOUBLE,
               local_a, sendcounts[rank], MPI_DOUBLE,
               0, MPI_COMM_WORLD);

  MPI_Bcast(b, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // matrix multiplication
  for (int i = 0; i < local_rows; i++) {
    for (int j = 0; j < N; j++) {
      local_c[i * N + j] = 0;
      for (int k = 0; k < N; k++) {
        local_c[i * N + j] += local_a[i * N + k] * b[k * N + j];
      }
    }
  }

  MPI_Gatherv(local_c, sendcounts[rank], MPI_DOUBLE,
              c, sendcounts, disp, MPI_DOUBLE,
              0, MPI_COMM_WORLD);

  if (rank == 0) {
    cout << "Sample C[0:2][0:2]:" << endl;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        cout << c[i * N + j] << " ";
      }
      cout << endl;
    }
    delete[] a;
    delete[] c;
  }

  delete[] b;
  delete[] local_a;
  delete[] local_c;
  delete[] sendcounts;
  delete[] disp;

  MPI_Finalize();
  return 0;
}
