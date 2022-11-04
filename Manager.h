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
    /*!
     * Manager default constructor
     */
    Manager();

    //Manager Setters
    /*!
     * Setter for the set of Students
     * @param students const set Student that will be assigned to the set Students of the Manager
     */
    void set_students(const std::set<Student>& students);
    /*!
     * Setter for the vector ClassSchedule
     * @param schedule const vector ClassSchedule that will be assigned to the vector schedule of the Manager
     */
    void set_schedule(const std::vector<ClassSchedule>& schedule);
    /*!
     * Setter for the queue Request
     * @param requests const queue Request that will be assigned to the queue requests of the Manager
     */
    void set_requests(const std::queue<Request>& requests);
    /*!
     * Setter for the list UcTurma
     * @param all_ucs const list UcTurma that will be assigned to the list all_ucs of the Manager
     */
    void set_all_ucs(const std::list<UcTurma>& all_ucs);

    //Manager Getters

    /*!
     * Getter for the set Student
     * @return object of type set Student referencing to the set students of the Manager
     */
    std::set<Student> get_students() const;
    /*!
     * Getter for the vector ClassSchedule
     * @return object of type vector ClassSchedule referencing to the vector schedule of the Manager
     */
    std::vector<ClassSchedule> get_schedule() const;
    /*!
     * Getter for the queue Request
     * @return object of type queue Request referencing to the queue requests of the Manager
     */
    std::queue<Request> get_requests() const;
    /*!
     * Getter for the list UcTurma
     * @return object of type list UcTurma referencing to the list UcTurma of the Manager
     */
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

    /*!
     * Gets the Request front of the queue of requests
     * @return returns a object of type Request
     */
    Request front_request();
    /*!
     * Responsible for removing the front Request of the queue
     */
    void pop_request();

    //Loads

    /*!
     * Responsible for loading all_ucs from the excel file "classes_per_uc"
     */
    void loadUcs();
    /*!
     * Responsible for loading schedule from the excel file "classes"
     */
    void loadSchedule();
    /*!
     * Responsible for loading students from the excel file "students_classes"
     */
    void loadStudentClasses();

    //Displays

    /*!
     * Asks for the input for the uc, year and classNumber and prints to the screen the number of students in that
     * class if there is some, it there isn't then prints where it failed
     */
    void classOcupation();
    /*!
     * Asks for the input for the uc, year, classNumber, typeOrder, sortOrder and numberStudents and prints to the screen the students in that
     * class if there is some, it there isn't then prints where it failed
     */
    void displayStudentsInClassUcYear();
    /*!
     * Asks for the input for the mecaNumber of the students and prints his schedule otherwise
     * if there isn't any or an error occurred prints why it happened
     */
    void studentSchedule();
    //todo
    void studentsInUcs();

    //Modifications

    /*!
     * Asks for the input for the uc and class to be removed from student with mecaNumber and stores it in the managers queue of requests in order
     * to be processed afterwards for the ProcessRequests function
     */
    void removeStudent();
    /*!
     * Asks for the input for the uc and class to be add to the student with mecaNumber and also the MaxNumber of students
     * a class can have and if there is an unbalance between the classes of that uc if he wishes to ignore it and stores it
     * in the managers queue of requests in order to be processed afterwards for the ProcessRequests function
     */
    void addStudent();
    /*!
     * Asks for the input for the uc and class to be altered to the student with mecaNumber and also the MaxNumber of students
     * a class can have and if there is an unbalance between the classes of that uc if he wishes to ignore it and stores it
     * in the managers queue of requests in order to be processed afterwards for the ProcessRequests function
     */
    void alterStudent();
    /*!
     * Asks for the input for the uc and class to be altered to the student with mecaNumber and also the MaxNumber of students
     * a class can have and if there is an unbalance between the classes of that uc if he wishes to ignore it while the user
     * wants to continue inputing and stores it in the managers queue of requests in order to be processed afterwards for the ProcessRequests function
     */
    void alterSetStudents();
};

#endif //LOADCLASSES_H_MANAGER_H
