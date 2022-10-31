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