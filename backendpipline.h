#ifndef BACKEND_RUNNER_H
#define BACKEND_RUNNER_H
#include "CSV.h"
#include "filters.h"
#pragma once
using namespace std;

// Created a vetor to store data
vector<DataRecord> run_backend_pipeline(const string& data_CSV, double* percent_out = nullptr);

#endif
