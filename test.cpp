#include <iostream>
#include <iomanip>

#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include <cerrno>

#include <dirent.h>

#include "student.h"
#include "studentList.h"

using namespace std; 

vector<string> dir_reader(const char*);
void read_record(vector<string> files);

Student* create_student(vector<string>); 
void sort_students(vector<Student*> &);
void create_rating(vector<Student*> &);
void write_rating_to_file(vector<Student*> &, int); // also could be passing the name of the file
                                        // could be like the initial_path + directory

int main(){
    try{
        const char* dirname = "/Users/angelina/Desktop/students/";  
        read_record(dir_reader(dirname)); 

    }
    catch(invalid_argument& e){
        //cout << "Invalid argument exception" << endl; 
        cerr << e.what() << endl; 
    }
    catch(runtime_error& e){
        cerr << e.what() << endl; 
    }
    // create_student();
}

// could be useful to pass the filename and number of record to make better error massage
// Student *
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

//StudentList
void read_record(vector<string> files)
{   
    StudentList student_list; 
    // float* average_list = new float[80];
    //vector<float> average_list;
    //vector<string> names;
    int bdgt_student_count = 0;
    int count = 0; 

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
        // cout << c << endl; 
        // int students_number = stoi(c); 
        // int bdgt_student_count = 0;

        // Read the Data from the file as String Vector
        vector<string> record; 
        string line, word;
    
        while (getline(fin, line)) {
            
            record.clear();
            // index of student record in input file
            count++; // !!!
            stringstream s(line);
            // cout << line << endl; 
    
            // read every column data of a row and store it in a string variable, 'word'
            while (getline(s, word, ',')) {
                // could count here how many 'columns' a table would have
                record.push_back(word);
            }

            
            student_list.add(create_student(record));
        }
        
        fin.close(); 
    
    }
    int scholarshipPercent = 40; 
    student_list.sort();
    student_list.createRating(scholarshipPercent, "rating.csv");
    // sort_students(student_list); 
    // create_rating(student_list); 
    // write_rating_to_file(student_list, int);

    // for(int i = 0; i < count; i++ ){
    //         cout << student_list[i]->getName() << " " << student_list[i]->getAvarage() << endl; 
    // }

    // for (vector<Student*>::iterator pObj = student_list.begin();
    //     pObj != student_list.end(); ++pObj) {
    //     delete *pObj; // Note that this is deleting what pObj points to,
    //                 // which is a pointer
    // }
    
}

//-
void sort_students(vector<Student*> &st_list){
    int count = st_list.size(); 
    //cout << count<< endl; 

    // !! merge sort
    for (int i = 0; i < count; i++){
        for (int j = 0; j < count; j++){
            if(st_list[i] -> getAvarage() > st_list[j] -> getAvarage()){
                swap(st_list[i], st_list[j]);
            }
        }
    }

    //cout << st_list[0]->getName() << endl;

}
//-
void create_rating(vector<Student*> &st_list){

    int count = st_list.size();
    int countOnBudget = 0, countForScholarship = 0; 
    int percentForScholarship = 40; // so it could possibly be changed later 

    for(int i = 0; i < count; i++){
        if(!st_list[i]->isOnContract()) {
            countOnBudget++;
        }
        else break; // because students are sorted in that way, that all on contract are at the end
    }
    // cout << countOnBudget << endl; 
    countForScholarship = countOnBudget * percentForScholarship / 100; 
    // cout << countForScholarship << endl; 
   
    write_rating_to_file(st_list, countForScholarship);
}
//-
void write_rating_to_file(vector<Student*> &st_list, int st_count){
    fstream fout;
    string filename = "rating10.csv"; 
    // !!! mb dont need to check if was opened before, just go with ios::app mode ?
    fout.open(filename, ios::app);
    if(!fout.is_open()){
        string msg = "Failed to open output file" + filename; 
        throw runtime_error(msg);
    }
    
    for (int i = 0; i < st_count; i++){
        fout << st_list[i]->getName() << "," << fixed << setprecision(3) << st_list[i]->getAvarage() << endl; 
    }

    fout.close();
   
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