void loadUcs(Manager& m)
{
    string FILENAME = "classes_per_uc.csv";
    list<UcTurma> all_ucs;

    ifstream file;
    string file_text;
    file.open(FILENAME);


    //Eliminate first line
    getline(file, file_text);

    while(!file.eof()) {

        getline(file, file_text, ',');
        string ucCode = file_text;

        getline(file, file_text);
        string classCode = file_text;

        if (!classCode.empty()) {
            UcTurma aux = UcTurma(ucCode, classCode);
            m.add_UC(aux);
        }
    }
}
