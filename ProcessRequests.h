/*!
 * Big O notation -> O(n) - n being the number of students
 * Responsible to verify if while adding a student to a class at a given UC it causes a difference
 * grater or equal than 4 between the number of student in that UC
 * @param m Manager to access the data from the excel and change it
 * @param uc string the UC for the balance to be check
 * @param temp_turma const UcTurma the class and UC the student is trying to get in
 * @return True if the change doesn't cause an unbalance, False otherwise
 */
bool CheckBalance(const Manager& m, string& uc, const UcTurma& temp_turma) {
    long long min = 2147483646, max = -1;
    auto students = m.get_students();
    //Iterate over every class of that uc and count the number of students in it
    for (const UcTurma& e: m.get_all_ucs()) {
        //if it is from the same uc
        if (e.get_ucCode() == uc) {
            //verify which class it is and count the number of student's in it
            auto aux = e.get_classCode();
            UcTurma t = UcTurma(uc, aux);
            auto count = count_if(students.begin(), students.end(),
                                  [&t](const Student &stud) -> bool {return stud.inside_turm(t);});

            //if it is the class he is trying to get in then consider one more student
            if (t == temp_turma) count++;

            if (count > max) {max = count;}
            if (count < min) {min = count;}
        }
    }
    //Biggest possible difference between the 2 classes from the same UC
    long long max_diff = max - min;
    //True -> if balanced
    //False -> Not balanced
    return max_diff < 4;
}

/*!
 * Big O notation -> O(n) - n being the number of students
 * Responsible to verify if while changing a student from one class to another at the same UC it causes a difference
 * grater or equal than 4 between the number of student in that UC
 * @param m Manager to access the data from the excel and change it
 * @param uc string the UC for the balance to be check
 * @param enter_turm const UcTurma the class and UC the student is trying to get in
 * @param leaving_turm const UcTurma the class and UC the student is trying to be changed from
 * @return True if the change doesn't cause an unbalance, False otherwise
 */
bool CheckBalance(const Manager& m, string& uc, const UcTurma& enter_turm,const UcTurma& leaving_turm) {
    //Balance Altering is different because he is leaving one and entering another one
    long long min = 2147483646, max = -1;
    auto students = m.get_students();
    //Iterate over every class of that uc and count the number of students in it
    for (const UcTurma& e: m.get_all_ucs()) {
        //if it is from the same uc
        if (e.get_ucCode() == uc) {
            //verify which class it is and count the number of student's in it
            auto aux = e.get_classCode();
            UcTurma t = UcTurma(uc, aux);
            auto count = count_if(students.begin(), students.end(),
                                  [&t](const Student &stud) -> bool {return stud.inside_turm(t);});

            //if it is the class he is trying to get in then consider one more student
            if (t == enter_turm) count++;
            //if it is the class he is getting out then consider one less student
            if (t == leaving_turm) count--;

            if (count > max) {max = count;}
            if (count < min) {min = count;}
        }
    }
    //Biggest possible difference between the 2 classes from the same UC
    long long max_diff = max - min;
    //True -> if balanced
    //False -> Not balanced
    return max_diff < 4;
}

/*!
 * Big O notation -> O(n) - n being the number of students
 * Responsible for verifying if adding one student to a given class causes the number of students of a class to be
 * bigger than the the CAP a number the user inputted representing the maximum number of students a class
 * @param m Manager to access the data from the excel and change it
 * @param turma UcTurma the class the student is trying to get in
 * @param cap int the maximum number of students a class can have, that being a given input by the user
 * @return True if the student can be add without any problem, False otherwise
 */
bool CheckCap(Manager& m, UcTurma& turma, int cap) {
    //count the number of students that have the same class and same UC
    auto students = m.get_students();
    auto n_students = count_if(students.begin(), students.end(),
                               [&turma](const Student &stud) -> bool {return stud.inside_turm(turma);});
    //verify if it can be added one more student without surpassing cap
    //True -> meaning it is ok
    //False -> meaning it is to much
    int res = ((n_students + 1) < cap) && n_students != 0;
    return res;
}

/*!
 * Big O notation -> O(n*x) - n being the number of schedules and x the number of Uc/class's
 * Responsible for verifying if adding a given class to a student doesn't cause an overlap between the schedule of that student
 * @param m Manager to access the data from the excel and change it
 * @param actual_turmas list UcTurma representing the list of classes and UC the student is inside
 * @param turma_mod const UcTurma representing the class at a given UC that a student is trying to get in
 * @return True if there the adding doesn't cause an overlap, False otherwise
 */
