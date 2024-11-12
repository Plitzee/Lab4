#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

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

// Insertion Sort for small arrays
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

// Merge function to merge two halves of the array
template <typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Standard Merge Sort
template <typename T>
void mergeSort(vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Hybrid Sort: Uses Merge Sort for large arrays and Insertion Sort for small subarrays
template <typename T>
void hybridSort(vector<T>& arr, int left, int right, int threshold = 10) {
    if (right - left + 1 <= threshold) {
        // Use Insertion Sort for small arrays
        insertionSort(arr, left, right);
    } else {
        // Use Merge Sort for large arrays
        int mid = left + (right - left) / 2;
        hybridSort(arr, left, mid, threshold);
        hybridSort(arr, mid + 1, right, threshold);
        merge(arr, left, mid, right);
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

        // Measure time for standard Merge Sort
        auto mergeSortList = originalList;
        double mergeSortTime = measureTime(mergeSort<int>, mergeSortList);
        cout << "Standard Merge Sort (size " << size << ") took " << mergeSortTime << " seconds for the process." <<endl;

        // Measure time for Hybrid Sort
        auto hybridSortList = originalList;
        double hybridSortTime = measureTime([&](vector<int>& arr, int left, int right) {
            hybridSort(arr, left, right, 10);  // Threshold of 10 for Insertion Sort
        }, hybridSortList);
        cout << "Hybrid Sort (size " << size << ") took " << hybridSortTime << " seconds for the process." <<endl;

        cout << "----------------------------------------" << endl;
    }

    return 0;
}
