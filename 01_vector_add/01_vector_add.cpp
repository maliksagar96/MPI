#include <iostream>
#include <vector>
#include <mpi.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 1000000000

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *count = new int[size];
    int *disp = new int[size];

    int base = N / size;
    int rem = N % size;

    // Compute counts and displacements
    for (int i = 0; i < size; ++i)
        count[i] = base + (i < rem ? 1 : 0);

    disp[0] = 0;
    for (int i = 1; i < size; ++i)
        disp[i] = disp[i - 1] + count[i - 1];

    // Allocate local buffers
    double* a_local = new double[count[rank]];
    double* b_local = new double[count[rank]];
    double* c_local = new double[count[rank]];

    // Root allocates and initializes full arrays
    double* a = nullptr;
    double* b = nullptr;
    double* c = nullptr;

    if (rank == 0) {
        a = new double[N];
        b = new double[N];
        c = new double[N];

        srand(42);
        for (int i = 0; i < N; ++i) {
            a[i] = rand() % 100 + 1;
            b[i] = rand() % 100 + 1;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    // Scatter a and b
    MPI_Scatterv(a, count, disp, MPI_DOUBLE,
                 a_local, count[rank], MPI_DOUBLE,
                 0, MPI_COMM_WORLD);

    MPI_Scatterv(b, count, disp, MPI_DOUBLE,
                 b_local, count[rank], MPI_DOUBLE,
                 0, MPI_COMM_WORLD);

    // Add a_local and b_local
    for (int i = 0; i < count[rank]; ++i)
        c_local[i] = a_local[i] + b_local[i];

    // Gather results to c
    MPI_Gatherv(c_local, count[rank], MPI_DOUBLE,
                c, count, disp, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double end = MPI_Wtime();

    // Root can now use c
    if (rank == 0) {
         cout << "Total time: " << end - start << " s\n";

        cout << "First 10 results from vector addition:\n";
        for (int i = N-10; i < N; ++i)
            cout << c[i] << " ";
        cout << endl;

        delete[] a;
        delete[] b;
        delete[] c;
    }

    delete[] a_local;
    delete[] b_local;
    delete[] c_local;

    MPI_Finalize();
    return 0;
}
