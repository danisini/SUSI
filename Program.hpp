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
protected:
    String programName;
    Subject* subjects;
    static size_t numSubjects;
public:
    String get_program(){return programName;}
    void set_program(const String& programName_){programName = programName_;}

    Program(String);
    Program(const Program&);
    Program& operator=(const Program&);
    ~Program();

};
size_t Program::numSubjects = 7;
void Program::copyProgram(const Program& other)
{
    programName = other.programName;
    numSubjects = other.numSubjects;
    subjects = other.subjects;
}
void Program::deleteProgram()
{
    if(subjects != nullptr)delete[] subjects;
}
Program::Program(String programName_ = "")
{
    programName = programName_;
    numSubjects = 0;
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
