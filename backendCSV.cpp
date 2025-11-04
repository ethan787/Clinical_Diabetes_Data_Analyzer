#include "CSV.h"
#include <fstream>
#include <cctype>

static bool is_space(char c){ return std::isspace((unsigned char)c); }

static std::string trim(const std::string& s){
    size_t i = 0, j = s.size();
    while (i < j && is_space(s[i])) ++i;
    while (j > i && is_space(s[j-1])) --j;
    return s.substr(i, j - i);
}

// very basic: split by comma (no quotes support)
static std::vector<std::string> split_csv_line(const std::string& line){
    std::vector<std::string> out; std::string cur;
    for(char c : line){
        if(c == ','){ out.push_back(trim(cur)); cur.clear(); }
        else        { cur.push_back(c); }
    }
    out.push_back(trim(cur));
    return out;
}

static std::string lower(std::string s){
    for (auto& c : s) c = (char)std::tolower((unsigned char)c);
    return s;
}

static int to_int(const std::string& s, int def = -1){
    if (s.empty()) return def;
    try { return std::stoi(s); } catch (...) { return def; }
}

static double to_double(const std::string& s, double def = -1.0){
    if (s.empty()) return def;
    try { return std::stod(s); } catch (...) { return def; }
}

std::vector<DataRecord> load_csv(const std::string& path){
    std::ifstream in(path);
    std::vector<DataRecord> rows;
    if(!in) return rows;

    std::string header;
    if(!std::getline(in, header)) return rows;
    auto hdrs = split_csv_line(header);

    auto find_col = [&](const char* name){
        std::string key = lower(name);
        for(size_t i = 0; i < hdrs.size(); ++i)
            if(lower(hdrs[i]) == key) return (int)i;
        return -1;
    };

    int the_id = find_col("id"),the_g = find_col("gender"), the_a  = find_col("age"), the_h  = find_col("hypertension") ,the_hd = find_col("heart_disease"), the_b  = find_col("bmi"),
        the_a1 = find_col("hba1c_level"),
        the_gl = find_col("blood_glucose_level"),
        the_d  = find_col("diabetes"),  the_s = find_col("smoking_history");




    std::string line;
    while (std::getline(in, line)){
        if (trim(line).empty()) continue;
        auto cols = split_csv_line(line);
        auto S = [&](int idx)->std::string{
            return (idx >= 0 && idx < (int)cols.size()) ? cols[idx] : "";
        };

        DataRecord q;
        q.id= to_int(S(the_id), -1); q.gender = S(the_g); q.age = to_int(S(the_a), -1); q.hypertension  = to_int(S(the_h), 0);

        q.heart_disease = to_int(S(the_hd), 0); q.smoke_history = S(the_s); q.bmi = to_double(S(the_b), -1.0);  q.hba1c  = to_double(S(the_a1), -1.0);

         q.glucose = to_int(S(the_gl), -1);  q.diabetes = to_int(S(the_d), 0);  rows.push_back(q);


    }
    return rows;
}
