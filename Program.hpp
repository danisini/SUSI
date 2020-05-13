#ifndef _PROGRAM_H_
#define _PROGRAM_H_
#include <iostream>
#include "String.hpp"
#include "Subject.hpp"
class Program
{
private:
    void copyProgram(const Program&);
    void deleteProgram();
    String programName;
    Subject** subjects;
    size_t numSubjects;
public:
    const String get_program()const{return programName;}
    void set_program(const String& programName_){programName = programName_;}
    Subject* get_subject(const size_t& i)const{return subjects[i];}/// Not const because we can't set mark then in enrollIn()
    const size_t get_numSubjects()const{return numSubjects;}
    Program(String, Subject**, const size_t&);
    Program(const Program&);
    Program& operator=(const Program&);
    ~Program();

};

Program::Program(String programName_ = "", Subject** subjects_ = nullptr, const size_t& numSubjects_ = 0)
{
    programName = programName_;
    size_t i = 0;
    numSubjects = 0;
    for(size_t i = 0; i < numSubjects_; i ++)
    {
        if(subjects_[i]->get_program() == programName)
        {
            numSubjects ++;
        }
    }
    std::cout << "ProgramName = " << programName << " numSubj = " << numSubjects << std::endl;
    subjects = new Subject*[numSubjects];
    numSubjects = 0;
    for(size_t i = 0; i < numSubjects_; i ++)
    {
        subjects_[i]->print();
        if(subjects_[i]->get_program() == programName)
        {
            subjects[numSubjects] = new Subject(subjects_[i]->get_name(), subjects_[i]->get_program(), subjects_[i]->get_type(), subjects_[i]->get_year());
            numSubjects ++;
        }
    }
}

void Program::copyProgram(const Program& other)
{
    programName = other.programName;
    numSubjects = other.numSubjects;
    subjects = new Subject*[numSubjects];
    for(size_t i = 0; i < numSubjects; i ++)
    {
        subjects[i] = other.subjects[i];
    }
}
void Program::deleteProgram()
{
    for(size_t i = 0; i < numSubjects; i ++)
        if(subjects[i] != nullptr)delete subjects[i];
    if(subjects != nullptr)delete[] subjects;
}
Program::~Program()
{
    deleteProgram();
}
Program::Program(const Program& other)
{
    copyProgram(other);
}
Program& Program::operator=(const Program& other)
{
    if(this != &other)
    {
        deleteProgram();
        copyProgram(other);
    }
    return (*this);
}

#endif // _SPECIALITY_H_
