#include "CSV.h"
#include <fstream>
#include <cctype>
#include <stdlib.h>

using namespace std;

// The bool function will check if there is any whitespaces which will return true
static bool is_space(char white_space){


    if (white_space == ' ' || white_space == '\t' ){
        return true;}
    if ( white_space == '\n' || white_space == '\r' ){
        return true;}

    if (white_space == '\f' || white_space == '\v'){

        return true;}

    else{

        return false;
    }
}

static string trim(const string& data){
    // intialze the variables for the trim function from beginning to end
    int first = 0, second = data.size(); //starts at the beginning and then at the end

    // This line will move the first to the right in the bounds which will leave the last char as a white spcae
    while (first < second && is_space(data[first])) {

        first = first + 1;// this will start the index by one

    }
    //This line will move the second to the back in the bounds which will leave the last char as a white spcae
    while (second > first && is_space(data[second-1])) {

    second = second - 1; // This line  will decrease the index by 1
    }
    // return the value of the data from the trim function
    return data.substr(first, second - first);
}

// This function will split the comma
static vector<string> split_csv_line(const string& data_line){

    vector<string> result_1; // creating a vector for the inout lines
    // created the hold variable to accumulator field
    string hold;
    // The for loop is used iterate through all inout lines

    for(int j = 0; j < data_line.length(); j++){
        char logic = data_line[j];
        // checks if there is a comma we intercpet
        if(logic == ','){
            // This line will store the field of the element
            result_1.push_back(trim(hold));
            hold.clear();
        }
        // This line will append the the character to the current field
        else {
            hold = hold + logic;

        }
    }
    // This line will the result the the field
    result_1.push_back(trim(hold));

    return result_1;
}

// teh function will take the value which is a copy and return a lower_case string
static string lower(string data){
    // The loop will go through the characters in the strings
    for (int z = 0; z< data.length(); z++) {
        // this line will transform the char to a lowercase
        data[z] = (char)std::tolower((unsigned char)data[z]);
    }
    // returns teh data
    return data;
}

//
static int to_int(const string& data_string, int result = -1){

    if (data_string.empty() == true){
        // return the result
        return result;
        }
    // This line will return 0 if there is no digits present
    else{return std::atoi(data_string.c_str());
        }

}


static void to_double_and_flag(const string& data_string, double& data_val, bool& flagged) {

    // checking if the data is empty
    if (data_string.empty() == true) {

        data_val = 0.0;
        flagged = false;
        // this will return if there is a failure

        return;
    }

    // This line is a leading numeriacl number which will not focus on trailing stuff
    double data_1 = std::atof(data_string.c_str());

    if (data_1 < 0) { // checks if there are neg numbers and will mark them as invalid

        data_val = 0.0;
        flagged = false;

    }
    // The else statment will have parsed values
    else {
        data_val = data_1;
        flagged = true;
    }
}

// create a int function
int find_col_index(vector<string> data_3, const char* lable){
    // A string is intialized to make a copy of target lable.

    string key_1 = lower(lable);
    // iterate through the vector to see each header string
    for(size_t i = 0; i <data_3.size(); ++i)
        //checks if there is a lower case and compare
        if(lower(data_3[i]) == key_1)

            return (int)i;
    return -1;
}


// This function will load the data in the data pipeline (data records)
vector<DataRecord> load_CSV(const string& CSV_pipe){

    ifstream in(CSV_pipe); // this line will read the CSV file
    // create a vector to hold all parsed row's
 vector<DataRecord> Matrix_rows;
    // checks if the file can not open

    if(!in) {

     return Matrix_rows;

    }

    string header;
    // checks if the file dose not have nothing
    if(!std::getline(in, header)){
        // returns the result
        return Matrix_rows;
    }

    // this vector will store the data into the columns
    vector<string> Data_hdrs = split_csv_line(header);

    // The lines below will search for the indices of each column
    int the_id = find_col_index(Data_hdrs, "id"),

         the_g = find_col_index(Data_hdrs, "gender"),

        the_a  = find_col_index(Data_hdrs, "age"),

        the_h  = find_col_index(Data_hdrs, "hypertension"),

    the_hd = find_col_index(Data_hdrs, "heart_disease"),

         the_b  = find_col_index(Data_hdrs, "bmi"),

        the_a1 = find_col_index(Data_hdrs, "hba1c_level"),

        the_gl = find_col_index(Data_hdrs, "blood_glucose_level"),

       the_d  = find_col_index(Data_hdrs, "diabetes"),

        the_s = find_col_index(Data_hdrs, "smoking_history");
    // Initliz a string to buffer each sub_sequantrecord
    string line;

    while (std::getline(in, line)){

        // The if statements will skip any whitspaces there

        if (trim(line).empty()
            ){
            // Skips the line
            continue;
        }

        // This line will split the lines to the right fields
        vector<string> data_columns = split_csv_line(line);


        DataRecord record_pop;
        // The lines below will pull the fields strings adn check if they are in bounds
        string id_str= (the_id >= 0 && the_id < (int)data_columns.size()) ? data_columns[the_id] : "";
        string g_str= (the_g >= 0  && the_g< (int)data_columns.size()) ? data_columns[the_g] : "";
        string a_str= (the_a >=0 && the_a < (int)data_columns.size()) ? data_columns[the_a] : "";
        string h_str= (the_h >= 0  && the_h< (int)data_columns.size()) ? data_columns[the_h] : "";
        string hd_str =  (the_hd >=0 && the_hd < (int)data_columns.size()) ? data_columns[the_hd] : "";
        string s_str = (the_s >= 0  && the_s<  (int)data_columns.size()) ? data_columns[the_s] : "";
        string b_str =  (the_b >= 0 && the_b <  (int)data_columns.size()) ? data_columns[the_b] : "";
        string a1_str = (the_a1 >=  0 && the_a1 <(int)data_columns.size()) ? data_columns[the_a1] : "";
        string gl_str = (the_gl >=0 && the_gl <(int)data_columns.size()) ? data_columns[the_gl] : "";
        string d_str =  (the_d >= 0  && the_d  < (int)data_columns.size()) ? data_columns[the_d] : "";
        // the lines below are the prase int

         record_pop.id = to_int(id_str, -1);

         record_pop.gender = g_str;
         record_pop.age = to_int(a_str, -1);
         record_pop.hypertension  = to_int(h_str, 0);
         record_pop.heart_disease = to_int(hd_str, 0);
         record_pop.smoke_history = s_str;

         // The lines bwloq are the double parse and presence flags.
        to_double_and_flag(b_str,  record_pop.bmi,  record_pop.has_bmi);
        to_double_and_flag(a1_str,  record_pop.hba1c,  record_pop.has_hba1c);
        to_double_and_flag(gl_str,  record_pop.glucose,  record_pop.has_glucose);

         record_pop.diabetes = to_int(d_str, 0);// This line will have the parse of the dia flag

        Matrix_rows.push_back(record_pop);// store the data
    }
    return Matrix_rows;
}
