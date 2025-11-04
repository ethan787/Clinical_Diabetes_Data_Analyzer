#include "sort.h"
#include <algorithm>
#include <optional>

static double key_of(const DataRecord& r, SortField f) {
    switch (f) {
    case SortField::Age:
        return static_cast<double>(r.age);

    case SortField::Glucose:
        // r.glucose is std::optional<double>
        return r.glucose.has_value() ? *r.glucose : -1.0;

    case SortField::HbA1c:
        // r.hba1c is std::optional<double>
        return r.hba1c.has_value() ? *r.hba1c : -1.0;

    case SortField::BMI:
        // r.bmi is std::optional<double>
        return r.bmi.has_value() ? *r.bmi : -1.0;
    }
    return -1.0; // fallback
}

// Put "missing" (-1) at end for Asc, at start for Desc.
static bool before(const DataRecord& a, const DataRecord& b, SortField f, SortOrder o){
    double ka = key_of(a, f), kb = key_of(b, f);
    if (ka < 0 && kb >= 0) return (o == SortOrder::Desc);
    if (kb < 0 && ka >= 0) return (o == SortOrder::Asc);
    return (o == SortOrder::Asc) ? (ka < kb) : (ka > kb);
}

static void insertion(std::vector<DataRecord>& a, SortField f, SortOrder o){
    for (size_t i = 1; i < a.size(); ++i){
        DataRecord x = a[i]; size_t j = i;
        while (j > 0 && before(x, a[j-1], f, o)){ a[j] = a[j-1]; --j; }
        a[j] = x;
    }
}

static void bubble(std::vector<DataRecord>& a, SortField f, SortOrder o){
    if (a.empty()) return;
    for (size_t n = a.size(); n > 1; --n){
        bool swapped = false;
        for (size_t i = 1; i < n; ++i){
            if (!before(a[i-1], a[i], f, o)){
                std::swap(a[i-1], a[i]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void sort_records(std::vector<DataRecord>& data, Algorithm algo, SortField field, SortOrder order){
    if (data.size() < 2) return;
    if (algo == Algorithm::Insertion) insertion(data, field, order);
    else                               bubble(data, field, order);
}
