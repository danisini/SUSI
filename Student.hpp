#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include "String.hpp"
#include "Program.hpp"
#include <vector>
class Student:public Program
{
private:
    size_t fn, year, groupNum, status;
    String name;///status-0 = zapisan
    double averMarks;
    ///static numStudents;
    std::vector<int> indexOfTakenOnes;///must fix it using dynamic array
public:

    Student(String, const size_t&, const size_t&, String);
    Student& operator=(const Student&);
    const size_t get_groupNum()const{return groupNum;}
    const size_t get_year()const{return year;}
    const size_t get_status()const{return status;}
    const double get_averMarks()const{return averMarks;}
    const size_t get_fn()const{return fn;}
    const String get_name()const{return name;}
    ///void set_groupNum(const size_t& newGN){groupNum = newGn;}
   /// void set_year(const size_t& newYear){year = newYear;}
    ///void set_status(const size_t& newStatus){status = newStatus;}

    void enroll(String, const size_t&, const size_t&, String);
    void enrollIn(String, const double&);
    void advance();
    void graduate();
    void interrupt();
    void resume();
    void print()const;
    void report()const;

};
void Student::enroll(String name_, const size_t& fn_, const size_t& group, String program)
{
    name = name_;
    fn = fn_;
    groupNum = group;
    programName = program;
}
Student& Student::operator=(const Student& other)
{
    name = other.name;
    fn = other.fn;
    groupNum = other.groupNum;
    averMarks = other.averMarks;
    year = other.year;
    status = other.status;
    programName = other.programName;
    return (*this);
}
void Student::advance()
{
    year ++;
}
void Student::graduate()
{
    for(size_t i = 0; i < numSubjects; i ++)
    {
        if(subjects[i].get_mark() <= 3.00)
        {
            std::cout << "This student can't graduate!" << std::endl;
            return;
        }
    }
    status = 2;
}
void Student::interrupt()
{
    status = 1;
}
void Student::resume()
{
    status = 0;
}
void Student::print()const
{
    std::cout << "name:" << name << " fn:" << fn << " year:" << year << " group:" << groupNum <<" program:" << programName <<  std::endl;
    /*std::cout << "Exams taken:" << std::endl;
    double aver = 0.0;
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        aver += subjects[indexOfTakenOnes[i]].get_mark();
        if(subjects[indexOfTakenOnes[i]].get_mark() >= 3.00)
        {
            subjects[indexOfTakenOnes[i]].print();
        }
    }
    std::cout << "Exams not taken:" << std::endl;
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(subjects[indexOfTakenOnes[i]].get_mark() < 3.00)
        {
            subjects[indexOfTakenOnes[i]].print();
        }
    }
    if(indexOfTakenOnes.size() != 0) std::cout << "Average grades:" << (double)aver/indexOfTakenOnes.size() << std::endl;
    */
    return;
}
void Student::report()const
{
    std::cout << "name:" << name << " fn:" << fn << " year:" << year << " group:" << groupNum << std::endl;
    std::cout << "Exams taken:" << std::endl;
    double aver = 0.0;
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        aver += subjects[indexOfTakenOnes[i]].get_mark();
        if(subjects[indexOfTakenOnes[i]].get_mark() >= 3.00)
        {
            subjects[indexOfTakenOnes[i]].print();
        }
    }
    std::cout << "Exams not taken:" << std::endl;
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(subjects[indexOfTakenOnes[i]].get_mark() < 3.00)
        {
            subjects[indexOfTakenOnes[i]].print();
        }
    }
    if(indexOfTakenOnes.size() != 0) std::cout << "Average grades:" << (double)aver/indexOfTakenOnes.size() << std::endl;
}
void Student::enrollIn(String subjName, const double& mark)
{
    for(size_t i = 0; i < numSubjects; i ++)
    {
        if(subjects[i].get_name() == subjName)
        {
            if(subjects[i].get_year() <= year)
            {
                subjects[i].set_mark(mark);
                indexOfTakenOnes.push_back(i);
                return;
            }
            else
            {
                std::cout << "This student is in lower year than allowed for this course!" << std::endl;
            }
        }
    }
    std::cout << "The subject was not found!" << std::endl;
}
Student::Student(String name_ = "", const size_t& fn_ = 0, const size_t& groupNum_ = 0, String program_ = ""):Program(program_)
{

    numSubjects = 0;
    name = name_;
    fn = fn_;
    groupNum = groupNum_;
    year = 1;
    status = 0;///zapisan
}
#endif // _STUDENT_H_
