void removeStudent(Manager& m)
{
    string uc, turma, meca;

    cout << "Example: 202030247, 202022512, 202050902, 202023362 ..." << endl;
    cout << "Introduce the MecaNumber of the student: ";
    cin >> meca; cout << endl;

    cout << "Example: L.EIC001, L.EIC002, L.EIC003, L.EIC004 ..." << endl;
    cout << "Introduce UC: ";
    cin >> uc; cout << endl;

    cout << "Example: 1LEIC01, 1LEIC02, 2LEIC01, 3LEIC01 ..." << endl;
    cout << "Introduce Class: ";
    cin >> turma; cout << endl;

    cout << "Your Request will be processed when you exit the program, every change made will be on the logfile" << endl;

    vector<string> data = {meca, uc, turma};
    Request r = Request("Remove", data);
    m.add_request(r);
}

