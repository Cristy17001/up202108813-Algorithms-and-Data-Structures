void addStudent(Manager& m)
{
    string uc, turma, meca, cap, balance;

    cout << "Example: 202030247, 202022512, 202050902, 202023362 ..." << endl;
    cout << "Introduce the MecaNumber of the student: ";
    cin >> meca; cout << endl;

    cout << "Example: L.EIC001, L.EIC002, L.EIC003, L.EIC004 ..." << endl;
    cout << "Introduce UC: ";
    cin >> uc; cout << endl;

    cout << "Example: 1LEIC01, 1LEIC02, 2LEIC01, 3LEIC01 ..." << endl;
    cout << "Introduce Class: ";
    cin >> turma; cout << endl;

    cout << "Example: 12, 22, 30, 31 ...";
    cout << "How many students should a class be able to have?" << endl;
    cin >> cap; cout << endl;

    cout << "In case this operation creates unbalance between the class's of that UC you want it to do it anyway?(Y/N)" << endl;
    cin >> balance; cout << endl;


    cout << "Your Request will be processed when you exit the program, every change made will be on the logfile" << endl;

    vector<string> data = {meca, uc, turma, cap, balance};
    Request r = Request("Add", data);
    m.add_request(r);
}