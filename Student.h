#ifndef LOADCLASSES_H_STUDENT_H
#define LOADCLASSES_H_STUDENT_H

#include <string>
#include <list>
#include "UcTurma.h"

class Student {
private:
    std::string mecaNumber_;
    std::string name_;
    std::list<UcTurma> turm_;

public:
    //Student Constructor
    /*!
     * Student default constructor
     */
    Student();
    Student(std::string mecaNumber, std::string name, std::list<UcTurma> turm);

    //Student Setters

    /*!
     * Student setter for mecanumber.
     * @param mecaNumber const string that will be assigned to the string mecaNumber of the Student
     */
    void set_mecaNumber(const std::string& mecaNumber);
    /*!
     * Student setter for name.
     * @param name string that will be assigned to the string name of the Student
     */
    void set_name(std::string name);
    /*!
     * Student for classes and UCs.
     * @param turm list UcTurma that will be assigned to the list turm of the Student
     */
    void set_turm(std::list<UcTurma> turm);


    //Student Getters

    /*!
     * Student getter for mecanumber.
     * @return object of type string referencing to the string mecaNumber of the Student
     */
    std::string get_mecaNumber() const;
    /*!
     * Student getter for name.
     * @return object of type string referencing to the string name of the Student
     */
    std::string get_name() const;
    /*!
     * Student getter for classes and UCs.
     * @return object of type list UcTurma referencing to the list Ucturma of the Manager
     */
    std::list<UcTurma> get_turm() const;


    //Student Operator Overloading

    /*!
     * Student Operator < Overloading
     * @param s
     * @return true if this student < student passed by argument, false otherwise
     */
    bool operator<(const Student& s) const;

    //Student Methods
    /*!
     * Responsible to verify if student already in a class.
     * @param const UcTurma
     * @return true if Ucturma already inside the classes of that student
     */
    bool inside_turm(const UcTurma& u) const;
    /*!
     * Responsible to verify if student already in a class of that uc. A student cannot be at 2 different classes in the same UC.
     * @param u const UcTurma
     * @return true if UcTurma passed by argument is already inside the classes of this student, false otherwise
     */
    bool already_on_uc(const UcTurma& u) const;
    /*!
     * Responsible to verify if student already in a class of that uc. A student cannot be at 2 different classes in the same UC.
     * @param u
     * @return the UcTurma if UcTurma passed by argument is already inside the classes of this student, false otherwise
     */
    UcTurma get_already_on_uc(const UcTurma& u) const;
};

#endif //LOADCLASSES_H_STUDENT_H
