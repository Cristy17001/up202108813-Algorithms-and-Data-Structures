void loadSchedule(Manager& m)
{
    string FILENAME = "classes.csv";

    ifstream file;
    string file_text;
    file.open(FILENAME);

    vector<ClassSchedule> v;

    //Eliminate first line
    getline(file, file_text);


    while(!file.eof()) {

        getline(file, file_text, ',');
        string classCode = file_text;

        getline(file, file_text, ',');
        string ucCode = file_text;

        getline(file, file_text, ',');
        string weekDay = file_text;

        getline(file, file_text, ',');
        string hour_dur = file_text;

        double startHour = atof(hour_dur.c_str());

        getline(file, file_text, ',');
        hour_dur = file_text;

        double duration = atof(hour_dur.c_str());

        getline(file, file_text);
        string type = file_text;

        if (classCode.empty())
        {
            UcTurma u = UcTurma(ucCode, classCode);
            ClassSchedule c = ClassSchedule(u, weekDay, startHour, duration, type);
            v.push_back(c);
        }

    }
    m.set_schedule(v);
    file.close();
}


