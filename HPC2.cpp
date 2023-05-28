#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;
void parallel_bubble_sort(vector<int>& arr) {
    bool swapped = true;
    int n = arr.size();
    #pragma omp parallel shared(arr, n, swapped)
    {
        while (swapped) {
            swapped = false;
            #pragma omp for nowait
            for (int i = 1; i < n; i++) {
                if (arr[i - 1] > arr[i]) {
                    swap(arr[i - 1], arr[i]);
                    swapped = true;
                }
            }
        }
    }
}
void parallel_merge_sort(vector<int>& arr) {
    if (arr.size() > 1) {
        int mid = arr.size() / 2;
        vector<int> left(arr.begin(), arr.begin() + mid);
        vector<int> right(arr.begin() + mid, arr.end());
        #pragma omp parallel sections
    {
        #pragma omp section
        parallel_merge_sort(left);
        #pragma omp section
        parallel_merge_sort(right);
    }
    merge(left.begin(), left.end(),
    right.begin(), right.end(), arr.begin());
    }
}
int main() {
    vector<int> arr = {5, 2, 9, 1, 7, 6, 8, 3, 4};
    cout << "Original array: ";
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;
    // Parallel bubble sort
    parallel_bubble_sort(arr);
    cout << "After parallel bubble sort: ";
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;
    // Parallel merge sort
    parallel_merge_sort(arr);
    cout << "After parallel merge sort: ";
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}