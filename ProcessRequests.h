void ProcessRequests(std::vector<std::string>& log, Manager& m)
{
    queue<Request> requests = m.get_requests();
    while (!m.get_requests().empty())
    {

        Request request =  requests.front();
        if (request.get_type() == "Remove")
        {
            std::string meca = request.get_data()[0];
            std::string uc = request.get_data()[1];
            std::string turma = request.get_data()[2];
            std::string log_text;

            bool error = false;
            //Constrains and log write
            if (!(regex_search(meca, std::regex("2[0-9]{8}"))))
            {
                log_text = LogMessage(std::string("Error Removing Student: Invalid Input MECANUMBER (StudentID) " + meca));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(uc, std::regex("[A-Z]{1}[.]{1}[A-Z]{3}[0-9]{3}"))))
            {
                log_text = LogMessage(std::string ("Error Removing Student: Invalid Input UC (UcID) " + uc));
                log.push_back(log_text);
                error = true;
            }

            if (!(regex_search(turma, std::regex("[1-5]{1}[A-Z]{4}[0-9]{2}"))))
            {
                log_text = LogMessage(std::string("Error Removing Student: Invalid Input Class (ClassID) " + turma));
                log.push_back(log_text);
                error = true;
            }

            //if data invalid just write to log
            if (error) return;


            //Finding the student in LogN time using predicate in a lambda function
            std::set<Student> students = m.get_students();
            std::list<UcTurma> turmas;

            auto it_stud = find_if(students.begin(), students.end(), [&meca](const Student& stud) -> bool { return stud.get_mecaNumber() == meca;});

            //if student was found
            if (!(it_stud == students.end())) {turmas = it_stud->get_turm();}

            //if student couldn't be found
            if (turmas.empty()){
                ostringstream input;
                input << "Error Removing Student: Couldn't find Student with Meca: " << meca << " at UC: " << uc << " in Class: " << turma;
                log_text = LogMessage(input.str());
                log.push_back(log_text);
                return;
            }
        }
    }
}