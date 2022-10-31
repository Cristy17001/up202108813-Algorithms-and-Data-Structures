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