#include "stats.h"

using namespace std; // Added

// Changed to pass-by-value (from header)
double dia_rate(vector<DataRecord> in){
    if (in.size() == 0) return 0.0; // Changed from .empty()

    int d1 = 0;

    // C-style for loop
    for (int i = 0; i < in.size(); i++) {
        if (in[i].diabetes == 1) {
            d1 = d1 + 1; // Changed from ++d1
        }
    }
    return 100.0 * d1 / (double)in.size();
}
