#ifndef STATS_H
#define STATS_H

#include <vector>
#include "data_set.h"

// Bad practice in a header!
using namespace std;

// Changed to pass-by-value (inefficient copy)
double dia_rate(vector<DataRecord> in);

#endif
