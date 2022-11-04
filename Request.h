#ifndef MAIN_CPP_REQUEST_H
#define MAIN_CPP_REQUEST_H

#include <string>
#include <vector>

//Type can be "Remove", "Add", "Alter"
//Data is where the user input for the given type of request are stored

class Request {
private:
    std::string type_;
    std::vector<std::string> data_;

public:
    //Request Constructor

    /*!
     * Big O notation -> O(1)
     * Request default constructor
     * @param type can be "Remove", "Add", "Alter"
     * @param data is where the user input for the given type of request are stored
     */
    Request(std::string type, std::vector<std::string> data);

    //Request Setters

    /*!
     * Big O notation -> O(1)
     * Request setter for type
     * @param type string that will be assign to the string type of the Request
     */
    void set_type(std::string type);
    /*!
     * Big O notation -> O(1)
     * Request setter for data
     * @param data vector string that will be assigned to the vector data of the Request
     */
    void set_data(std::vector<std::string> data);

    //Request Getters

    /*!
    * Big O notation -> O(1)
    * Request getter for type
    * @return object of type string referencing to the string type of the Request
    */
    std::string get_type() const;
    /*!
     * Big O notation -> O(1)
     * Request getter for data
     * @return object of type vector string referencing to the vector data of the Request
     */
    std::vector<std::string> get_data() const;

};


#endif //MAIN_CPP_REQUEST_H
