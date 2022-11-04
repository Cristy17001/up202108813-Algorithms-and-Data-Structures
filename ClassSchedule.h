#ifndef LOADCLASSES_H_CLASSSCHEDULE_H
#define LOADCLASSES_H_CLASSSCHEDULE_H

#include "UcTurma.h"

class ClassSchedule {
private:
    UcTurma ucTurma_;
    std::string weekDay_, type_;
    double startHour_, duration_;

public:
    //ClassSchedule Constructor
    /*!
     * Big O notation -> O(1)
     * ClassSchedule Default Constructor
     */
    ClassSchedule();
    /*!
     * Big O notation -> O(1)
     * ClassSchedule Constructor
     * @param ucTurma
     * @param weekDay
     * @param startHour
     * @param duration
     * @param type
     */
    ClassSchedule(UcTurma ucTurma, std::string weekDay, double startHour, double duration, std::string type);

    //ClassSchedule Setters
    /*!
     * Big O notation -> O(1)
     * ClassSchedule setter for ucTurma
     * @param ucTurma UcTurma that will be assigned to the UcTurma ucTurma of the ClassSchedule
     */
    void set_ucTurma(UcTurma ucTurma);
    /*!
     * Big O notation -> O(1)
     * ClassSchedule setter for weekDay
     * @param weekDay string that will be assigned to the string weekDay of the ClassSchedule
     */
    void set_weekDay(std::string weekDay);
    /*!
     * Big O notation -> O(1)
     * ClassSchedule setter for startHour
     * @param startHour double that will be assigned to the double startHour of the ClassSchedule
     */
    void set_starHour(double startHour);
    /*!
     * Big O notation -> O(1)
     * ClassSchedule setter for duration
     * @param duration double that will be assigned to the double duration of the ClassSchedule
     */
    void set_duration(double duration);
    /*!
     * Big O notation -> O(1)
     * ClassSchedule setter for type
     * @param type string that will be assigned to the string type of the ClassSchedule
     */
    void set_type(std::string type);

    //ClassSchedule Getters
    /*!
     * Big O notation -> O(1)
     * ClassSchedule getter for ucTurma
     * @return object of type UcTurma referencing to the UcTurma ucTurma of the ClassSchedule
     */
    UcTurma get_ucTurma() const;
    /*!
     * Big O notation -> O(1)
     * ClassSchedule getter for weekDay
     * @return object of type string referencing to the string weekDay of the ClassSchedule
     */
    std::string get_weekday() const;
    /*!
     * Big O notation -> O(1)
     * ClassSchedule getter for startHour
     * @return object of type double referencing to the double startHour of the ClassSchedule
     */
    double get_startHour() const;
    /*!
     * Big O notation -> O(1)
     * ClassSchedule getter for duration
     * @return object of type double referencing to the double duration of the ClassSchedule
     */
    double get_duration() const;
    /*!
     * Big O notation -> O(1)
     * ClassSchedule getter for type
     * @return object of type string referencing to the string type of the ClassShcedule
     */
    std::string get_type() const;
    /*!
     * Big O notation -> O(1)
     * @return object of type double referencing to double StartHour + double duration of the ClassSchedule
     */
    double get_endHour() const;

};

#endif //LOADCLASSES_H_CLASSSCHEDULE_H
