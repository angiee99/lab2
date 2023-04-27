#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <dirent.h>


using namespace std; 

void read_record(vector<string> files,  const char* initial_path); 
void create_rating(int, float*, vector<string>); 
vector<string> dir_reader(const char*);

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
    for(int i = 0; i < files.size(); i++){
    string filename = initial_path + files[i]; 
    cout << filename << endl;
    // File pointer
    fstream fin;
    // Open an existing file
   
    try
    {
        fin.open(filename, ios::in);
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << "Error when opening the file"<<'\n';
        cout <<  "Error when opening the file" << endl;
    }

    //if on budget -> calculate avarage
  
    // Get the roll number
    // of which the data is required
    int value_ind, count = 0;
    int budgetvalue = 6; 
    
    string c;
    getline(fin, c); 
    cout << c << endl; 
    // int students_number = stoi(c); 
    int students_number = 40;
    int bdgt_student_count = 0;

    float* average_list = new float[students_number];


    // Read the Data from the file
    // as String Vector
    vector<string> record; // could be char** array
    vector<string> names;
    string line, word;
  
    while (getline(fin, line)) {
        
        record.clear();
        // index of student record in input file
        count++; 
        // used for breaking words
        stringstream s(line);
        cout << line << endl; 
  
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
    
            // add all the column data
            // of a row to a vector
            record.push_back(word);
        }

        // * making lowercase all 
        float average = 0; 
        if (record[budgetvalue] == "TRUE" || record[budgetvalue] == "true"){
            names.push_back(record[0]); 
            

            for (int i = 1; i < budgetvalue; i++){
                average += stof(record[i]); 
            }
            average /=  budgetvalue - 1;

            average_list[bdgt_student_count] = average; 
            bdgt_student_count++;
        }
        cout << average << endl; 
        cout << count << endl; 
        
       
    }
    for(int i =0; i < students_number; i++){
            cout << "av "<< (average_list[i]) <<endl; 
    }
    for(int i =0; i < bdgt_student_count; i++){
           cout << "st "<< (names[i]) <<endl; 
    }


    fin.close(); 

    create_rating(bdgt_student_count, average_list, names); 
    
    }
}

void create_rating(int st_count, float* grade, vector<string> st_names){
    fstream fout;

    try
    {
        fout.open("rating1.csv", ios::app);
        //fout.open("rating.csv", ios::app); // here the probl with the first record
            // with st_count 
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << "Error when opening the file"<<'\n';
        cout <<  "Error when opening the file"<< endl;
    }
    
    // fout << st_count << "\n";

    for(int i = 0; i < st_count; i++){
        fout << st_names[i] << "," << grade[i]<<"\n";
    }
    
    fout.close(); 
}

// functoin to sort students acc to their grade, 
// count 40% of budget students and extracting the minimal mark 
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