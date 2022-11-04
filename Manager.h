#ifndef LOADCLASSES_H_MANAGER_H
#define LOADCLASSES_H_MANAGER_H

#include <set>
#include <queue>
#include <list>
#include <fstream>
#include <iostream>
#include <regex>

#include "Student.h"
#include "ClassSchedule.h"
#include "Request.h"

class Manager {
private:
    std::set<Student> students_;
    std::vector<ClassSchedule> schedule_;
    std::queue<Request> requests_;
    std::list<UcTurma> all_ucs_;

public:
    //Manager Constructor
    Manager();

    //Manager Setters
    void set_students(const std::set<Student>& students);
    void set_schedule(const std::vector<ClassSchedule>& schedule);
    void set_requests(const std::queue<Request>& requests);
    void set_all_ucs(const std::list<UcTurma>& all_ucs);

    //Manager Getters
    std::set<Student> get_students() const;
    std::vector<ClassSchedule> get_schedule() const;
    std::queue<Request> get_requests() const;
    std::list<UcTurma> get_all_ucs() const;

    //Manager Methods
    /*!
     * add_Student adds one more student to the set of students of the manager
     * @param student Const Student variable that contains the student to be added
     */
    void add_Student(const Student& student);

    /*!
     * remove_student removes one student of the set of students in manager
     * @param ItStudent Student Set Iterator that contains the student to be removed
     */
    void remove_student(std::set<Student>::iterator ItStudent);
    Request front_request();
    void pop_request();

    //Loads
    void loadUcs();
    void loadSchedule();
    void loadStudentClasses();

    //Displays
    void classOcupation();
    void displayStudentsInClassUcYear();
    void studentSchedule();
    void studentsInUcs();

    //Modifications
    void removeStudent();
    void addStudent();
    void alterStudent();
    void alterSetStudents();
};

#endif //LOADCLASSES_H_MANAGER_H
