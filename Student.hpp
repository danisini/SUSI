#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include <string>
#include "Speciality.hpp"
class Student:public Speciality
{
private:
    string name;
    size_t fn, courseNum, groupNum;
    char status[9];
    double averMarks;
    size_t specIndexTaken[64];///must fix it using dynamic array
public:
    void addMark(const Subject&, const double&);

};
void Student::addMark(const Subject& subj, const double& mark)
{
    for(size_t i = 0; i < numSubjects; i ++)
    {
        if(subjects[specIndexTaken[i]].name == subj.name)
        {
            subjects[specIndexTaken[i]].mark = mark;
            return;
        }
    }
    std::cout << "The subject was not found!" << std::endl;
}
#endif // _STUDENT_H_
