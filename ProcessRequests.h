#include "CheckCap.h"
#include "CheckBalance.h"
#include "CheckCompatability.h"

void ProcessRequests(std::vector<std::string>& log, Manager& m) {
    while (!m.get_requests().empty()) {

        Request request = m.front_request();
        m.pop_request();

        if (request.get_type() == "Remove") {
            std::string meca = request.get_data()[0];
            std::string uc = request.get_data()[1];
            std::string turma = request.get_data()[2];
            std::string log_text;

            bool error = false;
            //Constrains and log write
            if (!(regex_search(meca, std::regex("2[0-9]{8}")))) {
                log_text = LogMessage(
                        std::string("Error Removing Student: Invalid Input MECANUMBER (StudentID) " + meca));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(uc, std::regex("[A-Z]{1}[.]{1}[A-Z]{3}[0-9]{3}")))) {
                log_text = LogMessage(std::string("Error Removing Student: Invalid Input UC (UcID) " + uc));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(turma, std::regex("[1-5]{1}[A-Z]{4}[0-9]{2}")))) {
                log_text = LogMessage(std::string("Error Removing Student: Invalid Input Class (ClassID) " + turma));
                log.push_back(log_text);
                error = true;
            }

            //if data invalid just write to log and ignore search
            if (!error) {

                //Finding the student in LogN time using predicate in a lambda function
                std::set<Student> students = m.get_students();
                std::list<UcTurma> turmas;
                auto it_stud = find_if(students.begin(), students.end(),
                                       [&meca](const Student &stud) -> bool { return stud.get_mecaNumber() == meca; });

                //if student was found
                if (!(it_stud == students.end())) { turmas = it_stud->get_turm(); }

                //if student couldn't be found
                if (turmas.empty()) {
                    ostringstream input;
                    input << "Error Removing Student: Couldn't find Student with Meca: " << meca << " at UC: " << uc
                          << " in Class: " << turma;
                    log_text = LogMessage(input.str());
                    log.push_back(log_text);
                } else {

                    //if the student is in that UCTurma then remove it
                    UcTurma check = UcTurma(uc, turma);
                    for (UcTurma &t: turmas) {
                        if (t == check) {
                            turmas.remove(t);
                            break;
                        }
                    }

                    Student mod_student = Student(it_stud->get_mecaNumber(), it_stud->get_name(), turmas);
                    m.remove_student(it_stud);
                    m.add_Student(mod_student);

                    //Successfully Removed message
                    ostringstream input;
                    input << "Success Removed Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc << " Student successfully Removed if it existed";
                    log_text = LogMessage(input.str());
                    log.push_back(log_text);
                }
            }

        }
        if (request.get_type() == "Add") {
            std::string meca = request.get_data()[0];
            std::string uc = request.get_data()[1];
            std::string turma = request.get_data()[2];
            std::string cap = request.get_data()[3];
            std::string balance = request.get_data()[4];
            std::string log_text;

            //Constrains and log write
            bool error = false;

            if (!(regex_search(meca, std::regex("2[0-9]{8}")))) {
                log_text = LogMessage(
                        std::string("Error Adding Student: Invalid Input MECANUMBER (StudentID) " + meca));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(uc, std::regex("[A-Z]{1}[.]{1}[A-Z]{3}[0-9]{3}")))) {
                log_text = LogMessage(std::string("Error Adding Student: Invalid Input UC (UcID) " + uc));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(turma, std::regex("[1-5]{1}[A-Z]{4}[0-9]{2}")))) {
                log_text = LogMessage(std::string("Error Adding Student: Invalid Input Class (ClassID) " + turma));
                log.push_back(log_text);
                error = true;
            }

            //can't be over 99 students in a class
            if (!(regex_search(cap, std::regex("[1-9]{1}[0-9]{0,1}")))) {
                log_text = LogMessage(std::string(
                        "Error Adding Student: Invalid Input Cap either number is to big or not recognised Input: " +
                        cap));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(balance, std::regex("[YN]{1}")))) {
                log_text = LogMessage(
                        std::string("Error Adding Student: Invalid Input balanced or not Input: " + balance));
                log.push_back(log_text);
                error = true;
            }

            //if data invalid just write to log and ignore search
            if (!error) {
                //Verify if the Student exists
                std::set<Student> students = m.get_students();
                std::list<UcTurma> turmas;
                auto it_stud = find_if(students.begin(), students.end(),
                                       [&meca](const Student &stud) -> bool {return stud.get_mecaNumber() == meca;});

                if (!(it_stud == students.end())) { turmas = it_stud->get_turm(); }

                auto aux = UcTurma(uc, turma);
                //if student wasn't found
                if (turmas.empty()) {
                    ostringstream input;
                    input << "Error Adding Student: Couldn't find Student with Meca: " << meca;
                    log_text = LogMessage(input.str());
                    log.push_back(log_text);
                }
                //if student was found and already on a Class for that UC
                else if (it_stud->already_on_uc(aux)) {
                    ostringstream input;
                    input << "Error Adding Student: Student with " << meca << " already inside Class: " << turma
                          << " at UC: " << uc << ". A student can't have more then one class at the same UC!";
                    log_text = LogMessage(input.str());
                    log.push_back(log_text);
                }
                //if student was found
                else {
                    //if n_students doesn't surpass the CAP
                    UcTurma temp_turma = UcTurma(uc, turma);
                    int n_cap = stoi(cap);

                    if (CheckCap(m, temp_turma, n_cap)) {
                        //if there is an unbalance and user doesn't want to ignore it
                        if (!CheckBalance(m, uc, temp_turma) && balance == "N") {
                            ostringstream input;
                            input << "Error Adding Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc <<" Unbalance detected and user said to respect it";
                            log_text = LogMessage(input.str());
                            log.push_back(log_text);
                        }
                        //if there is an unbalance and want to ignore it
                        else if (!CheckBalance(m, uc, temp_turma) && balance == "Y") {
                            ostringstream input3;
                            input3 << "Note Adding Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc << " Unbalance detected and choose to ignore it";
                            log_text = LogMessage(input3.str());
                            log.push_back(log_text);

                            //if schedule is compatible
                            if (CheckCompatability(m, it_stud->get_turm(), UcTurma(uc, turma)))
                            {
                                UcTurma aux_adding_uc = UcTurma(uc, turma);
                                list<UcTurma> aux_list = it_stud->get_turm();
                                aux_list.push_back(aux_adding_uc);
                                aux_list.sort();
                                Student new_student = Student(it_stud->get_mecaNumber(), it_stud->get_name(), aux_list);
                                m.remove_student(it_stud);
                                m.add_Student(new_student);

                                //Successfully Added message
                                ostringstream input;
                                input << "Success Adding Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc << " Student successfully added";
                                log_text = LogMessage(input.str());
                                log.push_back(log_text);
                            }
                            else {
                                ostringstream input2;
                                input2 << "Error Adding Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc << " Compatability error overlap of schedules prevented!";
                                log_text = LogMessage(input2.str());
                                log.push_back(log_text);
                            }
                        }
                        //dont write to console no error
                        else if ((CheckBalance(m, uc, temp_turma) && balance == "N") || (CheckBalance(m, uc, temp_turma) && balance == "Y")) {
                            if (CheckCompatability(m, it_stud->get_turm(), UcTurma(uc, turma)))
                            {
                                UcTurma aux_adding_uc = UcTurma(uc, turma);
                                list<UcTurma> aux_list = it_stud->get_turm();
                                aux_list.push_back(aux_adding_uc);
                                aux_list.sort();
                                Student new_student = Student(it_stud->get_mecaNumber(), it_stud->get_name(), aux_list);
                                m.remove_student(it_stud);
                                m.add_Student(new_student);

                                //Successfully Added message
                                ostringstream input;
                                input << "Success Adding Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc << " Student successfully added";
                                log_text = LogMessage(input.str());
                                log.push_back(log_text);
                            }
                            else {
                                ostringstream input;
                                input << "Error Adding Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc << " Compatability error overlap of schedules prevented!";
                                log_text = LogMessage(input.str());
                                log.push_back(log_text);
                            }
                        }
                        else {
                            ostringstream input;
                            input << "Error Adding Student: UNEXPECTED ERROR OCCURRED!";
                            log_text = LogMessage(input.str());
                            log.push_back(log_text);
                        }
                    }

                    //if n_students has surpassed the CAP
                    else {
                        ostringstream input;
                        input << "Error Adding Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc
                        << " either can't add more because of Cap or that class in that specific UC isn't on the database!";
                        log_text = LogMessage(input.str());
                        log.push_back(log_text);
                    }

                }
            }
        }
        if (request.get_type() == "Alter") {

            std::string meca = request.get_data()[0];
            std::string uc = request.get_data()[1];
            std::string turma = request.get_data()[2];
            std::string cap = request.get_data()[3];
            std::string balance = request.get_data()[4];
            std::string log_text;

            //Constrains and log write
            bool error = false;

            if (!(regex_search(meca, std::regex("2[0-9]{8}")))) {
                log_text = LogMessage(
                        std::string("Error Altering Student: Invalid Input MECANUMBER (StudentID) " + meca));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(uc, std::regex("[A-Z]{1}[.]{1}[A-Z]{3}[0-9]{3}")))) {
                log_text = LogMessage(std::string("Error Altering Student: Invalid Input UC (UcID) " + uc));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(turma, std::regex("[1-5]{1}[A-Z]{4}[0-9]{2}")))) {
                log_text = LogMessage(std::string("Error Altering Student: Invalid Input Class (ClassID) " + turma));
                log.push_back(log_text);
                error = true;
            }

            //can't be over 99 students in a class
            if (!(regex_search(cap, std::regex("[1-9]{1}[0-9]{0,1}")))) {
                log_text = LogMessage(std::string(
                        "Error Altering Student: Invalid Input Cap either number is to big or not recognised Input: " +
                        cap));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(balance, std::regex("[YN]{1}")))) {
                log_text = LogMessage(
                        std::string("Error Altering Student: Invalid Input balanced or not Input: " + balance));
                log.push_back(log_text);
                error = true;
            }

            //if data invalid just write to log and ignore search
            if (!error) {
                //Verify if the Student exists
                std::set<Student> students = m.get_students();
                std::list<UcTurma> turmas;
                auto it_stud = find_if(students.begin(), students.end(),
                                       [&meca](const Student &stud) -> bool { return stud.get_mecaNumber() == meca; });

                if (!(it_stud == students.end())) { turmas = it_stud->get_turm(); }

                auto aux = UcTurma(uc, turma);
                //if student wasn't found
                if (turmas.empty()) {
                    ostringstream input;
                    input << "Error Altering Student: Couldn't find Student with Meca: " << meca;
                    log_text = LogMessage(input.str());
                    log.push_back(log_text);
                }
                    //if student was found and already on a Class for that UC Continue with the Altering
                else if (it_stud->already_on_uc(aux)) {
                    //if n_students doesn't surpass the CAP

                    //Class he is trying to get in
                    UcTurma enter_turm = UcTurma(uc, turma);
                    //Class he is in
                    UcTurma leaving_turm = it_stud->get_already_on_uc(enter_turm);

                    int n_cap = stoi(cap);

                    if (CheckCap(m, enter_turm, n_cap)) {
                        //if there is an unbalance and user doesn't want to ignore it
                        if (!CheckBalance(m, uc, enter_turm, leaving_turm) && balance == "N") {
                            ostringstream input;
                            input << "Error Altering Student: For input meca: " << meca << " class: " << turma
                                  << " Uc: " << uc << " Unbalance detected and user said to respect it";
                            log_text = LogMessage(input.str());
                            log.push_back(log_text);
                        }
                        //if there is an unbalance and user want to ignore it
                        else if (!CheckBalance(m, uc, enter_turm, leaving_turm) && balance == "Y") {
                            ostringstream input3;
                            input3 << "Note Altering Student: For input meca: " << meca << " class: " << turma
                                   << " Uc: " << uc << " Unbalance detected and choose to ignore it";
                            log_text = LogMessage(input3.str());
                            log.push_back(log_text);

                            //if schedule is compatible
                            list<UcTurma> aux_list = it_stud->get_turm();
                            //remove from class he was in
                            aux_list.remove(leaving_turm);
                            if (CheckCompatability(m, aux_list, UcTurma(uc, turma))) {
                                //add to the new class
                                aux_list.push_back(enter_turm);
                                aux_list.sort();
                                Student new_student = Student(it_stud->get_mecaNumber(), it_stud->get_name(), aux_list);
                                m.remove_student(it_stud);
                                m.add_Student(new_student);

                                //Successfully Altered message
                                ostringstream input;
                                input << "Success Altering Student: For input meca: " << meca << " class: " << turma
                                      << " Uc: " << uc << " Student successfully altered";
                                log_text = LogMessage(input.str());
                                log.push_back(log_text);
                            } else {
                                ostringstream input2;
                                input2 << "Error Altering Student: For input meca: " << meca << " class: " << turma
                                       << " Uc: "
                                       << uc << " Compatability error overlap of schedules prevented!";
                                log_text = LogMessage(input2.str());
                                log.push_back(log_text);
                            }
                        }
                        //dont write to console no error
                        else if ((CheckBalance(m, uc, enter_turm, leaving_turm) && balance == "N") || (CheckBalance(m, uc, enter_turm, leaving_turm) && balance == "Y")) {
                            list<UcTurma> aux_list = it_stud->get_turm();
                            //remove from class he was in
                            aux_list.remove(leaving_turm);
                            if (CheckCompatability(m, aux_list, UcTurma(uc, turma))) {
                                //add to the new class
                                aux_list.push_back(enter_turm);
                                aux_list.sort();
                                Student new_student = Student(it_stud->get_mecaNumber(), it_stud->get_name(), aux_list);
                                m.remove_student(it_stud);
                                m.add_Student(new_student);

                                //Successfully Altered message
                                ostringstream input;
                                input << "Success Altering Student: For input meca: " << meca << " class: " << turma
                                      << " Uc: " << uc << " Student successfully altered";
                                log_text = LogMessage(input.str());
                                log.push_back(log_text);
                            }
                            else {
                                ostringstream input;
                                input << "Error Altering Student: For input meca: " << meca << " class: " << turma
                                      << " Uc: " << uc << " Compatability error overlap of schedules prevented!";
                                log_text = LogMessage(input.str());
                                log.push_back(log_text);
                            }
                        }
                        else {
                            ostringstream input;
                            input << "Error Altering Student: UNEXPECTED ERROR OCCURRED!";
                            log_text = LogMessage(input.str());
                            log.push_back(log_text);
                        }

                    }
                    //if n_students has surpassed the CAP
                    else {
                        ostringstream input;
                        input << "Error Altering Student: For input meca: " << meca << " class: " << turma << " Uc: "
                              << uc << " either can't add more because of Cap or that class in that specific UC isn't on the database!";
                        log_text = LogMessage(input.str());
                        log.push_back(log_text);
                    }
                }
                //if student isn't already in that UC
                else {
                    ostringstream input;
                    input << "Error Altering Student: Student with " << meca << " isn't inside Class: " << turma
                          << " at UC: " << uc << ", therefore is class can't be altered!";
                    log_text = LogMessage(input.str());
                    log.push_back(log_text);
                }
            }
        }
    }
}