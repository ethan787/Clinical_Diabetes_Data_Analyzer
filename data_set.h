#ifndef DATA_set_H
#define DATA_set_H
#pragma once
#include <string>
#include <optional>
using namespace std;

struct DataRecord {
    // Intializing the variables for the data
    int id = 0, age = 0, hypertension = 0, heart_disease = 0,  diabetes = 0, clinical_notes;
    // intializing the strings
     string gender, location, race , smoke_history;
 // intializing the doubles
    double bmi = 0.0,  hba1c = 0.0 , glucose = 0.0;
// intializing the trur of false bools
    bool has_bmi = false, has_hba1c = false, has_glucose = false;
};

#endif
