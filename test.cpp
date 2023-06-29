#include <iostream>
#include <iomanip>
#include <stdio.h>

#include "studentList.h"
#include "dataParse.h"

using namespace std; 

int main(int argc, char *argv[]){
    
    try{
        if(argc != 2){
            cerr << "The command argument should include 2 arguments: \n-the name of the program \n-the directory name" << endl; 
            return 1;       
        }
        const char *dirname = argv[1];  
        
        StudentList *student_list = new StudentList; 
        read_record(dir_reader(dirname), student_list); 
        student_list->sort();
        
        int scholarshipPercent = 40; 
        student_list-> createRating(scholarshipPercent, "rating.csv");

        cout <<"Miminum grade for scholarship: " << fixed << setprecision(3) << student_list-> get_minimum_grade() << endl;

    }
    catch(invalid_argument &e){
        cerr << "Exception invalid_argument:\n" << e.what() << endl; 
    }
    catch(length_error &e){
        cerr << "Exception length_error:\n" << e.what() << endl; 
    }
    catch(out_of_range &e){
        cerr << "Exception out_of_range:\n" << e.what() << endl; 
    }
    catch(runtime_error &e){
        cerr << "Exception runtime_error:\n" << e.what() << endl; 
    }
    catch(exception &e){
        cerr << "Default exception occured:\n" << e.what() << endl; 
    }

}






