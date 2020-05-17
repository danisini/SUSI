#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include "String.hpp"
#include "Program.hpp"
#include <vector>
#include <fstream>
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
    Student(String, const size_t&, const size_t&, const size_t&, const size_t&, const Program&);
    Student& operator=(const Student&);
    const size_t get_groupNum()const{return groupNum;}
    const size_t get_year()const{return year;}
    const size_t get_status()const{return status;}
    const double get_averMarks()const{return averMarks;}
    const size_t get_fn()const{return fn;}
    const String get_name()const{return name;}
    const String get_programName()const{return program.get_program();}

    void set_program(const Program& program_){program.changeProgram(program_);}
    void set_group(const size_t& groupNum_){groupNum = groupNum_;}
    void set_year(const size_t& year_){year = year_;}

    bool canChangeProgram();
    bool canChangeYear(const size_t&);

    void enroll(String, const size_t&, const size_t&, const Program&);
    void enrollIn(String, const double&);
    void advance();
    void graduate();
    void interrupt();
    void resume();
    void print();
    void report();
    void addGrade(String, const double&);

    void printForProtocol(String course);
    bool is_interrupted();
    void saveSubjects(std::ofstream&);
    void addSubj(String, const double&);
    bool hasSubject(String);
};
bool Student::hasSubject(String course)
{
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(program.get_subject(indexOfTakenOnes[i])->get_name() == course)return 1;
    }
    return 0;
}
void Student::saveSubjects(std::ofstream& oFile)
{
    oFile << indexOfTakenOnes.size() << std::endl;
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        oFile << program.get_subject(indexOfTakenOnes[i])->get_name() << '\n' << program.get_subject(indexOfTakenOnes[i])->get_mark() << std::endl;
    }
}
bool Student::canChangeProgram()
{
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(program.get_subject(indexOfTakenOnes[i])->get_mark() < 3.00 && program.get_subject(indexOfTakenOnes[i])->get_type() == 0)return 0;
    }
    return 1;
}
bool Student::canChangeYear(const size_t& year_)
{
    size_t cnt = 0;
    if(year + 1 != year_)return 0;
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(program.get_subject(indexOfTakenOnes[i])->get_mark() < 3.00 && program.get_subject(indexOfTakenOnes[i])->get_type() == 0)cnt ++;
        if(cnt > 2)return 0;
    }
    return 1;
}
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
    std::cout << "name: " << name << ", fn: " << fn << ", year: " << year << ", group: " << groupNum <<", program: " << program.get_program() <<  std::endl;
}
void Student::printForProtocol(String course)
{
    std::cout << "name: " << name << ", fn: " << fn << ", year: " << year << ", group: " << groupNum << ", mark: ";
    for(size_t i = 0; i < indexOfTakenOnes.size(); i ++)
    {
        if(program.get_subject(indexOfTakenOnes[i])->get_name() == course)
        {
            std::cout << program.get_subject(indexOfTakenOnes[i])->get_mark() << std::endl;
        }
    }
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
void Student::addSubj(String subjName, const double& mark)
{
    for(size_t i = 0; i < program.get_numSubjects(); i ++)
    {
        if(program.get_subject(i)->get_name() == subjName)
        {
            program.get_subject(i)->set_mark(mark);
            indexOfTakenOnes.push_back(i);
            return;
        }
    }
    std::cout << "The subject " << subjName << " was not found!" << std::endl;
}
void Student::enrollIn(String subjName, const double& mark)
{
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
Student::Student(String name_, const size_t& fn_, const size_t& year_, const size_t& groupNum_, const size_t& status_, const Program& program_)
{
    name = name_;
    fn = fn_;
    groupNum = groupNum_;
    year = year_;
    status = status_;///0 - zapisan
    program = program_;
}
#endif // _STUDENT_H_
