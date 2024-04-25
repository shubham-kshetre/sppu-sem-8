#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    // Sample data
    vector<int> data = {3, 7, 1, 9, 4, 6, 8, 2, 5};

    // Number of elements
    int n = data.size();

    // Variables to store results
    int min_val, max_val, sum_val;
    double avg_val;

    // Parallel reduction for minimum
#pragma omp parallel for reduction(min:min_val)
    for (int i = 0; i < n; ++i) {
        // Each thread finds the local minimum within its assigned portion of the data
        // min_val is updated using the reduction operation to find the overall minimum
        if (i == 0 || data[i] < min_val)
            min_val = data[i];
    }

    // Parallel reduction for maximum
#pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < n; ++i) {
        // Each thread finds the local maximum within its assigned portion of the data
        // max_val is updated using the reduction operation to find the overall maximum
        if (i == 0 || data[i] > max_val)
            max_val = data[i];
    }

    // Parallel reduction for sum
#pragma omp parallel for reduction(+:sum_val)
    for (int i = 0; i < n; ++i) {
        // Each thread calculates the local sum within its assigned portion of the data
        // sum_val is updated using the reduction operation to find the overall sum
        sum_val += data[i];
    }

    // Compute average
    avg_val = static_cast<double>(sum_val) / n;

    // Output results
    cout << "Minimum: " << min_val << endl; // Output the minimum value
    cout << "Maximum: " << max_val << endl; // Output the maximum value
    cout << "Sum: " << sum_val << endl;     // Output the sum
    cout << "Average: " << avg_val << endl; // Output the average

    return 0;
}
// We define a vector data containing sample data.
//We determine the number of elements n in the data vector.
//We declare variables min_val, max_val, sum_val, and avg_val to store the results of minimum, maximum, sum, and average operations respectively.
//We use OpenMP's parallel for pragma to parallelize the loops for finding the minimum, maximum, and sum.
//For each operation (minimum, maximum, sum), we specify a reduction clause to perform the reduction operation (min, max, +) across all threads.
//Within each parallel loop, each thread performs its own local computation on its assigned portion of the data.
//The reduction operation updates the global result variable (min_val, max_val, sum_val) with the result from each thread.
//After parallel computation, we calculate the average by dividing the sum by the number of elements.
//Finally, we output the results including the minimum, maximum, sum, and average values.
