#include <iostream>
#include <vector>
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

// Function to heapify a subtree with the root at index `i`
// `n` is the size of the heap
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root, swap and heapify the affected subtree
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest); // Recursively heapify the affected subtree
    }
}

// Function to build a Max-Heap from the array
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
}

// Function to find the maximum value using Max-Heap
int findMaxWithHeapSort(vector<int>& arr) {
    // Build a Max-Heap
    buildMaxHeap(arr);
    // The maximum value will be at the root of the heap
    return arr[0];
}

int main() {
    int size = 10;  // Bạn có thể thay đổi kích thước của mảng ở đây
    auto arr = generateRandomList(size);

    // Find maximum using Heap Sort (Max-Heap)
    int maxVal = findMaxWithHeapSort(arr);
    cout << "The maximum value is: " << maxVal << endl;

    return 0;
}
