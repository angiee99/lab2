#include "dataParse.h"
// includes validation
Student* create_student(vector<string> data){

    if(data[0].empty() || data[0] == " "){
        string msg = "The first record in a table row (here: "+ data[0] + ")should be the name of a student, not an empty string."; 
        throw invalid_argument(msg);
    }
  
    int contractValueInd = data.size() - 1; 
    int grades_count = contractValueInd - 1; 
    // cout<< "grades_count: " << grades_count << endl; 

    vector<float> grades_list;
    bool isOnContract; 

    for(int i = 1 ; i < grades_count + 1; i++){
        
        grades_list.push_back(stof(data[i]));
        if(errno ==  ERANGE){
            string msg = "Error when transforming file content to float numbers"; 
            throw runtime_error(msg); 
        }

    }
    if(data[contractValueInd] == "FALSE" || data[contractValueInd] == "fasle"){
        isOnContract = false; 
    }
    else if (data[contractValueInd] == "TRUE" || data[contractValueInd] == "true")
    {
        isOnContract = true; 
    }
    else{
        throw invalid_argument("The last value in a file row shoudl be either TRUE or FALSE");
    }
    
    Student* st1 = new Student(data[0], grades_list, isOnContract);
    // cout << grades_list.size() << endl;
    // cout<< st1.getAvarage() << endl;

    return st1; 
}

void read_record(vector<string> files,  StudentList *student_list)
{   
    for(int i = 0; i < files.size(); i++)
    {
        // cout << files[i] << endl;
        ifstream fin;
        fin.open(files[i], ios::in);
        
        if(!fin.is_open()){
            string msg = "Failed to open input file" + files[i]; 
            throw runtime_error(msg);
        }

        string c;
        getline(fin, c); 
        
        vector<string> record; 
        string line, word;
    
        while (getline(fin, line)) {
            
            record.clear();
            stringstream s(line);
            // cout << line << endl; 

            // read every column data of a row and store it in a string variable, 'word'
            while (getline(s, word, ',')) {
                record.push_back(word);
            }

            student_list -> add(create_student(record));
        }
        fin.close(); 
    }

    // int scholarshipPercent = 40; 
    // student_list.sort();
    // student_list.createRating(scholarshipPercent, "rating.csv");
    // cout <<"Miminum grade for scholarship: " << student_list.get_minimum_grade() << endl;
}

vector<string> dir_reader(const char* dirname){
    vector<string> filenames;
    DIR* dir = opendir(dirname); 
    if(dir == NULL){
        string msg = "Error opening the directory"; 
        cout<< "An empty directory "<< dirname <<  endl; 
        throw runtime_error(msg); 
    }
    else{
        struct dirent* inside_dir; 
        inside_dir = readdir(dir); 

        while(inside_dir != NULL) {
            char full_path[100] = {0}; 
            strcat(full_path, dirname); 
            strcat(full_path, inside_dir->d_name);

            if(inside_dir->d_type == DT_REG && strcmp(inside_dir->d_name, ".DS_Store")!= 0){
            
                filenames.push_back(full_path);
                //cout << inside_dir->d_name << endl; 
            }
            if(inside_dir->d_type == DT_DIR && strcmp(inside_dir->d_name, ".")!= 0  && strcmp(inside_dir->d_name, "..")!= 0){
                dir_reader(full_path); 
                // cout << inside_dir->d_name << endl;
            }
            
            inside_dir = readdir(dir);
        }
    }
    closedir(dir);
    return filenames; 
}