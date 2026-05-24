#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

void selectionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

void insertionSort(vector<int> arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin()+l, arr.begin()+m+1);
    vector<int> right(arr.begin()+m+1, arr.begin()+r+1);
    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r-l)/2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1, r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int> arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    cout << "\n===== SORTING ALGORITHM ANALYSER =====\n\n";

    cout << "Time & Space Complexity:\n";
    cout << "-----------------------------------------------------------------\n";
    cout << left << setw(18) << "Algorithm" << setw(14) << "Best"
         << setw(14) << "Average" << setw(14) << "Worst" << "Space\n";
    cout << "-----------------------------------------------------------------\n";
    cout << setw(18) << "Bubble Sort"    << setw(14) << "O(n)"     << setw(14) << "O(n^2)"   << setw(14) << "O(n^2)"   << "O(1)\n";
    cout << setw(18) << "Selection Sort" << setw(14) << "O(n^2)"   << setw(14) << "O(n^2)"   << setw(14) << "O(n^2)"   << "O(1)\n";
    cout << setw(18) << "Insertion Sort" << setw(14) << "O(n)"     << setw(14) << "O(n^2)"   << setw(14) << "O(n^2)"   << "O(1)\n";
    cout << setw(18) << "Merge Sort"     << setw(14) << "O(nlogn)" << setw(14) << "O(nlogn)" << setw(14) << "O(nlogn)" << "O(n)\n";
    cout << setw(18) << "Quick Sort"     << setw(14) << "O(nlogn)" << setw(14) << "O(nlogn)" << setw(14) << "O(n^2)"   << "O(logn)\n";
    cout << setw(18) << "Heap Sort"      << setw(14) << "O(nlogn)" << setw(14) << "O(nlogn)" << setw(14) << "O(nlogn)" << "O(1)\n";
    cout << "-----------------------------------------------------------------\n\n";

    cout << "Step-by-step trace (Bubble Sort) on: [64, 34, 25, 12, 22, 11, 90]\n";
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    int n = arr.size(), step = 1;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                cout << "step " << step++ << ": [";
                for (int k = 0; k < n; k++)
                    cout << arr[k] << (k < n-1 ? ", " : "]\n");
            }
        }
    }
    cout << "\nsorted: [";
    for (int i = 0; i < n; i++) cout << arr[i] << (i < n-1 ? ", " : "]\n\n");

    return 0;
}
