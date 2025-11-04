#ifndef SORT_H
#define SORT_H

#include <vector>
#include "data_set.h"

enum class SortField { Age, Glucose, HbA1c, BMI };
enum class SortOrder { Asc, Desc };
enum class Algorithm { Insertion, Bubble };

void sort_records(std::vector<DataRecord>& data, Algorithm algo, SortField field,SortOrder order);

#endif
