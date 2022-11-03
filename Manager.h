#ifndef LOADCLASSES_H_MANAGER_H
#define LOADCLASSES_H_MANAGER_H

#include <set>
#include <queue>
#include <list>

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
    Manager(const std::set<Student>& students, const std::vector<ClassSchedule>& schedule);

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
    void add_Student(const Student& s);
    void remove_student(std::set<Student>::iterator start);
    void add_request(const Request& r);
    Request front_request();
    void pop_request();
    void add_UC(const UcTurma& t);


};

#endif //LOADCLASSES_H_MANAGER_H
