#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std; 


void read_record(); 
void create_rating(int, float*, vector<string>); 

int main(){


    read_record(); 
    // create(); - inside read_record
        // will accept the list of avarage marks and names/numbers in old file of students
}

void read_record()
{
    // File pointer
    fstream fin;
    // Open an existing file
    fin.open("students1.csv", ios::in);

    //if on budget -> calculate avarage
  
    // Get the roll number
    // of which the data is required
    int value_ind, count = 0;
    int budgetvalue = 6; 
    
    string c;
    getline(fin, c); 
    cout << c << endl; 
    int students_number = stoi(c); 
    int bdgt_student_count = 0;

    float* average_list = new float[students_number];


    // Read the Data from the file
    // as String Vector
    vector<string> record;
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

void create_rating(int st_count, float* grade, vector<string> st_names){
    fstream fout;
    try
    {
        fout.open("rating.csv", ios::out);
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << "Error when opening the file"<<'\n';
        cout <<  "Error when opening the file"<< endl;
    }
    fout << st_count << "\n";

    for(int i = 0; i < st_count; i++){
        fout << st_names[i] << "," << grade[i]<<"\n";
    }


    
    fout.close(); 
}
