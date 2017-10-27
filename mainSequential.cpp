#include "mpi.h"
#include <random>

using std::cout;
using std::endl;
using std::stoi;
using std::stod;

int main(int argc, char* argv[]) {
    int size, rank, elemDist;
    double result = 0.0, t1, t2;
    long double elem = 0.0, sum = 0.0;

    int arraySize = stoi(argv[1]);
    double initialValue = stod(argv[2]);
    double finalValue = stod(argv[3]);
    double* arr = new double[arraySize];

    std::random_device r;
    std::default_random_engine gen(0);
    std::uniform_real_distribution<double> dist(initialValue, finalValue);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    if (rank == 0) {
        for (int i = 0; i < arraySize; ++i) {
            arr[i] = dist(gen);            
        }

        t1 = MPI_Wtime();
        for (int i = 0; i < arraySize; ++i) {
            sum += arr[i];
        }

        result = sum / arraySize;
        cout << "Sequential algorithm result = " << result << endl;
        t2 = MPI_Wtime();
        cout << "Sequential algorithm time(in seconds) = " << t2-t1 << endl;
       
    }    
   
    MPI_Finalize();

    delete[] arr;

    return 0;
}