
#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>
#include "data_set.h"

// Loads a CSV with headers:
std::vector<DataRecord> load_CSV(const std::string& path);

#endif
