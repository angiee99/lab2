#include "student.h"

Student::Student(std::string name, std::vector<float> grades, bool oncontract) {
    _name = name; 
    _onContract = oncontract;
    _grades = grades; 
    _average = 0;
       
        // with argument gradesCount; 
        // int* _grades = new int[2*countOfGrades]; //2*countOfGrades just for additional space for now
        // for(int i = 0; i < countOfGrades; i++){
        //     _grades[i] = grades[i]; 
        // }
}
    // Student(Student &another){
    //     _name = another.getName(); 
    //     _onContract = another.isOnContract();
    //     int* _grades = new int[20]; //2*countOfGrades just for additional space for now
    //     for(int i = 0; i < countOfGrades; i++){
    //         _grades[i] = grades[i]; 
    //     }
    // }

    // ~Student(){ 
    //     _name = "";
    //     delete[] _grades; 
    // }

std::string Student::getName(){
    return _name;
}
bool Student::isOnContract(){
    return _onContract; 
}
float Student::getAvarage(){
    if (!_onContract && !_average){
        countAverageGrade();
    }
    return _average;
}
void Student::countAverageGrade(){

    for(int i = 0; i < _grades.size(); i++){
        _average += _grades[i];
    }
    _average /= _grades.size(); 

}
