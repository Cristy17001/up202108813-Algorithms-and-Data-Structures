#include "Request.h"
#include <utility>

//Request Constructor Implementation
Request::Request(std::string type, std::vector<std::string> data) {type_ = std::move(type); data_ = std::move(data);}

//Request Setters Implementation
void Request::set_type(std::string type) {type_ = std::move(type);}
void Request::set_data(std::vector<std::string> data) {data_ = std::move(data);}

//Request Getters Implementation
std::string Request::get_type() const {return type_;}
std::vector<std::string> Request::get_data() const {return data_;}

