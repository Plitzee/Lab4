#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
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

// Selection Sort for list
template <typename T>
void selectionSortList(list<T>& lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        auto minIt = it;
        for (auto jt = next(it); jt != lst.end(); ++jt) {
            if (*jt < *minIt) {
                minIt = jt;
            }
        }
        iter_swap(it, minIt);
    }
}

// Helper function to convert queue to vector for sorting
template <typename T>
vector<T> queueToVector(queue<T> q) {
    vector<T> vec;
    while (!q.empty()) {
        vec.push_back(q.front());
        q.pop();
    }
    return vec;
}

// Helper function to convert stack to vector for sorting
template <typename T>
vector<T> stackToVector(stack<T> s) {
    vector<T> vec;
    while (!s.empty()) {
        vec.push_back(s.top());
        s.pop();
    }
    return vec;
}

// Function to sort and measure time for Linked List
template <typename T>
double measureLinkedListSort(list<T>& lst) {
    auto start = chrono::high_resolution_clock::now();
    lst.sort(); // using the built-in sort function for linked list
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

// Function to sort and measure time for Queue
template <typename T>
double measureQueueSort(queue<T> q) {
    auto vec = queueToVector(q);
    auto start = chrono::high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

// Function to sort and measure time for Stack
template <typename T>
double measureStackSort(stack<T> s) {
    auto vec = stackToVector(s);
    auto start = chrono::high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    vector<int> sizes = { 100, 1000, 10000 }; // Different sizes for testing
    for (int size : sizes) {
        auto originalList = generateRandomList(size);
        
        // Test with Linked List
        list<int> linkedList(originalList.begin(), originalList.end());
        double linkedListTime = measureLinkedListSort(linkedList);
        cout << "Linked List Sort (size " << size << ") took " << linkedListTime << " seconds."<<endl;

        // Test with Queue
        queue<int> q;
        for (int num : originalList) {
            q.push(num);
        }
        double queueTime = measureQueueSort(q);
        cout << "Queue Sort (size " << size << ") took " << queueTime << " seconds."<<endl;

        // Test with Stack
        stack<int> s;
        for (int num : originalList) {
            s.push(num);
        }
        double stackTime = measureStackSort(s);
        cout << "Stack Sort (size " << size << ") took " << stackTime << " seconds."<<endl;

        cout << "----------------------------------------" << endl;
    }
    return 0;
}
