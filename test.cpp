#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <dirent.h>
#include "student.cpp"

using namespace std; 

void read_record(vector<string> files,  const char* initial_path); 
void create_rating(int, vector<float>, vector<string>); 
vector<string> dir_reader(const char*);

void read_record2(vector<string> files, const char* initial_path);
Student create_student(vector<string>); 

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

    vector<float> grades_list;
    bool isOnContract; 

    for(int i = 1 ; i < grades_count ; i++){
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
            fin.open("1.csv", ios::in);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << "Error when opening the file"<<'\n';
            cout <<  "Error when opening the file" << endl;
        }

        // int value_ind, count = 0;
        int contractValueInd = 6; //!!!!!!!!!!!!!!!!!!could be different
        
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
            cout << line << endl; 
    
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
        for(int i = 0; i < count; i++ ){
            cout << student_list[i].getName() << " " << student_list[i].getAvarage() << endl; 
        }
        fin.close(); 

    }
    //create_rating(bdgt_student_count, average_list, names); 

    // delete[] average_list;
    
}



//update try catch with proper cerr
void read_record(vector<string> files, const char* initial_path)
{   
    // float* average_list = new float[80];
    vector<float> average_list;
    vector<string> names;
    int bdgt_student_count = 0;

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

        int value_ind, count = 0;
        int contractValueInd = 6; //!!!!!!!!!!!!!!!!!!could be different
        
        string c;
        getline(fin, c); 
        cout << c << endl; 
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
            cout << line << endl; 
    
            // read every column data of a row and store it in a string variable, 'word'
            while (getline(s, word, ',')) {
                // could count here how many 'columns' a table would have

                record.push_back(word);
            }

    

            contractValueInd = record.size()-1;
            cout << contractValueInd << endl; 

            // * making lowercase all 
            float average = 0; 
            if (record[contractValueInd] == "FALSE" || record[contractValueInd] == "false"){
                names.push_back(record[0]); 
                
                for (int i = 1; i < contractValueInd; i++){
                    average += stof(record[i]); 
                }
                average /=  contractValueInd - 1;
                // average_list[bdgt_student_count] = average; 
                
                average_list.push_back(average);
                bdgt_student_count++;
            }

            // cout << average << endl; 
            // cout << count << endl; 
            
        }

        // for(int i =0; i < students_number; i++){
        //         cout << "av "<< (average_list[i]) <<endl; 
        // }
        // for(int i =0; i < bdgt_student_count; i++){
        //     cout << "st "<< (names[i]) <<endl; 
        // }

        fin.close(); 

    }
    create_rating(bdgt_student_count, average_list, names); 

    // delete[] average_list;
    
}

void create_rating(int st_count, vector<float> grade, vector<string> st_names){
    fstream fout;

    fout.open("rating3.csv", ios::in);
    if (fout){
        try
        {
            fout.open("rating3.csv", ios::app);
            //fout.open("rating.csv", ios::app); // here the probl with the first record
                // with st_count 
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << "Error when opening the file"<<'\n';
            cout <<  "Error when opening the file"<< endl;
        }
    }
    else{
        try
        {
            fout.open("rating3.csv", ios::out);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << "Error when opening the file"<<'\n';
            cout <<  "Error when opening the file"<< endl;
        }
    }
    
    // sorting students
    for(int i = 0; i < st_names.size(); i++){
        for (int j = 0; j < st_names.size(); j++){
            if(grade[i] > grade[j]){
                swap(grade[i], grade[j]);
                swap(st_names[i], st_names[j]);
            }
        }
    }
    // fout << st_count << "\n";

    for(int i = 0; i < st_names.size(); i++){
        fout << st_names[i] << "," << grade[i]<<"\n";
    }
    
    fout.close(); 
}


// count 40% of budget students and extracting the minimal mark 
// checking if name is void 
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