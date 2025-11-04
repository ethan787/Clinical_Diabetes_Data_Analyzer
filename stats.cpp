#include "stats.h"

double dia_rate(const std::vector<DataRecord>& in){
    if (in.empty()) return 0.0;
    int d1 = 0;
    for (const auto& r : in) if (r.diabetes == 1) ++d1;
    return 100.0 * d1 / (double)in.size();
}
