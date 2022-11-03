#include "UcTurma.h"
#include <string>
#include <list>
#include <regex>

void studentsInUcs(const Manager& m) {
    string nUcs, order;
    cout << "Example: 1, 2, 3, 4, (...), 9" << endl;
    cout << "Introduce a number of UCs: ";
    cin >> nUcs; cout << endl;
    cout << "Order alphabetically (1) or by mecanumber(2): ";
    cin >> order; cout << endl;

    bool error = false;
    //Constrains
    if (!(regex_match(nUcs, regex("[0-9]{1}")))) {cout << "INVALID NUMBER!" << endl; error = true;}
    if (!(regex_match(order, regex("[12]{1}")))) {cout << "INVALID OPTION!" << endl; error = true;}
    if (error) return;

    auto name = [](const Student& a, const Student&b) {return a.get_name() < b.get_name(); };
    std::set<Student, decltype(name) > studentByName(name);
    auto meca = [](const Student&a, const Student&b) {return a.get_mecaNumber() < b.get_mecaNumber();};
    std::set<Student, decltype(meca) > studentByMeca(meca);

    int nUc = stoi(nUcs);

    if (order == "1") {
        studentByName.clear();
        for (const Student& s: m.get_students()) {
            if (s.get_turm().size() > nUc) {
            studentByName.insert(s);
            }
        }
        for (const Student& s: studentByName) {
            cout << s.get_mecaNumber() << ' ' << s.get_name() << endl;
        }
        if (studentByName.empty()) cout << "Couldn't find any student." << endl;
    }

    else if (order == "2") {
        studentByMeca.clear();
        for (const Student& s: m.get_students()) {
            if (s.get_turm().size() > nUc) {
                studentByMeca.insert(s);
            }
        }
        for(const Student& s: studentByMeca){
            cout << s.get_mecaNumber() << ' ' << s.get_name() << endl;
        }
        if(studentByMeca.empty()) cout << "Couldn't find any student." << endl;
    }
}