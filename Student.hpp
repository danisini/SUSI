#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include "String.hpp"
#include "Program.hpp"
class Student:public Program
{
private:
    size_t fn, year, groupNum, status;
    String name;///status-0 = zapisan
    double averMarks;
    ///static numStudents;
    size_t specIndexTaken[64];///must fix it using dynamic array
public:

    Student(String, const size_t&, const size_t&,String);

    const size_t get_groupNum()const{return groupNum;}
    const size_t get_year()const{return year;}
    const size_t get_status()const{return status;}
    const double get_averMarks()const{return averMarks;}
    void set_groupNum(const size_t& newGN){groupNum = newGn;}
    void set_year(const size_t& newYear){year = newYear;}
    void set_status(const size_t& newStatus){status = newStatus;}

    void addMark(const Subject&, const double&);
    void addSubject(const Subject&);
};
void Student::addSubject(const Subject& subj_)
{
}
void Student::addMark(const Subject& subj, const double& mark)
{
    for(size_t i = 0; i < numSubjects; i ++)
    {
        if(subjects[specIndexTaken[i]].get_name() == subj.get_name())
        {
            subjects[specIndexTaken[i]].set_mark(mark);
            return;
        }
    }
    std::cout << "The subject was not found!" << std::endl;
}
Student::Student(String name_, const size_t& fn_, const size_t& groupNum_, String program_):Program(program_)
{
    name = name_;
    fn = fn_;
    groupNum = groupNum_;
    year = 1;
    status = 0;///zapisan
}
#endif // _STUDENT_H_
