#ifndef LOADCLASSES_H_UCTURMA_H
#define LOADCLASSES_H_UCTURMA_H

#include <string>

class UcTurma{
private:
    std::string ucCode_;
    std::string classCode_;

public:
    /*!
     * Big O notation -> O(1)
     * UcTurma Default Constructor
     */
    UcTurma();

    /*!
     * Big O notation -> O(1)
     * UcTurma Constructor
     * @param ucCode
     * @param ClassCode
     */
    UcTurma(std::string ucCode, std::string ClassCode);

    //UcTurma Setters
    /*!
     * Big O notation -> O(1)
     * UcTurma setter for ucCode
     * @param ucCode string that will be assigned to the string ucCode of the UcTurma
     */
    void set_ucCode(std::string ucCode);
    /*!
     * Big O notation -> O(1)
     * UcTurma setter for classCode
     * @param classCode string that will be assigned to the string classCode of the UcTurma
     */
    void set_classCode_(std::string classCode);

    //UcTurma Getters
    /*!
     * Big O notation -> O(1)
     * Ucturma getter for ucCode
     * @return object of type string referencing to the string ucCode of the UcTurma
     */
    std::string get_ucCode() const;
    /*!
     * Big O notation -> O(1)
     * Ucturma getter for classCode
     * @return object of type string referencing to the string classCode of the UcTurma
     */
    std::string get_classCode() const;

    /*!
     * Big O notation -> O(1)
     * @return char Year from which the a class is
     */
    char get_year();

    //Student Operator UcTurma
    /*!
     * Big O notation -> O(1)
     * Student Operator Ucturma
     * @param t const UcTurma
     * @return true if UcTurma equal to the UcTurma passed by argument, false otherwise
     */
    bool operator==(const UcTurma& t) const;
    /*!
     * Big O notation -> O(1)
     * Student Operator < check between classes
     * @param t const UcTurma
     * @return true if ucCode from this UcTurma < Ucturma passed by argument, false otherwise
     */
    bool operator<(const UcTurma& t) const;


};

#endif
