#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    // Input data from the user
    cout << "Enter the number of elements: ";
    int num_elements;
    cin >> num_elements;

    cout << "Enter the elements: ";
    vector<int> data(num_elements);
    for (int i = 0; i < num_elements; ++i) {
        cin >> data[i];
    }

    // Number of elements
    int n = data.size();

    // Variables to store results
    int min_val = data[0], max_val = data[0], sum_val = 0;
    double avg_val;

    // Parallel reduction for minimum
#pragma omp parallel for reduction(min:min_val)
    for (int i = 0; i < n; ++i) {
        if (data[i] < min_val)
            min_val = data[i];
    }

    // Parallel reduction for maximum
#pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < n; ++i) {
        if (data[i] > max_val)
            max_val = data[i];
    }

    // Parallel reduction for sum
#pragma omp parallel for reduction(+:sum_val)
    for (int i = 0; i < n; ++i) {
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
