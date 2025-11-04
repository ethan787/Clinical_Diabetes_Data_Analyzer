#ifndef FILTERS_H
#define FILTERS_H

#include <vector>
#include <string>
#include "data_set.h"

std::vector<DataRecord> filtergender(const std::vector<DataRecord>& in, const std::string& gender);
std::vector<DataRecord> filterdiabetes(const std::vector<DataRecord>& in, int diabetes_0_or_1);
std::vector<DataRecord> filter_age_range(const std::vector<DataRecord>& in, int minAge, int maxAge);

#endif
