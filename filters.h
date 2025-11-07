#ifndef FILTERS_H
#define FILTERS_H
#include <vector>
#include <string>
#include "data_set.h"
using namespace std;

// creating the vectors to hold data for the  gender , diabetes , and age.
vector<DataRecord> filterGen(vector<DataRecord> data, const string& gender);

vector<DataRecord> filterDia(vector<DataRecord> data, int dia_0or_1);

vector<DataRecord> filterAge(vector<DataRecord> data, int low_Age, int topAge);

#endif
