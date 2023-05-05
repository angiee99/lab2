#pragma once
#include <string>
#include <vector>

class Student{
    std::string _name; 
    // int* _grades;
    std::vector<float> _grades; 
    bool _onContract;
    float _average; 
protected: 
    void countAverageGrade();
public:
    Student(std::string name, std::vector<float> grades, bool oncontract);
    // Student(Student &another)
    // ~Student()
    std::string getName();
    bool isOnContract();
    float getAvarage();
};