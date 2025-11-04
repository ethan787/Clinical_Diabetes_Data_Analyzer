#ifndef DATA_set_H
#define DATA_set_H
#pragma once
#include <string>
#include <optional>

struct DataRecord {
    int id{},  age{} , hypertension{} , heart_disease{}, diabetes{};
    std :: string gender , location, race , smoke_history;
    std::optional<double> bmi , hba1c,  glucose;
    std::string clinical_notes;
};



#endif // DATA_MODEL_H
