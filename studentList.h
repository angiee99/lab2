#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "student.h"

class StudentList{
   std::vector<Student*> _student_list;
   int _size; 
   bool _isSorted; 
   int _budgetStCount; 
   int _scolarshipPercent; 
   int _scolarshipStCount; 
protected:
   void writeRatingToFile(std::string);
public: 
   StudentList();
   StudentList(std::vector<Student*>);
   ~StudentList();

   void add(Student*); 
   void sort();
   void createRating(int); 
   void createRating(int, std::string);
   float get_minimum_grade(); 
};