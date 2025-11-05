#include "sort.h"
#include <algorithm>
#include <optional>

static double key_of(const DataRecord& r, SortField f) {
    switch (f) {
    case SortField::Age:
        return static_cast<double>(r.age);

    case SortField::Glucose:
        // r.glucose is std::optional<double>
        return r.glucose.has_value() ? *r.glucose : -1.0;

    case SortField::HbA1c:
        // r.hba1c is std::optional<double>
        return r.hba1c.has_value() ? *r.hba1c : -1.0;

    case SortField::BMI:
        // r.bmi is std::optional<double>
        return r.bmi.has_value() ? *r.bmi : -1.0;
    }
    return -1.0; // fallback
}

// Put "missing" (-1) at end for Asc, at start for Desc.
static bool before(const DataRecord& a, const DataRecord& b, SortField f, SortOrder o){
    double ka = key_of(a, f), kb = key_of(b, f);
    if (ka < 0 && kb >= 0) return (o == SortOrder::Desc);
    if (kb < 0 && ka >= 0) return (o == SortOrder::Asc);
    return (o == SortOrder::Asc) ? (ka < kb) : (ka > kb);
}

// --- 1. MERGE SORT (Unchanged) ---
// This is the Merge Sort implementation.
static void merge(std::vector<DataRecord>& a, int left, int mid, int right, SortField f, SortOrder o) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<DataRecord> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (before(L[i], R[j], f, o)) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}
static void merge_sort_recursive(std::vector<DataRecord>& a, int left, int right, SortField f, SortOrder o) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(a, left, mid, f, o);
        merge_sort_recursive(a, mid + 1, right, f, o);
        merge(a, left, mid, right, f, o);
    }
}
static void merge_sort(std::vector<DataRecord>& a, SortField f, SortOrder o) {
    if (a.empty()) return;
    merge_sort_recursive(a, 0, a.size() - 1, f, o);
}


// --- 2. QUICK SORT (New) ---
// This is the Quick Sort implementation, replacing Shell Sort.

// Partition helper for Quick Sort (Lomuto partition scheme)
static int partition(std::vector<DataRecord>& a, int low, int high, SortField f, SortOrder o) {
    DataRecord pivot = a[high]; // Pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot (using 'before' comparator)
        if (before(a[j], pivot, f, o)) {
            i++; // increment index of smaller element
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i + 1], a[high]);
    return (i + 1);
}

// Recursive helper for Quick Sort
static void quick_sort_recursive(std::vector<DataRecord>& a, int low, int high, SortField f, SortOrder o) {
    if (low < high) {
        // pi is partitioning index, a[pi] is now at right place
        int pi = partition(a, low, high, f, o);

        // Separately sort elements before and after partition
        quick_sort_recursive(a, low, pi - 1, f, o);
        quick_sort_recursive(a, pi + 1, high, f, o);
    }
}

// Main Quick Sort function
static void quick_sort(std::vector<DataRecord>& a, SortField f, SortOrder o) {
    if (a.empty()) return;
    quick_sort_recursive(a, 0, a.size() - 1, f, o);
}
// --- END QUICK SORT ---


// --- UPDATED MAIN FUNCTION ---
void sort_records(std::vector<DataRecord>& data, Algorithm algo, SortField field, SortOrder order){
    if (data.size() < 2) return;

    // This now calls your new Quick and Merge sort functions
    if (algo == Algorithm::Quick) {
        quick_sort(data, field, order);
    } else if (algo == Algorithm::Merge) {
        merge_sort(data, field, order);
    }
}
