#include "backendpipline.h"
using namespace std;

// Created a vector to run the data
vector<DataRecord> run_backend_pipeline(const string& data_CSV, double*  percent_out) {

    // We are loading teh data of the information
    vector<DataRecord> all = load_CSV(data_CSV);
    // create a if statement on this line to check if data is empty or not
    if (all.empty()) {
        // if there is a percent out there
        if (percent_out) *percent_out = 0.0;

        return {};
    }

   // This vector will create a vector to filter out for the Gen
    vector<DataRecord> select = filterGen(all, "Female");

    select = filterAge(select, 30, 60);

    return select;
}
