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
vector<string> dir_reader(const char*); // no change

int main(){

    const char* dirname = "/Users/angelina/Desktop/students/";  
    vector<string> filenames;
    filenames =dir_reader(dirname);

    read_record(filenames, dirname); 
    
    // create(); - inside read_record
        // will accept the list of avarage marks and names/numbers in old file of students
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
            count++; 
            // used for breaking words
            stringstream s(line);
            cout << line << endl; 
    
            // read every column data of a row and store it in a string variable, 'word'
            while (getline(s, word, ',')) {
                // could count here how many 'columns' a table would have

                // add all the column data of a row to a vector
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
