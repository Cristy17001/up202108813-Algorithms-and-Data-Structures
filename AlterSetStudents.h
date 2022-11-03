void alterSetStudents(Manager& m) {
    string uc, turma, meca, cap, balance;
    string input_aux;
    vector<string> data;
    char choice;

    //do one time
    cout << "Example: 202030247, 202022512, 202050902, 202023362 ..." << endl;
    cout << "Introduce the MecaNumber of the student: ";
    cin >> meca; cout << endl;

    cout << "Example: L.EIC001, L.EIC002, L.EIC003, L.EIC004 ..." << endl;
    cout << "Introduce UC: ";
    cin >> uc;
    cout << endl;

    cout << "Example: 1LEIC01, 1LEIC02, 2LEIC01, 3LEIC01 ..." << endl;
    cout << "Introduce Class: ";
    cin >> turma;
    cout << endl;

    cout << "Example: 12, 22, 30, 31 ...";
    cout << "How many students should a class be able to have?" << endl;
    cin >> cap;
    cout << endl;

    cout << "In case this operation creates unbalance between the class's of that UC you want it to do it anyway?(y/n)" << endl;
    cin >> balance;
    cout << endl;

    //Add a request of type alter
    data = {meca, uc, turma, cap, balance};
    Request r = Request("Alter", data);
    m.add_request(r);

    cout << "Your Request will be processed when you exit the program, every change made will be on the logfile" << endl << endl;

    do {
        cout << "=================================================================" << '\n';
        cout << "\t\t\t\tOptions:" << "\n\n";
        cout << "Press 'c' if you want to continue altering for that given student!" << '\n';
        cout << "Press 'f' if you dont want to continue altering!" << '\n';
        cout << "=================================================================" << '\n';

        cout << endl << "Select your choice: ";
        cin >> input_aux; cout << endl;

        if (input_aux.length() > 1) {
            cout << "Error Invalid Input! Please Introduce only one character!" << endl;
            choice = '0';
        }
        else choice = input_aux[0];

        switch (choice) {
            case 'c': {
                cout << "Example: L.EIC001, L.EIC002, L.EIC003, L.EIC004 ..." << endl;
                cout << "Introduce UC: ";
                cin >> uc;
                cout << endl;

                cout << "Example: 1LEIC01, 1LEIC02, 2LEIC01, 3LEIC01 ..." << endl;
                cout << "Introduce Class: ";
                cin >> turma;
                cout << endl;

                cout << "Example: 12, 22, 30, 31 ...";
                cout << "How many students should a class be able to have?" << endl;
                cin >> cap;
                cout << endl;

                cout << "In case this operation creates unbalance between the class's of that UC you want it to do it anyway?(y/n)" << endl;
                cin >> balance;
                cout << endl;

                //Add a request of type alter
                data = {meca, uc, turma, cap, balance};
                Request r = Request("Alter", data);
                m.add_request(r);
                cout << "Your Request will be processed when you exit the program, every change made will be on the logfile" << endl;
                break;
            }
            case 'f': break;
            default: {
                if (input_aux.length() == 1) {
                    cout << endl << "Error: character not recognised please select one of the options!" << endl << endl;
                }
                choice = '0';
                break;
            }
        }

    } while (choice != 'f');

}