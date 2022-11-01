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
    Student();
    Student(std::string mecaNumber, std::string name, std::list<UcTurma> turm);

    //Student Setters
    void set_mecaNumber(const std::string& mecaNumber);
    void set_name(std::string name);
    void set_turm(std::list<UcTurma> turm);


    //Student Getters
    std::string get_mecaNumber() const;
    std::string get_name() const;
    std::list<UcTurma> get_turm() const;


    //Student Operator Overloading
    bool operator<(const Student& s) const;

    //Student Methods
    bool inside_turm(const UcTurma& u) const;
    bool already_on_uc(const UcTurma& u) const;
    UcTurma get_already_on_uc(const UcTurma& u) const;
};

#endif //LOADCLASSES_H_STUDENT_H
