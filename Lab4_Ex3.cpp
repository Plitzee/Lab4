#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <algorithm>
#include <type_traits>

using namespace std;

// Function to generate a list of random integers, floating-point numbers, or strings
template <typename T>
vector<T> generateRandomList(int size, T min, T max) {
    vector<T> list(size);
    random_device rd;
    mt19937 gen(rd());

    if constexpr (is_integral<T>::value) { // Integer generation
        uniform_int_distribution<> dist(min, max);
        for (auto& num : list) {
            num = dist(gen);
        }
    } else if constexpr (is_floating_point<T>::value) { // Floating-point generation
        uniform_real_distribution<> dist(min, max);
        for (auto& num : list) {
            num = dist(gen);
        }
    } else if constexpr (is_same<T, string>::value) { // String generation
        uniform_int_distribution<> char_dist(97, 122); // lowercase letters a-z
        for (auto& str : list) {
            str = "";
            for (int i = 0; i < 5; ++i) { // Random 5-letter strings
                str += static_cast<char>(char_dist(gen));
            }
        }
    }
    return list;
}

// Selection Sort
template <typename T>
void selectionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Bubble Sort
template <typename T>
void bubbleSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
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

// Quick Sort
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

template <typename T>
void quickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
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

template <typename T>
void mergeSort(vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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
    vector<int> sizes = {100, 1000, 10000}; // Array sizes to test
    
    for (int size : sizes) {
        cout << "\nArray size: " << size << endl;

        // Test with integers
        cout << "\nTesting with integers:" << endl;
        auto intList = generateRandomList<int>(size, 1, 1000);
        cout << "Selection Sort took " << measureTime(selectionSort<int>, intList) << " seconds."<<endl;
        cout << "Bubble Sort took " << measureTime(bubbleSort<int>, intList) << " seconds."<<endl;
        cout << "Insertion Sort took " << measureTime(insertionSort<int>, intList) << " seconds."<<endl;
        cout << "Quick Sort took " << measureTime([&](vector<int> arr) { quickSort(arr, 0, arr.size() - 1); }, intList) << " seconds."<<endl;
        cout << "Merge Sort took " << measureTime([&](vector<int> arr) { mergeSort(arr, 0, arr.size() - 1); }, intList) << " seconds."<<endl;
        
        // Test with floating-point numbers
        cout << "\nTesting with floating-point numbers:" << endl;
        auto floatList = generateRandomList<double>(size, 1.0, 1000.0);
        cout << "Selection Sort took " << measureTime(selectionSort<double>, floatList) << " seconds."<<endl;
        cout << "Bubble Sort took " << measureTime(bubbleSort<double>, floatList) << " seconds."<<endl;
        cout << "Insertion Sort took " << measureTime(insertionSort<double>, floatList) << " seconds."<<endl;
        cout << "Quick Sort took " << measureTime([&](vector<double> arr) { quickSort(arr, 0, arr.size() - 1); }, floatList) << " seconds."<<endl;
        cout << "Merge Sort took " << measureTime([&](vector<double> arr) { mergeSort(arr, 0, arr.size() - 1); }, floatList) << " seconds."<<endl;

        // Test with strings
        cout << "\nTesting with strings:" << endl;
        auto strList = generateRandomList<string>(size, "", "");
        cout << "Selection Sort took " << measureTime(selectionSort<string>, strList) << " seconds."<<endl;
        cout << "Bubble Sort took " << measureTime(bubbleSort<string>, strList) << " seconds."<<endl;
        cout << "Insertion Sort took " << measureTime(insertionSort<string>, strList) << " seconds."<<endl;
        cout << "Quick Sort took " << measureTime([&](vector<string> arr) { quickSort(arr, 0, arr.size() - 1); }, strList) << " seconds."<<endl;
        cout << "Merge Sort took " << measureTime([&](vector<string> arr) { mergeSort(arr, 0, arr.size() - 1); }, strList) << " seconds."<<endl;
    }

    return 0;
}
