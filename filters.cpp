#include "filters.h"
#include <cctype>
#include <algorithm>

static std::string lower(std::string s){
    for (auto& c : s) c = (char)std::tolower((unsigned char)c);
    return s;
}

std::vector<DataRecord> filter_by_gender(const std::vector<DataRecord>& in, const std::string& gender){
    std::vector<DataRecord> out;
    std::string g = lower(gender);
    for (const auto& r : in) if (lower(r.gender) == g) out.push_back(r);
    return out;
}

std::vector<DataRecord> filter_by_diabetes(const std::vector<DataRecord>& in, int diabetes_0_or_1){
    std::vector<DataRecord> out;
    for (const auto& r : in) if (r.diabetes == diabetes_0_or_1) out.push_back(r);
    return out;
}

std::vector<DataRecord> filter_by_age_range(const std::vector<DataRecord>& in, int minAge, int maxAge){
    if (minAge > maxAge) std::swap(minAge, maxAge);
    std::vector<DataRecord> out;
    for (const auto& r : in) if (r.age >= minAge && r.age <= maxAge) out.push_back(r);
    return out;
}
