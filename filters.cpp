#include "filters.h"
#include <cctype>
#include <algorithm>

using namespace std;

// This line will create a loop for the lower end to collect the data
static string lower(string s){
    for (int j = 0; j < s.length(); j++) {

        s[j] = (char)std::tolower((unsigned char)s[j]);
    }
    return s;
}
// This line will create the data being folled on the vector, takes in the data  by value
vector<DataRecord> filterGen(vector<DataRecord> data, const string& first_gen){
    /// vectoe created
    vector<DataRecord> out;

    string car = lower(first_gen);

    // for loop takes i tyhe lower end of gender and input the data in the lower end
    for (int z = 0; z < data.size(); z++) {
        if (lower(data[z].gender) == car) {

            out.push_back(data[z]);
        }
    }
    return out;
}

 // This value will filter the value of 1 or 0  which is the value we want for the filter operation
vector<DataRecord> filterDia(vector<DataRecord> in, int D0_or_1){
    // create a vector to collect the data
    vector<DataRecord> out;
    // for loop will iterate through all elements.
    for (int i = 0; i < in.size(); i++) {
        // checks if the value of the data of the diabeteies is the same value passed in the function.
        if (in[i].diabetes == D0_or_1) {
            out.push_back(in[i]);
        }
    }

    return out;
}

//The vector is created to filter out the the min and max of the age
vector<DataRecord> filterAge(vector<DataRecord> data, int low_Age, int high_Age){
    // checks if the age is greater then the or  =  ot the min or max ages
    if (low_Age > high_Age) {

        int temp = low_Age;
        low_Age = high_Age;
        high_Age = temp;

    }
    vector<DataRecord> out;
    // A for loop will iterate through the data in the vector to check for the age field.
    for (int i = 0; i < data.size(); i++) {
        if (data[i].age >= low_Age && data[i].age <= high_Age) {
            out.push_back(data[i]);
        }
    }
    return out;
}
