#include "Manager.h"

//Manager Constructor Implementation
Manager::Manager() {students_ = {}; schedule_ = {}; requests_ = {};}
Manager::Manager(std::set<Student> students, std::vector<ClassSchedule> schedule){students_ = students; schedule_ = schedule;}

//Manager Setters Implementation
void Manager::set_students(std::set<Student> students) {students_ = students;}
void Manager::set_schedule(std::vector<ClassSchedule> schedule) {schedule_ = schedule;}
void Manager::set_requests(std::queue<Request> requests) {requests_ = requests;}



//Manager Getters Implementation
std::set<Student> Manager::get_students() const {return students_;}
std::vector<ClassSchedule> Manager::get_schedule() const {return schedule_;}
std::queue<Request> Manager::get_requests() const {return requests_;}



//Manager Methods Implementation
void Manager::add_Student(const Student& s) {students_.insert(s);}
void Manager::add_request(const Request& r) {requests_.push(r);}

