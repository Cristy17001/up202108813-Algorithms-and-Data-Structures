#ifndef MAIN_CPP_REQUEST_H
#define MAIN_CPP_REQUEST_H

#include <string>
#include <vector>

//Type can be "Remove", "Add", "Alter", "AlterSet"
//Data is where the user input for the given type of request are stored

class Request {
private:
    std::string type_;
    std::vector<std::string> data_;

public:
    //Request Constructor
    Request(std::string type, std::vector<std::string> data);

    //Request Setters
    void set_type(std::string type);
    void set_data(std::vector<std::string> data);

    //Request Getters
    std::string get_type() const;
    std::vector<std::string> get_data() const;

};


#endif //MAIN_CPP_REQUEST_H
