#include <iostream>
#include <iomanip>
#include <stdio.h>

// #include "student.h"
#include "studentList.h"
#include "dataParse.h"

using namespace std; 

int main(int argc, char *argv[]){
    try{
        const char *dirname = argv[1]; 
        // const char* dirname = "/Users/angelina/Desktop/students/";  
        
        StudentList *student_list = new StudentList; 
        read_record(dir_reader(dirname), student_list); 
        student_list->sort();
        
        int scholarshipPercent = 40; 
        student_list-> createRating(scholarshipPercent, "rating.csv");

        cout <<"Miminum grade for scholarship: " << fixed << setprecision(3) << student_list-> get_minimum_grade() << endl;

    }
    catch(invalid_argument &e){
        //cout << "Invalid argument exception" << endl; 
        cerr << e.what() << endl; 
    }
    catch(length_error &e){
        cerr << e.what() << endl; 
    }
    catch(out_of_range &e){
        cerr << e.what() << endl; 
    }
    catch(runtime_error &e){
        cerr << e.what() << endl; 
    }
    catch(exception &e){
        cerr << e.what() << endl; 
    }

}