bool CheckCompatability(Manager m, list<UcTurma> actual_turmas, const UcTurma& turma_mod) {
    //iterate over every schedule, saving every class the student has in one list
    //iterate over every schedule, saving every schedule of the class we are trying to add to the student
    list<ClassSchedule> mod_schedule; list<ClassSchedule> actual_schedule;

    //iterate over every schedule
    for (const ClassSchedule& schedule: m.get_schedule()) {
        //saving every class the student has in one list
        for (const UcTurma& turma: actual_turmas) {
            if (schedule.get_ucTurma() == turma) {actual_schedule.push_back(schedule);}
        }
        //saving every schedule of the class we are trying to add to the student
        if (turma_mod == schedule.get_ucTurma()) {mod_schedule.push_back(schedule);}
    }

    //verify compatability
    for (const ClassSchedule& actual: actual_schedule) {
        for (const ClassSchedule& mod: mod_schedule) {
            if (actual.get_weekday() == mod.get_weekday()) {
                //on top -> Modification.end_hour <= Actual.start_hour && Modification.start_hour < Actual.start_hour
                //on bottom -> Modification.start_hour >= Actual.end_hour && Modification.end_hour > Actual.end_hour
                //if not compatible then return false
                if (!((mod.get_endHour() <= actual.get_startHour() && mod.get_startHour() < actual.get_startHour()) ||
                      (mod.get_startHour() >= actual.get_endHour() && mod.get_endHour() > actual.get_endHour())))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

/*!
 * Big O notation -> O(n)
 * Responsible for processing all the types of request them being "Add", "Remove" and "Alter" and report there execution
 * to the logfile in other for the user to be able to lookup the changes made in the Log_Output.txt
 * @param log vector string for storing the output message of the logfile
 * @param m Manager to access the data from the excel and change it
 */
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
            if (!(regex_match(meca, std::regex("2[0-9]{8}")))) {
                log_text = LogMessage(
                        std::string("Error Removing Student: Invalid Input MECANUMBER (StudentID) " + meca));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_match(uc, std::regex("[A-Z]{1}[.]{1}[A-Z]{3}[0-9]{3}")))) {
                log_text = LogMessage(std::string("Error Removing Student: Invalid Input UC (UcID) " + uc));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_match(turma, std::regex("[1-5]{1}[A-Z]{4}[0-9]{2}")))) {
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

            if (!(regex_match(meca, std::regex("2[0-9]{8}")))) {
                log_text = LogMessage(
                        std::string("Error Adding Student: Invalid Input MECANUMBER (StudentID) " + meca));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_match(uc, std::regex("[A-Z]{1}[.]{1}[A-Z]{3}[0-9]{3}")))) {
                log_text = LogMessage(std::string("Error Adding Student: Invalid Input UC (UcID) " + uc));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_match(turma, std::regex("[1-5]{1}[A-Z]{4}[0-9]{2}")))) {
                log_text = LogMessage(std::string("Error Adding Student: Invalid Input Class (ClassID) " + turma));
                log.push_back(log_text);
                error = true;
            }

            //can't be over 99 students in a class
            if (!(regex_match(cap, std::regex("[1-9]{1}[0-9]{0,1}")))) {
                log_text = LogMessage(std::string(
                        "Error Adding Student: Invalid Input Cap either number is to big or not recognised Input: " +
                        cap));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_match(balance, std::regex("[yn]{1}")))) {
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
                    input << "Error Adding Student: Student with " << meca << " already inside a Class "
                          << "at UC: " << uc << ". A student can't have more then one class at the same UC!";
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
                        if (!CheckBalance(m, uc, temp_turma) && balance == "n") {
                            ostringstream input;
                            input << "Error Adding Student: For input meca: " << meca << " class: " << turma << " Uc: " << uc <<" Unbalance detected and user said to respect it";
                            log_text = LogMessage(input.str());
                            log.push_back(log_text);
                        }
                        //if there is an unbalance and want to ignore it
                        else if (!CheckBalance(m, uc, temp_turma) && balance == "y") {
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
                        else if ((CheckBalance(m, uc, temp_turma) && balance == "n") || (CheckBalance(m, uc, temp_turma) && balance == "y")) {
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

            if (!(regex_match(meca, std::regex("2[0-9]{8}")))) {
                log_text = LogMessage(
                        std::string("Error Altering Student: Invalid Input MECANUMBER (StudentID) " + meca));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_match(uc, std::regex("[A-Z]{1}[.]{1}[A-Z]{3}[0-9]{3}")))) {
                log_text = LogMessage(std::string("Error Altering Student: Invalid Input UC (UcID) " + uc));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_match(turma, std::regex("[1-5]{1}[A-Z]{4}[0-9]{2}")))) {
                log_text = LogMessage(std::string("Error Altering Student: Invalid Input Class (ClassID) " + turma));
                log.push_back(log_text);
                error = true;
            }

            //can't be over 99 students in a class
            if (!(regex_match(cap, std::regex("[1-9]{1}[0-9]{0,1}")))) {
                log_text = LogMessage(std::string(
                        "Error Altering Student: Invalid Input Cap either number is to big or not recognised Input: " +
                        cap));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_match(balance, std::regex("[yn]{1}")))) {
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
                        if (!CheckBalance(m, uc, enter_turm, leaving_turm) && balance == "n") {
                            ostringstream input;
                            input << "Error Altering Student: For input meca: " << meca << " class: " << turma
                                  << " Uc: " << uc << " Unbalance detected and user said to respect it";
                            log_text = LogMessage(input.str());
                            log.push_back(log_text);
                        }
                        //if there is an unbalance and user want to ignore it
                        else if (!CheckBalance(m, uc, enter_turm, leaving_turm) && balance == "y") {
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
                        else if ((CheckBalance(m, uc, enter_turm, leaving_turm) && balance == "n") || (CheckBalance(m, uc, enter_turm, leaving_turm) && balance == "y")) {
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