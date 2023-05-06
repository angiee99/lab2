#include "studentList.h"

StudentList::StudentList(){
    _size = 0; 
    _isSorted = false;
    _budgetStCount = 0; 
    _scolarshipPercent = 0; 
    _scolarshipStCount = 0; 
};
StudentList::StudentList(std::vector<Student*> list){
    _size = list.size(); 
    _isSorted = false;
    for(int i = 0; i < _size; i++){
        _student_list[i] = list[i];
        if(!_student_list[i]->isOnContract()){
            _budgetStCount++; 
        } 
    }
    _scolarshipPercent = 0; 
    _scolarshipStCount = 0; 
};
StudentList::~StudentList(){
    _size = 0; 
    _isSorted = false;
    for (int i = 0; i < _size; i++) {
        delete _student_list[i]; 
    }
    _budgetStCount = 0; 
    _scolarshipPercent = 0; 
    _scolarshipStCount = 0; 
}

void StudentList::add(Student *newStudent){
    _student_list.push_back(newStudent); 
    _size++;
    _isSorted = false; 
    if(!newStudent->isOnContract()){
        _budgetStCount++; 
    }

};
void StudentList::sort(){
    if(!_isSorted){
        for (int i = 0; i < _size; i++){
            for (int j = 0; j < _size; j++){
                if(_student_list[i] -> getAvarage() > _student_list[j] -> getAvarage()){
                    std::swap(_student_list[i], _student_list[j]);
                }
            }
        }
        _isSorted = true;
    }

};

void StudentList::createRating(int scholarshipPercent){
    _scolarshipPercent = scholarshipPercent;
    if(!_isSorted){
        sort(); 
    }
    // for(int i = 0; i < _size; i++){
    //     if(!_student_list[i]->isOnContract()) {
    //         countOnBudget++;
    //     }
    //     else break; // because students are sorted in that way, that all on contract are at the end
    // }
    //std::cout << _budgetStCount << std::endl; 
    _scolarshipStCount = _budgetStCount * _scolarshipPercent / 100; 
    // cout << countForScholarship << endl; 
   
    //write_rating_to_file(countForScholarship);
};
void StudentList::createRating(int scholarshipPercent, std::string filename){
    _scolarshipPercent = scholarshipPercent;
    if(!_isSorted){
        sort(); 
    }
    _scolarshipStCount = _budgetStCount * _scolarshipPercent / 100; 
    // cout << _scolarshipStCount << endl; 
   
    writeRatingToFile(filename);
};

void StudentList::writeRatingToFile(std::string filename){
    std::fstream fout;
    // string filename = "rating10.csv"; 
    fout.open(filename, std::ios::out);
    if(!fout.is_open()){
        std::string msg = "Failed to open output file " + filename; 
        throw std::runtime_error(msg);
    }
    
    for (int i = 0; i < _scolarshipStCount; i++){
        fout << _student_list[i]->getName() << "," << std::fixed << std::setprecision(3) << _student_list[i]->getAvarage() << std::endl; 
    }

    fout.close();
}

float StudentList::get_minimum_grade(){
    if(_scolarshipStCount){
        return _student_list[_scolarshipStCount - 1]-> getAvarage();  
    }
    else {
        std::cout << "The rating is not created. Please first create rating to get minimum grade for scholarship" << std::endl; 
        return 0; 
    }
}