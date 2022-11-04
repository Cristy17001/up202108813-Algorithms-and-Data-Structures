#ifndef LOADCLASSES_H_UCTURMA_H
#define LOADCLASSES_H_UCTURMA_H

#include <string>

class UcTurma{
private:
    std::string ucCode_;
    std::string classCode_;

public:
    /*!
     * UcTurma Default Constructor
     */
    UcTurma();

    /*!
     * UcTurma Constructor
     * @param ucCode
     * @param ClassCode
     */
    UcTurma(std::string ucCode, std::string ClassCode);

    //UcTurma Setters
    /*!
     * UcTurma setter for ucCode
     * @param ucCode string that will be assigned to the string ucCode of the UcTurma
     */
    void set_ucCode(std::string ucCode);
    /*!
     * UcTurma setter for classCode
     * @param classCode string that will be assigned to the string classCode of the UcTurma
     */
    void set_classCode_(std::string classCode);

    //UcTurma Getters
    /*!
     * Ucturma getter for ucCode
     * @return object of type string referencing to the string ucCode of the UcTurma
     */
    std::string get_ucCode() const;
    /*!
     * Ucturma getter for classCode
     * @return object of type string referencing to the string classCode of the UcTurma
     */
    std::string get_classCode() const;

    char get_year();

    //Student Operator UcTurma
    /*!
     * Student Operator Ucturma
     * @param t
     * @return
     */
    bool operator==(const UcTurma& t) const;
    /*!
     * Student Operator UcTurma
     * @param t
     * @return
     */
    bool operator<(const UcTurma& t) const;


};

#endif
