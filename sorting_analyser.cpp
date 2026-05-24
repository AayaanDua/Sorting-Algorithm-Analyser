#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
using namespace std;
using namespace chrono;

// ─── Sorting Algorithms ───────────────────────────────────────────────────────

void bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; j--; }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < (int)left.size() && j < (int)right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < (int)left.size()) arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

void mergeSortHelper(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortHelper(arr, l, m);
        mergeSortHelper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSort(vector<int> arr) { mergeSortHelper(arr, 0, arr.size() - 1); }

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int> arr) { quickSortHelper(arr, 0, arr.size() - 1); }

void heapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) { swap(arr[i], arr[largest]); heapify(arr, n, largest); }
}

void heapSort(vector<int> arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) { swap(arr[0], arr[i]); heapify(arr, i, 0); }
}

// ─── Benchmark Helper ─────────────────────────────────────────────────────────

double measureTime(void (*sortFn)(vector<int>), const vector<int>& data) {
    auto start = high_resolution_clock::now();
    sortFn(data);
    auto end = high_resolution_clock::now();
    return duration<double, micro>(end - start).count();
}

// ─── Display ─────────────────────────────────────────────────────────────────

void printComplexity() {
    cout << "\n";
    cout << left << setw(20) << "Algorithm"
         << setw(18) << "Best Case"
         << setw(18) << "Average Case"
         << setw(18) << "Worst Case"
         << setw(10) << "Space" << "\n";
    cout << string(84, '-') << "\n";

    vector<tuple<string,string,string,string,string>> rows = {
        {"Bubble Sort",    "O(n)",      "O(n^2)",    "O(n^2)",    "O(1)"},
        {"Insertion Sort", "O(n)",      "O(n^2)",    "O(n^2)",    "O(1)"},
        {"Selection Sort", "O(n^2)",   "O(n^2)",    "O(n^2)",    "O(1)"},
        {"Merge Sort",     "O(n logn)","O(n logn)", "O(n logn)", "O(n)"},
        {"Quick Sort",     "O(n logn)","O(n logn)", "O(n^2)",    "O(logn)"},
        {"Heap Sort",      "O(n logn)","O(n logn)", "O(n logn)", "O(1)"},
    };
    for (auto& [name, best, avg, worst, space] : rows)
        cout << left << setw(20) << name << setw(18) << best
             << setw(18) << avg << setw(18) << worst << setw(10) << space << "\n";
}

void runBenchmark(const vector<int>& sizes) {
    vector<pair<string, void(*)(vector<int>)>> algos = {
        {"Bubble Sort",    bubbleSort},
        {"Insertion Sort", insertionSort},
        {"Selection Sort", selectionSort},
        {"Merge Sort",     mergeSort},
        {"Quick Sort",     quickSort},
        {"Heap Sort",      heapSort},
    };

    cout << "\n=== Benchmark: Execution Time (microseconds) ===\n\n";
    cout << left << setw(20) << "Algorithm";
    for (int s : sizes) cout << setw(14) << ("n=" + to_string(s));
    cout << "\n" << string(20 + 14 * sizes.size(), '-') << "\n";

    for (auto& [name, fn] : algos) {
        cout << left << setw(20) << name;
        for (int n : sizes) {
            vector<int> data(n);
            for (int i = 0; i < n; i++) data[i] = rand() % 10000;
            cout << setw(14) << fixed << setprecision(1) << measureTime(fn, data);
        }
        cout << "\n";
    }
}

// ─── Main ────────────────────────────────────────────────────────────────────

int main() {
    cout << "╔══════════════════════════════════════════╗\n";
    cout << "║      SORTING ALGORITHM ANALYSER          ║\n";
    cout << "╚══════════════════════════════════════════╝\n";

    cout << "\n=== Time & Space Complexity ===";
    printComplexity();

    vector<int> sizes = {100, 500, 1000, 5000};
    runBenchmark(sizes);

    cout << "\n=== Step-by-Step Trace: Bubble Sort on [64, 34, 25, 12, 22, 11, 90] ===\n";
    vector<int> trace = {64, 34, 25, 12, 22, 11, 90};
    int n = trace.size();
    int step = 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (trace[j] > trace[j + 1]) {
                swap(trace[j], trace[j + 1]);
                cout << "Step " << step++ << ": swap positions " << j << " & " << j+1 << " -> [";
                for (int k = 0; k < n; k++) cout << trace[k] << (k < n-1 ? ", " : "");
                cout << "]\n";
            }
        }
    }
    cout << "\nFinal sorted: [";
    for (int i = 0; i < n; i++) cout << trace[i] << (i < n-1 ? ", " : "");
    cout << "]\n\n";

    return 0;
}
