#include "UcTurma.h"

void displayStudentsInClass(const Manager& m) {

    string uc, year, cn;
    cout << "Example: 1, 2, 3, 4, (...), 15 ..." << endl;
    cout << "Introduce a class number: ";
    cin >> cn; cout << endl;

    cout << "Example: 1, 2, 3 (...)" << endl;
    cout << "Introduce year: ";
    cin >> year; cout << endl;

    int count = 0;
    bool error = false;

    //Constrains
    if (!(regex_search(cn, regex("[0-9]{1,2}")))) {cout << "INVALID CLASS NUMBER!" << endl; error = true;}
    if (!(regex_search(year, regex("[1-6]{1}")))) {cout << "INVALID YEAR" << endl; error = true;}
    if (error) return;

    for (const Student& s: m.get_students()) {

        for (auto t: s.get_turm()) {
            if ( t.get_year() == year[0] ) {

                string classCode = t.get_classCode();
                int class_num = std::stoi(&classCode[5]);

                if (class_num == std::stoi( cn )) {
                    count++;
                    cout << "Student: " << s.get_mecaNumber() << " - " << s.get_name() << endl;
                    break;
                }
            }
        }
    }

    if (count == 0) {
        cout << "Couldn't find any student for class " << cn << " " << year << endl;
    }

}

