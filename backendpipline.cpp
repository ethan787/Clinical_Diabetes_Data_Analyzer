#include "backendpipline.h"

std::vector<DataRecord> run_backend_pipeline(const std::string& csvPath, double* outPercent) {
    // 1) load
    auto all = load_CSV(csvPath);
    if (all.empty()) {
        if (outPercent) *outPercent = 0.0;
        return {};
    }

    // 2) filter (example: Female, ages 30–60)
    auto pick = filter_by_gender(all, "Female");
    pick = filter_by_age_range(pick, 30, 60);

     // 3) sort (beginner default)

    // // sort_records(pick, Algorithm::Insertion, SortField::Glucose, SortOrder::Asc);  // <<< only change needed
    //

    // 4) stat (optional)
    // if (outPercent) *outPercent =  dia_rate(pick);

    return pick;
}
