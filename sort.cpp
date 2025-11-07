#include "sort.h"
#include <algorithm>
#include <optional>
using namespace std;

// This function is going to swap the items
static void mySwap(DataRecord &data_hold_a, DataRecord &data_hold_b) {
    // holding data for swap
    DataRecord hold = data_hold_a;
    // swaping items
    data_hold_a = data_hold_b;
    data_hold_b = hold;
}

//
static double key_of(const DataRecord& track_1, SortField f_track) {
    switch (f_track) {
    case SortField::Age:

        return static_cast<double>(track_1.age);

    case SortField::Glucose:
        // This line will update the curretn bool flag so it can be used
        return track_1.has_glucose == true ?
                   track_1.glucose : -1.0;

    case SortField::HbA1c:
        // This line will update the curretn bool flag so it can be used
        return track_1.has_hba1c == true ?
                   track_1.hba1c : -1.0;

    case SortField::BMI:
         // This line will update the curretn bool flag so it can be used
        return track_1.has_bmi == true ?
                   track_1.bmi : -1.0;
    }

    return -1.0;
}

// Function will have a the total order
static bool before(const DataRecord& a_data, const DataRecord& b_data, SortField  f, SortOrder o_data){

    double data_1 = key_of(a_data, f);

    double data5 = key_of(b_data, f);

    // the lines will handle the missing values

    if (data_1 < 0 && data5 >= 0) {

        return (o_data == SortOrder::Desc);
    }
    if (data5 < 0 && data_1 >= 0) {

        return (o_data == SortOrder ::Asc);

    }
    // This line will have both present and missing of the numerical number
    if (o_data == SortOrder::Asc) {

        return (data_1 < data5);

    }
    else {
        return (data_1 > data5);
    }
}

// This is the merge sort algroth we use
static void merge(vector<DataRecord>& num, int data_left, int data_mid, int data_right, SortField data_f, SortOrder data_o) {

    int n1 = data_mid - data_left + 1;
    int n2 = data_right - data_mid;

    vector<DataRecord> L(n1), R(n2);

    // iterating through the loop
    for (int z = 0; z < n1; z++)

        L[z] = num[data_left + z];
    // iterating through the loop data
    for (int j = 0; j < n2; j++)
        R[j] = num[data_mid + 1 + j];

    int z_1 = 0, j = 0, k = data_left;
    // checking id the left should come 1st
    while (z_1 < n1 && j < n2) {
        if (before(L[z_1], R[j], data_f, data_o)) {

            num[k] = L[z_1];

            z_1++;

        }
        else {
            num[k] = R[j];
            j++;
        }
        k++;
    }
    // This line will copy all leftovers
    while (z_1 < n1) {

        num[k] = L[z_1];

        z_1++;
        k++;
    }
    while (j < n2) {

        num[k] = R[j];

        j++;

        k++;
    }
}


// This void is a recursive merge sort

static void merge_sort_recursive(vector<DataRecord>& data_a, int data_left, int data_right, SortField data_f, SortOrder data_o)
{
    // checking if the the case is a one or zero
    if (data_left < data_right) {
        // Intalize the int variable for mid point to split
        int mid = data_left + (data_right - data_left) / 2;
        // the lines will be sorting the right , mid , left
        merge_sort_recursive(data_a, data_left, mid, data_f, data_o);
        merge_sort_recursive(data_a, mid + 1, data_right, data_f, data_o);
        merge(data_a, data_left, mid, data_right, data_f, data_o);

    }
}

// The void will be teh first point of the merge sort
static void merge_sort(vector<DataRecord>& a_data, SortField f_data, SortOrder o_data) {

    // checks if there is nothing to sort
    if (a_data.empty()) {

        return;
    }
    // calling the recursive function
    merge_sort_recursive(a_data, 0, (int)a_data.size() - 1, f_data, o_data);

}


//// This is the quick sort algroth we use
static int partition(vector<DataRecord>& data_a, int data_low, int data_high, SortField data_f, SortOrder data_o) {

    // This line of code will choose the last element
    DataRecord _1pivot = data_a[data_high];

    int i =(data_low - 1);
    // The loop iterates trough the low to high
    for (int j = data_low; j <= data_high - 1; j++) {

        // checks if the 1 st element should come beofre

    if (before(data_a[j], _1pivot, data_f, data_o)) {
                  i++;
            mySwap(data_a[i], data_a[j]);
        }
    }
    mySwap(data_a[i + 1],
        data_a[data_high]);

    return (i + 1);
}


static void quick_sort_recursive(vector<DataRecord>& data_a, int data_low, int data_high, SortField data_f, SortOrder data_o) {
    // checks if the algorith is in range
    if (data_low < data_high) {
        // The line below will get the pivot index
        int pi=  partition(data_a, data_low, data_high, data_f, data_o);

        // The recursive are called to sort
    quick_sort_recursive(data_a, data_low, pi - 1, data_f, data_o);
         quick_sort_recursive(data_a, pi + 1, data_high, data_f, data_o);
     }
}

static void quick_sort(vector<DataRecord>& data_a, SortField data_f, SortOrder data_o) {
    // cheks if the data is empty

    if (data_a.empty()) {
        // returns if data is empty
        return;

    }
    // Sort algorithm is called
    quick_sort_recursive(data_a, 0, (int)data_a.size() - 1, data_f, data_o);
}


// this function will allows us to choose the algorithm
void sort_records(vector<DataRecord>& data1_data, Algorithm data1_algo, SortField data1_field, SortOrder data1_order){

    // checks if the there is a 0 or 1 elements then no actions will happen
    if ( data1_data.size() == 0 ||  data1_data.size() == 1) {

            return;

        }

   //checks what was choosen
    if ( data1_algo == Algorithm::Quick) {

         quick_sort( data1_data,  data1_field,  data1_order);

            }//

    else if ( data1_algo == Algorithm::Merge) {

          merge_sort( data1_data,  data1_field,  data1_order);// recursive function is called
    }
}
