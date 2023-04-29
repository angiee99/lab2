#include <string>
#include <vector>

class Student{
    std::string _name; 
    // int* _grades;
    std::vector<float> _grades; 
    bool _onContract;
    float _average; 
protected: 
    void countAverageGrade(){

        for(int i = 0; i < _grades.size(); i++){
            _average += _grades[i];
        }
        _average /= _grades.size(); 

    }
public:
    Student(std::string name, std::vector<float> grades, bool oncontract, float average = 0) {
        _name = name; 
        _onContract = oncontract;
        _grades = grades; 
        _average = average;
       
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

    std::string getName(){
        return _name;
    }
    bool isOnContract(){
        return _onContract; 
    }
    float getAvarage(){
        if (!_onContract && !_average){
            countAverageGrade();
        }
        return _average;
    }


};