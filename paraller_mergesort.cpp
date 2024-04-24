#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void merge(vector<int>& arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1), right(n2);
    
    for (int i = 0; i < n1; i++) {
        left[i] = arr[low + i];
    }
    
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void parallelMergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }
        merge(arr, low, mid, high);
    }
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> arrCopy = arr; // Copy for parallel sort

    double start_time, end_time;

    // Measure Sequential Time
    start_time = omp_get_wtime(); 
    mergeSort(arr, 0, n - 1);
    end_time = omp_get_wtime(); 
    cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds\n";
    cout << "Sorted array (Sequential): ";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    // Measure Parallel time
    start_time = omp_get_wtime(); 
    parallelMergeSort(arrCopy, 0, n - 1);
    end_time = omp_get_wtime(); 
    cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds\n";
    cout << "Sorted array (Parallel): ";
    for (int num : arrCopy) cout << num << " ";
    cout << "\n";

    return 0;
}
