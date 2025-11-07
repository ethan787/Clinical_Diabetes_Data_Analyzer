#ifndef CSV_H
#define CSV_H
#include <string>
#include <vector>
#include "data_set.h"
using namespace std;


// The vector is created to load the data from the CSV file
vector<DataRecord> load_CSV(const string& pipeline_data);

#endif
