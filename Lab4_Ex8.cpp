#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

// Function to generate a list of random integers
vector<int> generateRandomList(int size, int min = 1, int max = 1000) {
    vector<int> list(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    for (int& num : list) {
        num = dist(gen);
    }
    return list;
}

// Insertion Sort for small subarrays
template <typename T>
void insertionSort(vector<T>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Partition function for Quick Sort
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Standard Quick Sort
template <typename T>
void quickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Hybrid Sort: Uses Quick Sort for large datasets and Insertion Sort for small subarrays
template <typename T>
void hybridSort(vector<T>& arr, int low, int high, int threshold = 10) {
    if (high - low + 1 <= threshold) {
        // Use Insertion Sort for small subarrays
        insertionSort(arr, low, high);
    } else {
        // Use Quick Sort for large subarrays
        int pi = partition(arr, low, high);
        hybridSort(arr, low, pi - 1, threshold);
        hybridSort(arr, pi + 1, high, threshold);
    }
}

// Helper function to measure execution time
template <typename Func, typename T>
double measureTime(Func func, vector<T>& arr) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    vector<int> sizes = {100, 1000, 10000};  // Array sizes for testing
    for (int size : sizes) {
        auto originalList = generateRandomList(size);

        // Measure time for standard Quick Sort
        auto quickSortList = originalList;
        double quickSortTime = measureTime(quickSort<int>, quickSortList);
        cout << "Standard Quick Sort (size " << size << ") took " << quickSortTime << " seconds for the process." <<endl;

        // Measure time for Hybrid Sort
        auto hybridSortList = originalList;
        double hybridSortTime = measureTime([&](vector<int>& arr, int low, int high) {
            hybridSort(arr, low, high, 10);  // Threshold of 10 for Insertion Sort
        }, hybridSortList);
        cout << "Hybrid Sort (size " << size << ") took " << hybridSortTime << " seconds for the process." <<endl;

        cout << "----------------------------------------" << endl;
    }

    return 0;
}

