#include "UcTurma.h"

#include <utility>

//UcTurma Default Constructor Implementation
UcTurma::UcTurma() {ucCode_ = "default", classCode_ = "default";}

//UcTurma Constructor Implementation
UcTurma::UcTurma(std::string ucCode, std::string classCode) {ucCode_ = std::move(ucCode); classCode_ = std::move(classCode);}

//UcTurma Setters Implementation
void UcTurma::set_ucCode(std::string ucCode) {ucCode_ = std::move(ucCode);}
void UcTurma::set_classCode_(std::string classCode) {classCode_ = std::move(classCode);}

//UcTurma Getters Implementation
std::string UcTurma::get_ucCode() const {return ucCode_;}
std::string UcTurma::get_classCode() const {return classCode_;}

//UcTurma Methods
char UcTurma::get_year() {return classCode_[0];}

//Student Operator UcTurma Implementation
bool UcTurma::operator==(const UcTurma& t) const {return (t.get_classCode() == classCode_ && t.get_ucCode()== ucCode_);}
bool UcTurma::operator<(const UcTurma& t) const {return ucCode_ < t.get_ucCode();}
