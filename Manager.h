#ifndef LOADCLASSES_H_MANAGER_H
#define LOADCLASSES_H_MANAGER_H

#include <set>
#include <vector>
#include <queue>

#include "Student.h"
#include "ClassSchedule.h"
#include "Request.h"

class Manager {
private:
    std::set<Student> students_;
    std::vector<ClassSchedule> schedule_;
    std::queue<Request> requests_;

public:
    //Manager Constructor
    Manager();
    Manager(std::set<Student> students, std::vector<ClassSchedule> schedule);

    //Manager Setters
    void set_students(std::set<Student> students);
    void set_schedule(std::vector<ClassSchedule> schedule);
    void set_requests(std::queue<Request> requests);

    //Manager Getters
    std::set<Student> get_students() const;
    std::vector<ClassSchedule> get_schedule() const;
    std::queue<Request> get_requests() const;


    //Manager Methods
    void add_Student(const Student& s);
    void add_request(const Request& r);

};

#endif //LOADCLASSES_H_MANAGER_H
