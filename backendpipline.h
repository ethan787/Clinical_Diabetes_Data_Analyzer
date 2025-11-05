#ifndef BACKEND_RUNNER_H
#define BACKEND_RUNNER_H

#include "CSV.h"      // <<< uses your backend files
#include "filters.h"
#pragma once

std::vector<DataRecord> run_backend_pipeline(const std::string& csvPath, double* outPercent = nullptr);

#endif
