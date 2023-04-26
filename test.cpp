#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std; 


void read_record2()
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
    float* average_list = new float[students_number];

    // Read the Data from the file
    // as String Vector
    vector<string> record;
    string line, word, temp;
  
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
            for (int i = 1; i < budgetvalue; i++){
                average += stof(record[i]); 
            }
            average /=  budgetvalue - 1;
        }
        cout << average << endl; 
        cout << count << endl; 
        average_list[count-1] = average; 
       
  
    }
     for(int i =0; i < students_number; i++){
            cout << "av "<< (average_list[i]) <<endl; 
    }

}

int main(){


    read_record2(); 
    // create(); - inside read_record2 probably,
        // will accept the list of avarage marks and names/numbers in old file of students
}