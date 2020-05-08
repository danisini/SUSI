#include <iostream>
#include <fstream>
#include "Student.hpp"
#include "String.hpp"
using namespace std;
int main()
{
    cout << "This is the system SUSI! Do you want to open a file?" << endl;
    string s;
    cin >> s;
    ofstream iFile;
    if(s == "open")
    {
        string filePath;
        cin >> filePath;

        iFile.open(filePath, ios::out);
        ///check if opened cout a message its opened or cout not a valid path
        ///saving data to classes


        ///iFile.close();
    }
    else cout << "Not a valid command!" << endl;
    cin >> s;
    if(s == "enroll")
    {
        string program, name;
        size_t group, fn;
        cin >> fn >> program >> group;
        getline(cin, name, '\n');
        Student newStudent(name, fn, group, program);
    }
    if(s == "advance")
    {
        size_t fn, numStudents = students.get_num();
        cin >> fn;
        /*for(size_t i = 0; i < numStudents; i ++)
        {
            if(students[i].get_fn() == fn)
            {
                students[i].set_course(students[i].get_course + 1);
                break;
            }
        }*/
    }
    if(s == "change")
    {
        size_t fn;
        string option;
        cin >> fn >> option;
        if(option == "program")
        {
            string value;
            cin >> value;

        }
    }
    iFile.close();
    return 0;
}
