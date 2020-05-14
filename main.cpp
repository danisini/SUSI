#include <iostream>
#include <fstream>
#include "Student.hpp"
#include "String.hpp"
#include "susi.hpp"
using namespace std;
int main()
{
    Susi system;
    /*cout << "This is the system SUSI! Do you want to open a file?" << endl;
    String s;
    ifstream iFile;
    string filePath;
    cin >> s;
    Susi::systemSusi.menu();
    Student** students;
    Subject** subjects;
    Program** programs;
    int cnt = 0;
    size_t numPrograms = 0;
    size_t numSubjects = 0;
    if(s == "open")
    {
        iFile.open("students.txt", ios::in);
        if(!iFile.is_open())
        {
            cout << "Couldn't open the file or not a valid path!" << endl;
        }
        else
        {
            cout << "File students opened successfully" << endl;
            iFile >> cnt;
            if(cnt != 0)students = new Student*[cnt];
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
            cout << "File subjects opened successfully" << endl;
            size_t year;
            String name, program;
            bool type;
            subjects = new Subject*[7];
            for(size_t i = 0; i < 7; i ++)
            {
                getline(iFile, name);
                iFile >> type >> year;
                iFile.get();
                getline(iFile, program);
                subjects[i] = new Subject(name, program, type, year);
                numSubjects ++;
                subjects[i]->print();
            }
            for(size_t i = 0; i < 7; i ++)
            {
                bool flag = 1;
                for(size_t j = 0; j < i; j ++)
                {

                    if(subjects[j]->get_program() == subjects[i]->get_program())
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag == 1)
                {
                    numPrograms ++;
                }
            }
            programs = new Program*[numPrograms];
            numPrograms = 0;
            for(size_t i = 0; i < 7; i ++)
            {
                bool flag = 1;
                for(size_t j = 0; j < i; j ++)
                {
                    if(subjects[j]->get_program() == subjects[i]->get_program())
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag == 1)
                {
                    programs[numPrograms] = new Program(subjects[i]->get_program(), subjects, numSubjects);
                    numPrograms ++;
                }
            }
        }
    }
    while(!(s == "exit"))
    {
        cin >> s;
        cout << "You entered:" << s << endl;
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
                    oFile << students[i]->get_name().size() << " " << students[i]->get_name() << " " << students[i]->get_fn() << " " << students[i]->get_groupNum() << " " << students[i]->get_status() <<
                    " " << students[i]->get_programName().size() << " " << students[i]->get_programName() << endl;
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
            Program temp;
            int indx;
            for(size_t i = 0; i < numPrograms; i ++)
            {
                if(programs[i]->get_program() == program)
                    indx = i;
            }
            students[cnt] = new Student(name, fn, group, *programs[indx]);
            for(int i = 0; i < programs[indx]->get_numSubjects(); i ++)cout << programs[indx]->get_subject(i)->get_name()<<endl;
            cnt ++;
            students[cnt - 1]->print();
        }
        else
        if(s == "advance")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->advance();
                    break;
                }
            }
        }
        else
        if(s == "change")
        {
            size_t fn, numStudents = cnt, indx ;
            String option;
            cin >> fn;
            cin.get();
            getline(cin, option);
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    indx = i;
                    break;
                }
            }
            if(option == "program")
            {
                String value;
                getline(cin, value);
                cout << "test1 " << value << endl;;
                if(!students[indx]->is_interrupted() && students[indx]->canChangeProgram())
                {
                    cout << "test2 " << endl;
                    int ind = -1;
                    for(size_t i = 0; i < numPrograms; i ++)
                    {
                        if(value == programs[i]->get_program())
                        {
                            ind = i;
                            break;
                        }
                    }
                    cout <<"test3 "<< ind << endl;
                    if(ind != -1)
                    {
                        cout << programs[ind]->get_program() << " " << programs[ind]->get_numSubjects() << endl;
                        students[indx]->set_program(*programs[ind]);
                    }
                    else cout << "Program not found!" << endl;

                }
                else
                {
                    cout << "The student is not allowed to change program!" << endl;
                }
            }
            else if(option == "group")
            {
                size_t group;
                cin >> group;
                if(!students[indx]->is_interrupted())
                {
                    students[indx]->set_group(group);
                }
                else
                {
                    cout << "The students is not allowed to change groups!" << endl;
                }
            }
            else if(option == "year")
            {
                size_t year;
                cin >> year;
                if(!students[indx]->is_interrupted() && students[indx]->canChangeYear(year))
                {
                    students[indx]->set_year(year);
                }
            }
            else cout << "Not a valid option for changing" << endl;
        }
        else
        if(s == "graduate")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->graduate();
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
                if(students[i]->get_fn() == fn)
                {
                    students[i]->interrupt();
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
                if(students[i]->get_fn() == fn)
                {
                    students[i]->resume();
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
                if(students[i]->get_fn() == fn)
                {
                    students[i]->print();
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
                if(s1 == students[i]->get_programName() && year == students[i]->get_year())
                        students[i]->print();
            }
        }
        else
        if(s == "report")
        {
            size_t fn, numStudents = cnt;///using static ones
            cin >> fn;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->report();
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
                if(students[i]->get_fn() == fn)
                {
                    students[i]->print();
                    std::cout << course << std::endl;
                    students[i]->enrollIn(course, 2.00);///not needed 2.00
                    break;
                }
            }
        }
        else
        if(s == "addgrade")
        {
            size_t fn, numStudents = cnt;
            String course;
            double mark;
            cin >> fn;
            cin.get();
            getline(cin, course);
            cin >> mark;
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->addGrade(course, mark);///not needed 2.00
                    break;
                }
            }
        }
    }
    */
    return 0;
}
