#include <iostream>
#include <fstream>
#include "Student.hpp"
#include "String.hpp"
using namespace std;
int main()
{
    cout << "This is the system SUSI! Do you want to open a file?" << endl;
    String s;
    ifstream iFile;
    string filePath;
    cin >> s;
    Student* students;
    Subject subjects[7];
    int cnt = 0;
    if(s == "open")
    {
        iFile.open("students.txt", ios::in);
        if(!iFile.is_open())
        {
            cout << "Couldn't open the file or not a valid path!" << endl;
        }
        else
        {
            iFile >> cnt;
            students = new Student[cnt];
        }

        ///saving data to classes
        iFile.close();


        iFile.open("subjects.txt", ios::in);
        if(!iFile.is_open())
        {
            cout << "Couldn't open the file or not a valid path!" << endl;
        }
        else
        {
            size_t year;
            String name;
            bool type;
            for(size_t i = 0; i < 7; i ++)
            {
                getline(iFile, name);
                iFile >> type >> year;
                iFile.get();
                subjects[i].construct(name, type, year);
            }
        }
    }
    while(!(s == "exit"))
    {
        cin >> s;
        cout << s << endl;
        if(s == "save")
        {
            ofstream oFile;
            oFile.open("students.txt", ios::out);
            if(!oFile.is_open())
            {
                cout << "Couldn't open the file or not a valid path!" << endl;
            }
            else
            {
                for(size_t i = 0; i < cnt; i ++)
                {
                    oFile << students[i].get_name().size() << " " << students[i].get_name() << " " << students[i].get_fn() << " " << students[i].get_groupNum() << " " << students[i].get_status() <<
                    " " << students[i].get_program().size() << " " << students[i].get_program() << endl;
                }
            }
        }
        else
        if(s == "enroll")
        {
            size_t group, fn;
            String program, name;
            cin >> fn;
            cin.get();
            getline(cin, program);
            cin >> group;
            cin.get();
            getline(cin, name);
            Student* temp = new Student[cnt + 1];
            for(size_t i = 0; i < cnt; i++)
                temp[i] = students[i];
            temp[cnt].enroll(name, fn, group, program);
            cnt ++;
            if(students != nullptr)delete[] students;
            students = temp;
            students[cnt - 1].print();
        }
        else
        if(s == "advance")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i].get_fn() == fn)
                {
                    students[i].advance();
                    break;
                }
            }
        }
        else
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
        else
        if(s == "graduate")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i].get_fn() == fn)
                {
                    students[i].graduate();
                    break;
                }
            }
        }
        else
        if(s == "interrupt")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i].get_fn() == fn)
                {
                    students[i].interrupt();
                    break;
                }
            }
        }
        else
        if(s == "resume")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i].get_fn() == fn)
                {
                    students[i].resume();
                    break;
                }
            }
        }
        else
        if(s == "print")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i].get_fn() == fn)
                {
                    students[i].print();
                    break;
                }
            }
        }
        else
        if(s == "printall")
        {
            String s1;
            size_t year, numStudents = cnt;///using static ones
            getline(cin, s1);
            cin >> year;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(s1 == students[i].get_program() && year == students[i].get_year())
                        students[i].print();
            }
        }
        else
        if(s == "report")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i].get_fn() == fn)
                {
                    students[i].report();
                    break;
                }
            }
        }
        else
        if(s == "enrollin")
        {
            size_t fn, numStudents = cnt;
            String course;
            cin >> fn;
            cin.get();
            getline(cin, course);
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i].get_fn() == fn)
                {
                    students[i].print();
                    students[i].enrollIn(course, 2.00);///not needed 2.00
                    break;
                }
            }
        }
    }
    return 0;
}
