#pragma once
#include "studentList.h"
#include <fstream>
#include <sstream>
#include <cerrno>
#include <dirent.h>

using namespace std; 

vector<string> dir_reader(const char*);
void read_record(vector<string> files, StudentList *);
Student* create_student(vector<string>); 
