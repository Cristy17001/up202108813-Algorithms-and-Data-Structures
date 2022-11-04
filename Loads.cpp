#include "Manager.h"

using namespace std;

void Manager::loadUcs() {
    string ucCode, classCode, file_text;

    ifstream file;
    file.open("classes_per_uc.csv");

    //Eliminate first line
    getline(file, file_text);

    while(!file.eof()) {

        getline(file, ucCode, ',');
        getline(file, classCode);

        if (!classCode.empty()) {
            UcTurma aux = UcTurma(ucCode, classCode);
            all_ucs_.push_back(aux);
        }
    }
    file.close();
}
void Manager::loadSchedule() {

    ifstream file;
    string file_text, classCode, ucCode, weekDay, type;
    double startHour, duration;
    file.open("classes.csv");

    vector<ClassSchedule> v;

    //Eliminate first line
    getline(file, file_text);

    while(!file.eof()) {

        getline(file, classCode, ',');
        getline(file, ucCode, ',');
        getline(file, weekDay, ',');

        getline(file, file_text, ',');
        startHour = atof(file_text.c_str());

        getline(file, file_text, ',');
        duration = atof(file_text.c_str());

        getline(file, type);

        if (!classCode.empty()) {
            UcTurma u = UcTurma(ucCode, classCode);
            ClassSchedule c = ClassSchedule(u, weekDay, startHour, duration, type);
            v.push_back(c);
        }

    }
    schedule_ = v;
    file.close();
}
void Manager::loadStudentClasses() {

    ifstream file;
    string file_text;
    file.open("students_classes.csv");

    string mecaNumber_ant;
    string studentName_ant;
    string mecaNumber, studentName, ucCode, classCode;

    list<UcTurma> l;

    //Eliminate first line
    getline(file, file_text);
    bool flag = false;

    while(!file.eof()) {

        getline(file, mecaNumber, ',');
        getline(file, studentName, ',');
        getline(file, ucCode, ',');
        getline(file, classCode);

        if (mecaNumber != mecaNumber_ant and flag) {
            Student s = Student(mecaNumber_ant, studentName_ant, l);
            students_.insert(s);
            l.clear();
            UcTurma u = UcTurma(ucCode, classCode);
            l.push_back(u);
        }
        else
        {
            UcTurma u = UcTurma(ucCode, classCode);
            l.push_back(u);
        }

        studentName_ant = studentName;
        mecaNumber_ant = mecaNumber;
        flag = true;
    }
    file.close();
}
