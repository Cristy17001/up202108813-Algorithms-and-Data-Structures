#include "Manager.h"

//Manager Constructor Implementation
Manager::Manager() {students_ = {}; schedule_ = {}; requests_ = {}; all_ucs_ = {};}

//Manager Setters Implementation
void Manager::set_students(const std::set<Student>& students) {students_ = students;}
void Manager::set_schedule(const std::vector<ClassSchedule>& schedule) {schedule_ = schedule;}
void Manager::set_requests(const std::queue<Request>& requests) {requests_ = requests;}
void Manager::set_all_ucs(const std::list<UcTurma>& all_ucs) {all_ucs_ = all_ucs;}

//Manager Getters Implementation
std::set<Student> Manager::get_students() const {return students_;}
std::vector<ClassSchedule> Manager::get_schedule() const {return schedule_;}
std::queue<Request> Manager::get_requests() const {return requests_;}
std::list<UcTurma> Manager::get_all_ucs() const {return all_ucs_;}


//Some manager Methods Implementation
void Manager::add_Student(const Student& student) {students_.insert(student);}
void Manager::remove_student(std::set<Student>::iterator ItStudent) {students_.erase(*ItStudent);}
Request Manager::front_request() {return requests_.front();}
void Manager::pop_request() {requests_.pop();}

