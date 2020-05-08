#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <iostream>
#include "String.hpp"
class Subject
{
private:
    String name;
    bool type;///zadulj izbiraema
    size_t year;
    double mark;
public:
    void set_mark(const double& mark_){mark = mark_;}
    const double get_mark()const{return mark;}
    String get_name()const{return name;}
    Subject(String, const bool&, const size_t&);
};
Subject::Subject(String name_, const bool& type_, const size_t& year_)
{
    name = name_;
    type = type_;
    year = year_;
    mark = 2.00;
}
#endif // _SUBJECT_H_
