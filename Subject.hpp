#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <iostream>
#include "String.hpp"
class Subject
{
private:
    String name, program;
    bool type;///zadulj izbiraema
    size_t year;
    double mark;

public:
    void set_mark(const double& mark_){mark = mark_;}
    const double get_mark()const{return mark;}
    const size_t get_year()const{return year;}
    const String get_program()const{return program;}
    const String get_name()const{return name;}
    const bool get_type()const{return type;}
    Subject(String, String, const bool&, const size_t&);
    void construct(String, String, const bool&, const size_t&);
    void print()const;
    Subject& operator=(const Subject&);
    bool operator==(const Subject&);
};
void Subject::print()const
{
    if(!type)std::cout << "name:" << name << " (Not mandatory) mark:" << mark << std::endl;
    else std::cout << "name:" << name << " (Mandatory) mark:" << mark << std::endl;
}
void Subject::construct(String name_, String program_, const bool& type_, const size_t& year_)
{
    name = name_;
    program = program_;
    type = type_;
    year = year_;

}
Subject::Subject(String name_ = "", String program_= "", const bool& type_ = 1, const size_t& year_ = 1)
{
    name = name_;
    program = program_;
    type = type_;
    year = year_;
    mark = 2.00;
}
bool Subject::operator==(const Subject& other)
{
    if(other.name == name)
    {
        ///v documentaciqta da se napishe che se priema samo tova za zadulj
        return 1;
    }
    return 0;
}
#endif // _SUBJECT_H_
