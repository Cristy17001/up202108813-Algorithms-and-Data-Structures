#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

#include "Manager.h"
#include "LogMessage.h"
#include "ProcessRequests.h"
#include "ClearScreen.h"

int main() {
    Manager m = Manager();
    m.loadUcs();
    m.loadSchedule();
    m.loadStudentClasses();
    vector<string> log;
    ofstream log_output;
    log_output.open("Output_Files/Log_Output.log", ios::app);

    string input_aux;
    char choice;

    do {
        cout << endl << "=========================================================" << endl;
        cout << "\t\t\tOptions:" << endl;
        cout << "1. Display Possibility's" << endl;
        cout << "2. Modify Database" << endl << endl;
        cout << "Select 'q' to quit!" << endl;
        cout << "Select 'c' to clear!" << endl;
        cout << "=========================================================" << endl;

        cout << "Select your choice: ";
        cin >> input_aux;
        cout << endl;
        if (input_aux.length() > 1) {cout << "Error Invalid Input! Please Introduce only one character!" << endl; choice = '0';}
        else choice = input_aux[0];

        switch (choice) {
            case '1':
                cout << endl << "=========================================================" << endl;
                cout << "\t\t\tOptions:" << endl;
                cout << "1. Display number of students of a given class" << endl;
                cout << "2. Display students in a given class" << endl;
                cout << "3. Display schedule of a given student" << endl;
                cout << "4. Display students with more then a given number of UC's" << endl << endl;
                cout << "Select 'b' to go back!" << endl;
                cout << "=========================================================" << endl;

                cout << "Select your choice: ";
                cin >> input_aux;
                cout << endl;
                if (input_aux.length() > 1) {cout << "Error Invalid Input! Please Introduce only one character!" << endl; choice = '0';}
                else choice = input_aux[0];

                switch (choice) {
                    case '1': {m.classOcupation(); break;}

                    case '2': {m.displayStudentsInClassUcYear(); break;}

                    case '3': {m.studentSchedule(); break;}

                    case '4': {m.studentsInUcs(); break;}

                    case 'b': break;

                    default:
                        if (input_aux.length() == 1) {
                            cout << endl << "Error: character not recognised please select one of the options!" << endl << endl;
                        }
                        choice = '0';
                        break;
                }
                break;

            case '2':
                cout << endl << "=========================================================" << endl;
                cout << "\t\t\tOptions:" << endl;
                cout << "1. Remove student from a UC" << endl;
                cout << "2. Add student to Class/UC" << endl;
                cout << "3. Change Class/UC of a given student" << endl;
                cout << "4. Change a set of Class/UC of a given student" << endl << endl;
                cout << "Select 'b' to go back!" << endl;
                cout << "=========================================================" << endl;

                cout << "Select your choice: ";
                cin >> input_aux;
                cout << endl;
                if (input_aux.length() > 1) {cout << "Error Invalid Input! Please Introduce only one character!" << endl; choice = '0';}
                else choice = input_aux[0];

                switch (choice) {
                    case '1': {m.removeStudent(); break;}

                    case '2': {m.addStudent(); break;}

                    case '3': {m.alterStudent(); break;}

                    case '4': {m.alterSetStudents(); break;}

                    case 'b': break;

                    default: {
                        if (input_aux.length() == 1) {
                            cout << endl << "Error: character not recognised please select one of the options!" << endl
                                 << endl;
                        }
                        choice = '0';
                        break;
                    }
                }
                break;

            case 'c': {ClearScreen(); break;}

            case 'q': {cout << endl << "Exiting..." << endl; break;}

            default: {
                if (input_aux.length() == 1) {
                    cout << endl << "Error: character not recognised please select one of the options!" << endl << endl;
                }
                choice = '0'; break;
            }
        }

    } while (choice != 'q');

    ProcessRequests(log, m);
    if (!log.empty()) {
        //Write to logFile the Error's
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);

        log_output << "#Software: Gestor Base Dados Algoritmos e Estruturas de Dados\n"
                      "#Version: 1.0\n"
                      "#DateTime: " << put_time(ltm, "%d/%m/%Y : %H:%M:%S\n") <<
                      "#Fields: Day Time Error_message"
                      << endl << endl;

        for (const string &line: log) { log_output << line << endl; }
        log_output << endl;
        log_output.close();
    }
    if (!m.get_students().empty()) {
        ofstream students_classesMod;
        students_classesMod.open("Output_Files/students_classesMod.csv");
        students_classesMod << "StudentCode,StudentName,UcCode,ClassCode" << endl;

        for (const Student& s: m.get_students()) {
            for (const UcTurma& t: s.get_turm()) {
                students_classesMod << s.get_mecaNumber() << ',' << s.get_name() << ',' << t.get_ucCode() << ',' << t.get_classCode() << endl;
            }

        }
        students_classesMod.close();
    }

    return 0;
}
