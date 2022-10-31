bool CheckBalance(const Manager& m, string& uc) {
    long long min = 2147483646, max = -1;
    auto students = m.get_students();
    //Iterate over every class of that uc and count the number of students in it
    for (const UcTurma& e: m.get_all_ucs()) {
        if (e.get_ucCode() == uc) {
            auto aux = e.get_classCode();
            UcTurma t = UcTurma(uc, aux);
            auto count = count_if(students.begin(), students.end(),
                             [&t](const Student &stud) -> bool {return stud.inside_turm(t);});
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