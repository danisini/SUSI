#ifndef _PROGRAM_H_
#define _PROGRAM_H_
#include <iostream>
#include "vector.hpp"
#include "String.hpp"
#include "Subject.hpp"
class Program
{
private:
    String programName;
    Subject** subjects;
    size_t numSubjects;
    Vector <size_t> indexOfSubjects;
    void copyProgram(const Program&);
    void deleteProgram();
public:
    Program(String, Subject**, const size_t&);
    Program(const Program&);
    Program& operator=(const Program&);
    ~Program();
    const String get_program()const{return programName;}
    void set_program(const String& programName_){programName = programName_;}
    Subject* get_subject(const size_t& i)const{return subjects[i];}/// Not const because we can't set mark then in enrollIn()
    const size_t get_numSubjects()const{return numSubjects;}
    void changeProgram(const Program&);
};

Program::Program(String programName_ = "", Subject** subjects_ = nullptr, const size_t& numSubjects_ = 0)
{
    programName = programName_;
    size_t i = 0;
    numSubjects = 0;
    for(size_t i = 0; i < numSubjects_; i ++)
    {
        if(subjects_[i]->get_program() == programName)numSubjects ++;
    }
    subjects = new Subject*[numSubjects];
    numSubjects = numSubjects_;
    for(size_t i = 0; i < numSubjects; i ++)
    {
        if(subjects_[i]->get_program() == programName)
            indexOfSubjects.push_back(i);
        subjects[i] = new Subject(subjects_[i]->get_name(), subjects_[i]->get_program(), subjects_[i]->get_type(), subjects_[i]->get_year());
    }
}
void Program::changeProgram(const Program& other)
{
    programName = other.programName;
    for(size_t i = 0; i < other.indexOfSubjects.size(); i ++)
    {
        bool flag = 1;
        for(size_t j = 0; j < indexOfSubjects.size(); i ++)
        {
            if(other.indexOfSubjects[i] == indexOfSubjects[j])
            {
                flag = 0;
                break;
            }
        }
        if(flag)indexOfSubjects.push_back(other.indexOfSubjects[i]);
        else break;
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
    indexOfSubjects.clear();
    for(size_t i = 0; i < other.indexOfSubjects.size(); i ++)
    {
        indexOfSubjects.push_back(other.indexOfSubjects[i]);
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
    deleteProgram();
    copyProgram(other);
}
Program& Program::operator=(const Program& other)
{
    if(this != &other)
    {
        copyProgram(other);
    }
    return (*this);
}

#endif // _SPECIALITY_H_
