#include "ClassSchedule.h"
#include <utility>

//ClassSchedule Constructor Implementation
ClassSchedule::ClassSchedule() {ucTurma_ = UcTurma(); weekDay_ = "Default"; startHour_ = 0; duration_ = 0; type_ = "Default";}
ClassSchedule::ClassSchedule(UcTurma ucTurma, std::string weekDay, double startHour, double duration, std::string type)
{ucTurma_ = std::move(ucTurma); weekDay_ = std::move(weekDay); startHour_ = startHour; duration_ = duration; type_ = std::move(type);}

//ClassSchedule Setters Implementation
void ClassSchedule::set_ucTurma(UcTurma ucTurma) {ucTurma_ = std::move(ucTurma);}
void ClassSchedule::set_weekDay(std::string weekDay) {weekDay_ = std::move(weekDay);}
void ClassSchedule::set_starHour(double startHour) {startHour_ = startHour;}
void ClassSchedule::set_duration(double duration) {duration_ = duration;}
void ClassSchedule::set_type(std::string type) {type_ = std::move(type);}

//ClassSchedule Getters Implementation
UcTurma ClassSchedule::get_ucTurma() const {return ucTurma_;}
std::string ClassSchedule::get_weekday() const {return weekDay_;}
double ClassSchedule::get_startHour() const {return startHour_;}
double ClassSchedule::get_duration() const {return duration_;}
std::string ClassSchedule::get_type() const {return type_;}
double ClassSchedule::get_endHour() const {return startHour_ + duration_;}

