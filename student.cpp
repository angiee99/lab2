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

Student::Student(Student &another){
    this-> _name = another.getName(); 
    this-> _onContract = another.isOnContract();
    for(int i = 0; i < another._grades.size(); i++){
        this->_grades[i] = another._grades[i];
    }
    this->_average = another.getAvarage(); 

}

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
float Student::getNthGrade(int n){
    if( n < _grades.size()){
        return _grades[n]; 
    }
    else {
        std::string msg = "Cannot get " + std::to_string(n) + "th grade, as the grade count is " + std::to_string(_grades.size());
        throw std::out_of_range("msg"); 
    }
}