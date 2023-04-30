#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <dirent.h>
#include "student.h"

using namespace std; 


vector<string> dir_reader(const char*);

void read_record2(vector<string> files, const char* initial_path);
Student create_student(vector<string>); 
void sort_students(vector<Student> &);
void create_rating2(vector<Student> &);
void write_rating_to_file(vector<Student> &, int); // also could be passing the name of the file
                                        // could be like the initial_path + directory

int main(){

    const char* dirname = "/Users/angelina/Desktop/students/";  
    vector<string> filenames;
    filenames =dir_reader(dirname);

    read_record2(filenames, dirname); 
    
    // create_student();
}

// could be useful to pass the filename and number of record to make better error massage
Student create_student(vector<string> data){

    if(data[0].empty() || data[0] == " "){
        throw invalid_argument("The first record in a table row should be the name of a student, not an empty string.");
    }
  
    int contractValueInd = data.size() - 1; 
    int grades_count = contractValueInd - 1; 
    // cout<< "grades_count: " << grades_count << endl; 

    vector<float> grades_list;
    bool isOnContract; 

    for(int i = 1 ; i < grades_count + 1; i++){
        try{
            grades_list.push_back(stof(data[i]));
        }
        catch(std::invalid_argument& e){
            cerr << e.what()<<endl;
            std::cout << "Error when transforming file content to float numbers" << endl; 
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
    
    
    Student st1(data[0], grades_list, isOnContract);
    // cout << grades_list.size() << endl;
    // cout<< st1.getAvarage() << endl;

    return st1; 
}
void read_record2(vector<string> files, const char* initial_path)
{   
    vector<Student> student_list; 

    // float* average_list = new float[80];
    vector<float> average_list;
    vector<string> names;
    int bdgt_student_count = 0;
    int count = 0; 

    for(int i = 0; i < files.size(); i++)
    {
        string filename = initial_path + files[i]; 
        cout << filename << endl;
        fstream fin;

        try
        {
            fin.open(filename, ios::in);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << "Error when opening the file"<<'\n';
            cout <<  "Error when opening the file" << endl;
        }
        
        string c;
        getline(fin, c); 
        // cout << c << endl; 
        int students_number = stoi(c); 
        // int bdgt_student_count = 0;

        // Read the Data from the file as String Vector
        vector<string> record; 
        // vector<string> names;
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

            try{
                student_list.push_back(create_student(record));
            } 
            catch (const std::exception& e){
                cout << e.what() << endl; 
            }
            
        }
        
        fin.close(); 
    
    }
  
    sort_students(student_list); 
    create_rating2(student_list); 
    // write_rating_to_file(student_list, int);

    
    for(int i = 0; i < count; i++ ){
            cout << student_list[i].getName() << " " << student_list[i].getAvarage() << endl; 
    }
    
}
void sort_students(vector<Student> &st_list){
    int count = st_list.size(); 
    cout << count<< endl; 
    int countOnBudget = 0; 

    // !! merge sort
    for (int i = 0; i < count; i++){
        for (int j = 0; j < count; j++){
            if(st_list[i].getAvarage() > st_list[j].getAvarage()){
                swap(st_list[i], st_list[j]);
            }
        }
    }

    cout << st_list[0].getName() << endl;

}
void create_rating2(vector<Student> &st_list){

    int count = st_list.size();
    int countOnBudget = 0, countForScholarship = 0; 
    int percentForScholarship = 40; // so it could possibly be changed later 

    for(int i = 0; i < count; i++){
        if(!st_list[i].isOnContract()) {
            countOnBudget++;
        }
        else break; // because students are sorted in that way, that all on contract are at the end
    }
    cout << countOnBudget << endl; 
    countForScholarship = countOnBudget * percentForScholarship / 100; 
    cout << countForScholarship << endl; 
   
    write_rating_to_file(st_list, countForScholarship);

}
void write_rating_to_file(vector<Student> &st_list, int st_count){
    fstream fout;
    // !!! mb dont need to check if was opened before, just go with ios::app mode ?
    try
    {
        fout.open("rating1.csv", ios::app);
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << "Error when opening the file"<<'\n';
        cout <<  "Error when opening the file"<< endl;
    }

    for (int i = 0; i < st_count; i++){
        fout << st_list[i].getName() << "," << st_list[i].getAvarage() << endl; 
    }

    fout.close();
   
}

//update try catch with proper cerr

vector<string> dir_reader(const char* dirname){
    vector<string> filenames;
    DIR* dir = opendir(dirname); 
    if(dir == NULL){
        cout<< "An empty directory "<< dirname <<  endl; 
    }
    else{
        struct dirent* inside_dir; 
        inside_dir = readdir(dir); 

        while(inside_dir != NULL) {
           
            if(inside_dir->d_type == DT_REG){
                // !!! mb here strcat dirname and inside_dir->d_name
                filenames.push_back(inside_dir->d_name);
                cout << inside_dir->d_name << endl; 
            }
            if(inside_dir->d_type == DT_DIR && strcmp(inside_dir->d_name, ".")!= 0  && strcmp(inside_dir->d_name, "..")!= 0){
                char recursive_dir[100] = {0};
                strcat(recursive_dir, dirname); 
                strcat(recursive_dir, "/"); 
                strcat(recursive_dir, inside_dir->d_name);

                dir_reader(recursive_dir); 
            }
           
            inside_dir = readdir(dir);
            
        }
        
    }
    closedir(dir);
    return filenames; 
}