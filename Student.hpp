#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include "String.hpp"
#include "Program.hpp"
#include <vector>
class Student
{
private:
    size_t fn, year, groupNum, status;
    String name;///status-0 = zapisan
    double averMarks;
    Program program;
    ///static numStudents;
    std::vector<int> indexOfTakenOnes;///must fix it using dynamic array
public:
    Student();
    Student(String, const size_t&, const size_t&, const Program&);
    Student& operator=(const Student&);
    const size_t get_groupNum()const{return groupNum;}
    const size_t get_year()const{return year;}
    const size_t get_status()const{return status;}
    const double get_averMarks()const{return averMarks;}
    const size_t get_fn()const{return fn;}
    const String get_name()const{return name;}
    const String get_programName()const{return program.get_program();}
    ///void set_groupNum(const size_t& newGN){groupNum = newGn;}
   /// void set_year(const size_t& newYear){year = newYear;}
    ///void set_status(const size_t& newStatus){status = newStatus;}

    void enroll(String, const size_t&, const size_t&, const Program&);
    void enrollIn(String, const double&);
    void advance();
    void graduate();
    void interrupt();
    void resume();
    void print();
    void report();

    void addGrade(String, const double&);
    bool is_interrupted();

};
void Student::addGrade(String course, const double& mark_)
{
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(program.get_subject(indexOfTakenOnes[i])->get_name() == course)
        {
            program.get_subject(indexOfTakenOnes[i])->set_mark(mark_);
            return;
        }
    }
    std::cout << "This student doesn't belong to this course!"<< std::endl;
}
bool Student::is_interrupted()
{
    if(status == 1)return 1;
    return 0;
}
void Student::enroll(String name_, const size_t& fn_, const size_t& group, const Program& program_)
{
    name = name_;
    fn = fn_;
    groupNum = group;
    program = program_;
}
Student& Student::operator=(const Student& other)
{
    name = other.name;
    fn = other.fn;
    groupNum = other.groupNum;
    averMarks = other.averMarks;
    year = other.year;
    status = other.status;
    program = other.program;
    return (*this);
}
void Student::advance()
{
    year ++;
}
void Student::graduate()
{
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(program.get_subject(i)->get_mark() <= 3.00)
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
void Student::print()
{
    std::cout << "name:" << name << " fn:" << fn << " year:" << year << " group:" << groupNum <<" program:" << program.get_program() <<  std::endl;
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
void Student::report()
{
    std::cout << "name:" << name << " fn:" << fn << " year:" << year << " group:" << groupNum << std::endl;
    std::cout << "Exams taken:" << std::endl;
    double aver = 0.0;
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        aver += program.get_subject(indexOfTakenOnes[i])->get_mark();
        if(program.get_subject(indexOfTakenOnes[i])->get_mark() >= 3.00)
        {
            program.get_subject(indexOfTakenOnes[i])->print();
        }
    }
    std::cout << "Exams not taken:" << std::endl;
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(program.get_subject(indexOfTakenOnes[i])->get_mark() < 3.00)
        {
            program.get_subject(indexOfTakenOnes[i])->print();
        }
    }
    if(indexOfTakenOnes.size() != 0) std::cout << "Average grades:" << (double)aver/indexOfTakenOnes.size() << std::endl;
}
void Student::enrollIn(String subjName, const double& mark)
{
    std::cout <<"programName= " << program.get_program() << " "<< program.get_numSubjects() << std::endl;
    for(size_t i = 0; i < program.get_numSubjects(); i ++)
    {
        if(program.get_subject(i)->get_name() == subjName)
        {
            if(program.get_subject(i)->get_year() <= year )
            {
                    program.get_subject(i)->set_mark(mark);
                    indexOfTakenOnes.push_back(i);
            }
            else
            {
                std::cout << "This student is in lower year than allowed for this course!" << std::endl;
            }
            return;
        }
    }
    std::cout << "The subject was not found!" << std::endl;
}
Student::Student()
{
}
Student::Student(String name_, const size_t& fn_, const size_t& groupNum_, const Program& program_)
{
    name = name_;
    fn = fn_;
    groupNum = groupNum_;
    year = 1;
    status = 0;///zapisan
    program = program_;
}
#endif // _STUDENT_H_
