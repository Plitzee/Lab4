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

// Standard Insertion Sort
template <typename T>
void insertionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Binary Search to find the insertion position
template <typename T>
int binarySearch(const vector<T>& arr, int start, int end, const T& key) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) start = mid + 1;
        else end = mid - 1;
    }
    return start; // Return the position where key should be inserted
}

// Insertion Sort using Binary Search
template <typename T>
void binaryInsertionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int pos = binarySearch(arr, 0, i - 1, key);

        
        for (int j = i - 1; j >= pos; --j) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = key;
    }
}

// Helper function to measure execution time
template <typename Func, typename T>
double measureTime(Func func, vector<T> arr) {
    auto start = chrono::high_resolution_clock::now();
    func(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    vector<int> sizes = {100, 1000, 10000}; // Array sizes for testing
    for (int size : sizes) {
        auto originalList = generateRandomList(size);

        // Measure time for standard Insertion Sort
        auto standardInsertionSortList = originalList;
        double standardTime = measureTime(insertionSort<int>, standardInsertionSortList);
        cout << "Standard Insertion Sort (size " << size << ") took " << standardTime << " seconds for the process."<<endl;

        // Measure time for Binary Insertion Sort
        auto binaryInsertionSortList = originalList;
        double binaryTime = measureTime(binaryInsertionSort<int>, binaryInsertionSortList);
        cout << "Binary Insertion Sort (size " << size << ") took " << binaryTime << " seconds for the process."<<endl;

        cout << "----------------------------------------" << endl;
    }

    return 0;
}
