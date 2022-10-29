#include <regex>
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <sstream>
#include <iomanip>

#include "Manager.h"
#include "LoadSclasses.h"
#include "UcTurma.h"
#include "LoadSchedule.h"
#include "ClassOcupation.h"
#include "StudentSchedule.h"
#include "RemoveStudent.h"
#include "LogMessage.h"
#include "ProcessRequests.h"
#include "DisplayStudentsInClass.h"

using namespace std;

int main()
{
    Manager m = Manager();
    loadStudentClasses(m);
    loadSchedule(m);
    vector<string> log;


    char choice;
    do {
        cout << endl << "====================================================" << endl;
        cout << "\t\t\tOptions:" << endl;
        cout << "1. Display Possibility's" << endl;
        cout << "2. Modify Database" << endl << endl;
        cout << "Select 'q' to quit!" << endl;
        cout << "====================================================" << endl;

        cout << "Select your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << endl << "====================================================" << endl;
                cout << "\t\t\tOptions:" << endl;
                cout << "1. Display ocupation of a given class" << endl;
                cout << "2. Display shechedule of a given student" << endl;
                cout << "3. Display students in a given class" << endl;
                cout << "4. Display students with more then a given number of UC's" << endl;
                cout << "Select 'b' to go back!" << endl;
                cout << "====================================================" << endl;

                cout << "Select your choice: ";
                cin >> choice;

                switch (choice) {
                    case '1': {
                        classOcupation(m);
                        break;
                    }
                    case '2': {
                        studentSchedule(m);
                        break;
                    }
                    case '3':
                        displayStudentsInClass(m);
                    case '4':
                        break;

                    case 'b':
                        break;
                    default:
                        cout << endl << "Error: character not recognised please select one of the options!" << endl;
                        break;
                }
                break;

            case '2':
                cout << endl << "====================================================" << endl;
                cout << "\t\t\tOptions:" << endl;
                cout << "1. Remove student from a UC" << endl;
                cout << "2. Add student to Class/UC" << endl;
                cout << "3. Change Class/UC of a given student" << endl;
                cout << "4. Change a set of Class/UC of a given student" << endl;
                cout << "Select 'b' to go back!" << endl;
                cout << "====================================================" << endl;

                cout << "Select your choice: ";
                cin >> choice;

                switch (choice) {
                    case '1':
                        removeStudent(m);
                        break;
                    case '2':
                        break;
                    case '3':
                        break;
                    case '4':
                        break;
                    case 'b':
                        break;
                    default:
                        cout << endl << "Error: character not recognised please select one of the options!" << endl;
                        break;
                }
                break;

            case 'q':
                cout << endl << "Exiting..." << endl;
                break;
            default:
                cout << endl << "Error: character not recognised please select one of the options!" << endl << endl;
                break;
        }

    } while (choice != 'q');
    ProcessRequests(log, m);
    return 0;
}
