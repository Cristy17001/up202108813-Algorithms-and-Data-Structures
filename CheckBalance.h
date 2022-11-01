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