#include <iostream>
#include <cstdlib>
#include <mpi.h>

using namespace std;

#define N 1000000000

int main(int argc, char *argv[]) {

  
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);


  srand(42);

  int *sendcounts = new int[size];
  int *disp = new int[size];

  double *array = nullptr;
  double sum = 0;

  int base = N/size;
  int rem = N%size;

  for(int i = 0;i<size;i++) {
    sendcounts[i] = base + (i<rem?1:0);
  }
  
  disp[0] = 0;

  for(int i = 1;i<size;i++) {
    disp[i] = disp[i-1] + sendcounts[i-1];
  }

  double *local_array = new double[sendcounts[rank]];

  if(rank == 0) {
    array = new double[N];
    for(int i = 0;i<N;i++) {
      // array[i] = rand()%100 + 1;
      array[i] = i/1000;
    }
  }

  double start = MPI_Wtime();

  MPI_Scatterv(array, sendcounts, disp, MPI_DOUBLE, local_array, sendcounts[rank],MPI_DOUBLE, 0, MPI_COMM_WORLD);
  
  double partial_sum = 0;
  for(int i = 0;i<sendcounts[rank];i++) {
    partial_sum += local_array[i];
  }

  double total_sum = 0;
  
/*
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
               MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
*/
  MPI_Reduce(&partial_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  double end = MPI_Wtime();

  if(rank == 0) {

    cout<<"The total sum  = "<<total_sum<<endl;
    cout<<"Total time taken = "<<end-start<<endl; 
    delete[] array;
  }

  MPI_Finalize();

  
  delete[] sendcounts;
  delete[] disp;
  delete[] local_array;
}