#ifndef _SPECIALITY_H_
#define _SPECIALITY_H_
#include <string>
#inlcude <iostream>
#include "Subject.hpp"
class Speciality
{
private:
    string specName;
    Subject* subjects;
    size_t numSubjects;
};
#endif // _SPECIALITY_H_
