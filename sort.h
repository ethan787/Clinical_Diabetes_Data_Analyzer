#ifndef SORT_H
#define SORT_H
#include <vector>
#include "data_set.h"
using namespace std;


// The lines blow hold the algorthms we need to sort by
    enum class SortField { Age, Glucose, HbA1c, BMI };

 enum class SortOrder { Asc, Desc };// This line will go up or down
// This line will pick the algorithm
     enum class Algorithm { Quick, Merge };

void sort_records(vector<DataRecord>& pipline_data, Algorithm sort_algo, SortField field,SortOrder alfo_order);

#endif
