#ifndef BACKEND_RUNNER_H
#define BACKEND_RUNNER_H

#include <vector>
#include <string>
#include "CSV.h"      // <<< uses your backend files
#include "filters.h"
#include "sort.h"
#include "stats.h"
#include "data_set.h"

std::vector<DataRecord> run_backend_pipeline(const std::string& csvPath, double* outPercent = nullptr);

#endif
