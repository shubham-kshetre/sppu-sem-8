#include <iostream>
#include <cstdlib> // for rand()

__global__ void add(int* A, int* B, int* C, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < size) {
        C[tid] = A[tid] + B[tid];
    }
}

void print(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int N;
    std::cout << "Enter the size of the vectors: ";
    std::cin >> N;

    int* A, * B, * C;
    A = new int[N];
    B = new int[N];
    C = new int[N];

    std::cout << "Enter values for vector A:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::cout << "Enter values for vector B:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cin >> B[i];
    }

    int* X, * Y, * Z;
    cudaMalloc(&X, N * sizeof(int));
    cudaMalloc(&Y, N * sizeof(int));
    cudaMalloc(&Z, N * sizeof(int));

    cudaMemcpy(X, A, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B, N * sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    add<<<blocksPerGrid, threadsPerBlock>>>(X, Y, Z, N);

    cudaMemcpy(C, Z, N * sizeof(int), cudaMemcpyDeviceToHost);

    std::cout << "Addition: ";
    print(C, N);

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);

    return 0;
}

