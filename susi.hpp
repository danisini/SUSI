#ifndef _SUSI_H_
#define _SUSI_H_
#include "Student.hpp"
#include "Subject.hpp"
#include "String.hpp"
#include "Program.hpp"

class Susi
{
private:
    Student** students;
    Subject** subjects;
    Program** programs;
    size_t numPrograms;
    size_t numSubjects;
    size_t numStudents;
    String filePathSubj;
    String filePathStud;

    void deleteStudent();
    void open(String);
    void save();
    void help();
    void saveAs(String);
    void deleteSusi();
    size_t countSpaces(String);
    void protocol(String, const Program&);
    void sortForProtocol();
public:
    Susi();
    ~Susi();
    Susi(const Susi&) = delete;
    Susi& operator=(const Susi&) = delete;

};
void Susi::sortForProtocol()
{
    for(size_t i = 0; i < numStudents; i ++)
    {
        for(size_t j = i + 1; j < numStudents; j ++)
        {
            if(students[i]->get_year() > students[j]->get_year() || (students[i]->get_year() == students[j]->get_year() && students[i]->get_fn() > students[j]->get_fn()))
            {
                Student* temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}
void Susi::protocol(String course, const Program& program)
{
    std::cout << "For program with name: " << program.get_program();
    size_t y = 0, cnt = 1;
    for(size_t i = 0; i < numStudents; i ++)
    {
        if(students[i]->get_programName() == program.get_program() && students[i]->hasSubject(course))
        {
            if(students[i]->get_year() > y)
            {
                std::cout << " and year: " << ++ y << ":" << std::endl;
                cnt = 1;
            }
            std::cout << cnt ++ << ") ";
            students[i]->printForProtocol(course);

        }
    }
    if(y == 0) std::cout << " there aren't any students." << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
}
void Susi::deleteSusi()
{
    for(size_t i = 0; i < numSubjects; i ++)
        delete subjects[i];
    if(subjects != nullptr)delete[] subjects;

    for(size_t i = 0; i < numPrograms; i ++)
        delete programs[i];
    if(programs != nullptr)delete[] programs;

    for(size_t i = 0; i < numStudents; i ++)
        delete students[i];
    if(students != nullptr)delete[] students;

}
Susi::~Susi()
{
    deleteSusi();
}
void Susi::help()
{
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "open <filePath>    |" << "opens a file with path <filePath>" << std::endl;
    std::cout << "close              |" << "closes currently opened files" << std::endl;
    std::cout << "help               |" << "prints this information" << std::endl;
    std::cout << "save               |" << "saves currently opened files" << std::endl;
    std::cout << "save as <filePath> |" << "saves currently opened files at path <filePath>" << std::endl;
    std::cout << "exit               |" << "exits the program" << std::endl;
    std::cout << "enroll <fn>        |" << "enrolls student with faculty number <fn>," << std::endl;
    std::cout << "<program>          |" << "program name <program>," << std::endl;
    std::cout << "<group>            |" << "group name <group> and" << std::endl;
    std::cout << "<name>             |" << "name <name> as a first year student" << std::endl;
    std::cout << "advance <fn>       |" << "enrolls student with faculty number <fn> in the next year" << std::endl;
    std::cout << "change <fn>        |" << "for student with faculty number <fn> changes" << std::endl;
    std::cout << "<option>           |" << "either program, or group, or year described in <option>" << std::endl;
    std::cout << "<value>            |" << "with value <value> if possible" << std::endl;
    std::cout << "graduate <fn>      |" << "student with faculty number <fn> graduates if possible" << std::endl;
    std::cout << "interrupt <fn>     |" << "student with faculty number <fn> interrupts" << std::endl;
    std::cout << "resume <fn>        |" << "student with faculty number <fn> is no longer with no rights"  << std::endl;
    std::cout << "print <fn>         |" << "prints info about student with faculty number <fn>" << std::endl;
    std::cout << "printall           |" << "prints info about all the students" << std::endl;
    std::cout << "<program>          |" << "in program <program>" << std::endl;
    std::cout << "<year>             |" << "and year <year>" << std::endl;
    std::cout << "enrollin <fn>      |" << "enrolls in student with faculty number <fn>" << std::endl;
    std::cout << "<course>           |" << "in course with name <course>" << std::endl;
    std::cout << "addgrade <fn>      |" << "adds grade <grade>" << std::endl;
    std::cout << "<course>           |" << "for student with faculty number <fn>" << std::endl;
    std::cout << "<grade>            |" << "in course with name <course>" << std::endl;
    std::cout << "protocol <course>  |" << "prints a protocol for course with name <course>" << std::endl;
    std::cout << "report <fn>        |" << "prints info about the grades of a student with faculty number <fn>" << std::endl;
}
void Susi::open(String input)
{
    std::ifstream iFile;
    String filePath = "";
    for(size_t i = 5; i < input.size(); i ++)
    {
        filePath = filePath + input[i];
    }
    iFile.open(filePath.stringToChar(), std::ios::in);
    if(!iFile.is_open())
    {
        std::cout << "Couldn't open the file or not a valid path!" << std::endl;
        return;
    }
    std::cout << "File opened successfully" << std::endl;
    String fileType;
    iFile >> fileType;
    if(fileType == "students")
    {
        numStudents = 0;
        filePathStud = filePath;
        iFile >> numStudents;
        if(numStudents != 0)students = new Student*[numStudents];
        String name, program, subjName;
        double mark;
        size_t fn, status, groupNum, numSubjTaken, year;
        int indx;
        for(size_t i = 0; i < numStudents; i ++)
        {
            iFile.get();
            indx = -1;
            getline(iFile, name);
            iFile >> fn >> year >> groupNum >> status;
            iFile.get();
            getline(iFile, program);
            for(size_t j = 0; j < numPrograms; j ++)
            {
                if(programs[j]->get_program() == program)
                {
                    indx = j;
                    break;
                }
            }
            iFile >> numSubjTaken;
            if(indx != -1)
            {
                students[i] = new Student(name, fn, year, groupNum, status, *programs[indx]);
                for(size_t j = 0; j < numSubjTaken; j ++)
                {
                    iFile.get();
                    getline(iFile,subjName);
                    iFile >> mark;
                    students[i]->addSubj(subjName, mark);
                }

            }
            else std::cout << "This students is not in a valid program" << std::endl;
        }
        ///saving data to classes
    }
    else if(fileType == "subjects")
    {
        filePathSubj = filePath;
        numSubjects = 0;
        iFile >> numSubjects;
        size_t year;
        String name, program;
        bool type;
        subjects = new Subject*[numSubjects];
        iFile.get();
        for(size_t i = 0; i < numSubjects; i ++)
        {
            getline(iFile, name);
            iFile >> type >> year;
            iFile.get();
            getline(iFile, program);
            subjects[i] = new Subject(name, program, type, year);
        }
        for(size_t i = 0; i < numSubjects; i ++)
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
        for(size_t i = 0; i < numSubjects; i ++)
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
    else
    {
        std::cout << "This file is not for students or subjects so it is not allowed to be opened" << std::endl;
    }
    iFile.close();
}
size_t Susi::countSpaces(String str)
{
    size_t cnt = 0;
    for(size_t i = 0; i < str.size() - 1; i ++)
    {
        if(str[i] == ' ')cnt ++;
    }
    return cnt;
}
void Susi::save()
{
    std::ofstream oFile;
    oFile.open(filePathStud.stringToChar(), std::ios::out);
    if(!oFile.is_open())
    {
        std::cout << "We are sorry! Couldn't save file with path " << filePathStud <<  " properly!" << std::endl;
        return;
    }
    else
    {
        oFile << "students" << '\n' << numStudents << '\n';
        for(size_t i = 0; i < numStudents; i ++)
        {
            oFile << students[i]->get_name() << '\n' << students[i]->get_fn() << " " << students[i]->get_year() << " " << students[i]->get_groupNum()
            << " " << students[i]->get_status() << '\n' << students[i]->get_programName() << std::endl;
            students[i]->saveSubjects(oFile);
        }
        oFile.close();
    }
    oFile.open(filePathSubj.stringToChar(), std::ios::out);
    if(!oFile.is_open())
    {
        std::cout << "We are sorry! Couldn't save file with path " << filePathSubj <<  " properly!" << std::endl;
        return;
    }
    else
    {
        oFile << "subjects" << '\n' << numSubjects << '\n';
        for(size_t i = 0; i < numSubjects; i ++)
        {
            oFile << subjects[i]->get_name() << '\n' << subjects[i]->get_type() << " " << subjects[i]->get_year() << '\n' << subjects[i]->get_program() << '\n';
        }
        oFile.close();
    }
}
void Susi::saveAs(String input)
{
    String filePath = "";
    for(size_t i = 8; i < input.size(); i ++)
    {
        filePath += input[i];
    }
    filePathSubj = filePath + "\subjects.txt";
    filePathStud = filePath + "\students.txt";
    save();
}
void Susi::deleteStudent()
{
    for(size_t i = 0; i < numStudents; i ++)
    {
        delete students[i];
    }
}
Susi::Susi()
{
    numStudents = numSubjects = numPrograms = 0;
    String command = "", input;
    while(!(command == "exit"))
    {
        command = "";
        getline(std::cin, input);
        size_t cntSpaces = countSpaces(input);
        for(size_t i = 0; i < input.size(); i ++)
        {
            if(input[i] == ' ')break;
            command = command + input[i];
        }
        std::cout << command << std::endl;
        if(command == "open")
        {
            open(input);
        }
        else if(command == "save")
        {
            if(cntSpaces == 2)saveAs(input);
            else save();
        }
        else if(command == "close")
        {
            deleteSusi();
        }
        else if(command == "help")
        {
            help();
        }
        else if(command == "enroll")
        {
            size_t group, fn;
            String program, name;
            std::cin >> fn;
            std::cin.get();
            getline(std::cin, program);
            std::cin >> group;
            std::cin.get();
            getline(std::cin, name);
            Program temp;
            int indx = -1;
            for(size_t i = 0; i < numPrograms; i ++)
            {
                if(programs[i]->get_program() == program)
                    indx = i;
            }
            Student** tempor = new Student*[numStudents + 1];
            for(size_t i = 0; i < numStudents; i ++)
            {
                tempor[i] = new Student(*students[i]);
            }

            if(indx != -1) tempor[numStudents] = new Student(name, fn, 1, group, 0, *programs[indx]);
            else std::cout << "This student belongs to no program" << std::endl;
            deleteStudent();
            students = tempor;
            for(int i = 0; i < programs[indx]->get_numSubjects(); i ++)std::cout <<"test15 " <<  programs[indx]->get_subject(i)->get_name()<<std::endl;
            numStudents ++;
            students[numStudents - 1]->print();
        }
        else if(command == "advance")
        {
            size_t fn;
            std::cin >> fn;
            std::cin.get();
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->advance();
                    break;
                }
            }
        }
        else if(command == "change")
        {
            size_t fn, indx;
            String option;
            std::cin >> fn;
            std::cin.get();
            getline(std::cin, option);
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
                getline(std::cin, value);
                if(!students[indx]->is_interrupted() && students[indx]->canChangeProgram())
                {
                    int ind = -1;
                    for(size_t i = 0; i < numPrograms; i ++)
                    {
                        if(value == programs[i]->get_program())
                        {
                            ind = i;
                            break;
                        }
                    }
                    if(ind != -1)
                    {
                        std::cout << programs[ind]->get_program() << " " << programs[ind]->get_numSubjects() << std::endl;
                        students[indx]->set_program(*programs[ind]);
                    }
                    else std::cout << "Program not found!" << std::endl;

                }
                else
                {
                    std::cout << "The student is not allowed to change program!" << std::endl;
                }
            }
            else if(option == "group")
            {
                size_t group;
                std::cin >> group;
                std::cin.get();
                if(!students[indx]->is_interrupted())
                {
                    students[indx]->set_group(group);
                }
                else
                {
                    std::cout << "The students is not allowed to change groups!" << std::endl;
                }
            }
            else if(option == "year")
            {
                size_t year;
                std::cin >> year;
                std::cin.get();
                if(!students[indx]->is_interrupted() && students[indx]->canChangeYear(year))
                {
                    students[indx]->set_year(year);
                }
            }
            else std::cout << "Not a valid option for changing" << std::endl;
        }
        else if(command == "graduate")
        {
            size_t fn;
            std::cin >> fn;
            std::cin.get();
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->graduate();
                    break;
                }
            }
        }
        else if(command == "interrupt")
        {
            size_t fn;
            std::cin >> fn;
            std::cin.get();
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->interrupt();
                    break;
                }
            }
        }
        else if(command == "resume")
        {
            size_t fn;
            std::cin >> fn;
            std::cin.get();
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->resume();
                    break;
                }
            }
        }
        else if(command == "print")
        {
            size_t fn;
            std::cin >> fn;
            std::cin.get();
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->print();
                    break;
                }
            }
        }
        else if(command == "printall")
        {
            String s1;
            size_t year;
            getline(std::cin, s1);
            std::cin >> year;
            std::cin.get();
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(s1 == students[i]->get_programName() && year == students[i]->get_year())
                        students[i]->print();
            }
        }
        else if(command == "enrollin")
        {
            size_t fn;
            String course;
            std::cin >> fn;
            std::cin.get();
            getline(std::cin, course);
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    if(students[i]->is_interrupted() == 0)
                    {
                        students[i]->print();
                        std::cout << course << std::endl;
                        students[i]->enrollIn(course, 2.00);///not needed 2.00
                        break;
                    }
                    else std::cout << "This student has no rights!" << std::endl;
                }
            }
        }
        else if(command == "addgrade")
        {
            size_t fn;
            String course;
            double mark;
            std::cin >> fn;
            std::cin.get();
            getline(std::cin, course);
            std::cin >> mark;
            std::cin.get();
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    if(students[i]->is_interrupted() == 0)
                    {
                        students[i]->addGrade(course, mark);///not needed 2.00
                        break;
                    }
                    else std::cout << "This student has no rights!" << std::endl;
                }
            }
        }
        else if(command == "protocol")
        {
            String course;
            getline(std::cin, course);
            sortForProtocol();
            for(size_t i = 0; i < numPrograms; i ++)
            {
                std::cout << i << " " << programs[i]->get_program() << std::endl;
                protocol(course, *programs[i]);
            }
        }
        else if(command == "report")
        {
            size_t fn;
            std::cin >> fn;
            std::cin.get();
            for(size_t i = 0; i < numStudents; i ++)
            {
                if(students[i]->get_fn() == fn)
                {
                    students[i]->report();
                    break;
                }
            }
        }
    }
}
#endif // _SUSI_H_
