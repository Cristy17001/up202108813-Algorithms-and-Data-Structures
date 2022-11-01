#include "Student.h"

//Student Constructor Implementation
Student::Student() {mecaNumber_ = "default"; name_ = "default"; turm_ = {};}
Student::Student(std::string mecaNumber, std::string name, std::list<UcTurma> turm) {mecaNumber_ = std::move(mecaNumber); name_ = std::move(name); turm_ = std::move(turm);}

//Student Setters Implementation
void Student::set_mecaNumber(const std::string& mecaNumber) {mecaNumber_ = mecaNumber;}
void Student::set_name(std::string name) {name_ = std::move(name);}
void Student::set_turm(std::list<UcTurma> turm) {turm_ = std::move(turm);}


//Student Getters Implementation
std::string Student::get_mecaNumber() const {return mecaNumber_;}
std::string Student::get_name() const {return name_;}
std::list<UcTurma> Student::get_turm() const {return turm_;}


//Student Operator Overloading Implementation
bool Student::operator<(const Student& s) const {
    {return mecaNumber_ < s.mecaNumber_;}
}

//Student Methods Implementation
bool Student::inside_turm(const UcTurma& u) const {
    for (const UcTurma& e: turm_) {if (e == u) return true;}
    return false;
}

bool Student::already_on_uc(const UcTurma& u) const {
    //if student already in a class of that uc. A student cannot be at 2 different classes in the same UC
    for (const UcTurma& e: turm_) {
        if (e.get_ucCode() == u.get_ucCode()) {
            return true;
        }
    }
    return false;
}

UcTurma Student::get_already_on_uc(const UcTurma& u) const {
    //if student already in a class of that uc. A student cannot be at 2 different classes in the same UC
    for (const UcTurma& e: turm_) {
        if (e.get_ucCode() == u.get_ucCode()) {
            return e;
        }
    }
    return u;
}



