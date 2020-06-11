//პროგრამის დასაწყისი


#include "platypus.h" //კლასის ბიბლიოთეკის დაკავშირება
using namespace std;


/*დამატებითი*/

//ვამოწმებთ თუ რიცხვი მთელია
int InputInt(int&);

/**/

/*მთავარი ფუნქციები*/

//ვქმნით ახალ პლატიპუს
void CreateNewPL(vector<platypus>& animals);
//ვქმნით შემთხვევით ახალ პლატიპუს
void CreateRandomPL(vector<platypus>& animals);
//ვირჩევთ პლატიპუს
void SelectPL(vector<platypus>& animals);
//პროგრამის ინფორმაცია
void Info();

/**/

/* SelectPL-ს დამხმარე ფუნქციები*/

void Fight(vector<platypus>& animals, platypus& pl, int selected); //სხვა პლატიპუსთან ჩხუბი
void ChangePL(platypus& pl); //პლატიპუსის შეცვლა
void hatchCreate(platypus& pl, vector<platypus>& animals); //ახალშობილის შექმნა

/**/



//Main ფუნქცია
int main() {
    srand((unsigned int)time(NULL));
    int Input;
    vector<platypus> animals;
    cout << BOLDGREEN << "/***/ Welcome in platypus care simulator! /****/\n\n" << RESET; //მისალმება

    //მთავარი მენიუ
    while (true) {
        cout << GREEN << "/**/MAIN MENU/**/\n \n[1] Create New Platypus\n[2] Make Random Platypus\n[3] Select Platypus\n[4] Info\n[5] Exit From Program\n" << RESET;
        InputInt(Input);
        while (Input <= 0 || Input >= 6) {
            cout << BOLDRED << "[ERROR]: Input between 1-5 ! \n" << RESET;
            InputInt(Input);
        }
        switch (Input) {
        case 1: CreateNewPL(animals); break; // ახალი პლატიპუსი
        case 2: CreateRandomPL(animals); break; // შემთხვევითი პლატიპუსი
        case 3: SelectPL(animals); break; // პლატიპუსის არჩევა
        case 4: Info(); break; // პროგრამის ინფორმაცია
        case 5: return 0; break; // პროგრამიდან გამოსვლა
        default: break;
        }
    }

}

/*დამატებითი*/
int InputInt(int& some) {
    cin >> some;
    while (!cin.good())
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << BOLDRED << "[ERROR]: Enter only integer!\n" << RESET;
        cin >> some;
    }
    return some;
}
/*****/

/*მთავარი ფუნქციები*/


//ვქმნით ახალ პლატიპუს
void CreateNewPL(vector<platypus>& animals) {
    platypus* pn = new(nothrow)platypus;
    cin >> *pn;
    animals.push_back(*pn);
    delete pn;

}

//ვქმნით შემთხვევით ახალ პლატიპუს
void CreateRandomPL(vector<platypus>& animals) {
    platypus *pn = new (nothrow) platypus;
    pn->setAlive(true);
    animals.push_back(*pn);
    cout << BOLDYELLOW << "[INFO]: Platypus created succesful!\n" << RESET;
    delete pn;
}

//ვირჩევთ პლატიპუს
void SelectPL(vector<platypus>& animals) {
    //თუ სია ცარიელია
    if (animals.size() == 0) {
        cout << BOLDRED << "[ERROR]: platypus list is empty! \n" << RESET;
        return;
    }
    cout << BLUE;
    //სიის დაბეჭდვა
    for (int i = 0; i < animals.size(); i++) {
        cout << "[" << i << "]" << " " << animals[i].getName() << endl;
    }
    cout << RESET;
    int Input;
    InputInt(Input);
    //თუ არასწორად იყო არჩეული
    while (Input < 0 || Input >= animals.size()) {
        cout << BOLDRED << "[ERROR]: Such platypus not finded! \n" << RESET;
        InputInt(Input);
    }
    platypus* pl = &animals.at(Input);

    //არჩეული პლატიპუსის მართვა
    while (true) {
        int Input2;
        cout << GREEN << "/*/MENU/*/\n \n[1] Info\n[2] Eat\n[3] Add Month\n[4] Fight\n[5] Change \n[6] Hatch \n[7] Delete\n[8] Back to Main Menu\n" << RESET;
        InputInt(Input2);
        while (Input2 < 1 || Input2 > 8) {
            cout << BOLDRED << "[ERROR]: Input between 1-8! \n" << RESET;
            InputInt(Input2);
        }
        switch (Input2) {
        case 1: cout << *pl << endl;  break; //დაბეჭდვა
        case 2: pl->eat(); break; //ჭამა
        case 3: pl->age_me(); break; //ასაკის მომატება
        case 4: Fight(animals, *pl, Input); break; //ჩხუბი
        case 5: ChangePL(*pl); break; //შეცვლა
        case 6: hatchCreate(*pl, animals); break; //ახალშობილის დამატება
        case 7: cout << BOLDRED << "[INFO]: You delete platypus! \n" << RESET; animals.erase(animals.begin() + Input); return;  break;
        case 8:  return;  break;
        default: break;
        }
        cout << endl << RESET;
    }


}

//ინფორმაცია
void Info() {
    cout << BOLDBLUE << "[INFO]: Program by Dimitri Kvirikashvili.\n" << RESET;
}

/*!!!!!!*/

/* SelectPL-ს დამხმარე ფუნქციები*/

//ვცვლით პლატიპუს
void ChangePL(platypus& pl) {
    int Input;
    while (true) {
        cout << YELLOW << "\n \n[1] Name\n[2] Weight\n[3] Age\n[4] Gender\n[5] Alive\n[6] Mutant\n[7] Back\n" << RESET;
        InputInt(Input);
        while (Input < 1 || Input > 7) {
            cout << BOLDRED << "[ERROR]: Input between 1-7! \n" << RESET;
            InputInt(Input);
        }
        char* gender = new char;
        short* age = new short;
        float* weight = new float;
        string* name = new  string("M");
        bool* check = new bool[7];
        for (int i = 0; i < 7; i++) {
            if (Input - 1 == i)
                *(check + i) = true;
            else
                *(check + i) = false;
        }
        //შესამოწმებელი მასივი
        while (true) {
            //სახელის შეყვანა
            if (*check) {
                pl.setName(*name);
                if (*name == pl.getName() || *name == "getrand") {
                    *check = false;
                }
                else {
                    continue;
                }
            }
            //წონის შეყვანა
            if (*(check + 1)) {

                pl.setWeight(*weight);
                if (*weight == pl.getWeight()) {
                    *(check + 1) = false;
                }
                else {
                    continue;
                }
            }
            //ასაკის შეყვანა
            if (*(check + 2)) {
                pl.setAge(*age);
                if (*age == pl.getAge()) {
                    *(check + 2) = false;
                }
                else {
                    continue;
                }

            }
            //სქესის შეყვანა
            if (*(check + 3)) {

                pl.setGender(*gender);
                if (*gender == pl.getGender()) {
                    *(check + 2) = false;
                }
                else {
                    continue;
                }
            }
            if (*(check + 4)) {
                cout << BOLDBLUE << "[INFO]: Input 0 OR 1! \n" << RESET;
                int Input2;
                InputInt(Input2);
                while (Input2 < 0 || Input2 > 1) {
                    cout << BOLDRED << "[ERROR]: Input 0 OR 1! \n" << RESET;
                    InputInt(Input2);
                }
                pl.setAlive(Input2);

            }
            if (*(check + 5)) {
                cout << BOLDBLUE << "[INFO]: Input 0 OR 1! \n" << RESET;
                int Input2;
                InputInt(Input2);
                while (Input2 < 0 || Input2 > 1) {
                    cout << BOLDRED << "[ERROR]: Input 0 OR 1! \n" << RESET;
                    InputInt(Input2);
                }
                pl.setMutant(Input2);
            }
            if (*(check + 6)) {
                return;
                break;
            }

            if (!(*(check) && *(check + 1) && *(check + 2) && *(check + 3))) {
                cout << RED << "***Platypus has changed!***\n\n" << RESET;
                break;
            }
        }

        delete[] check;
        delete gender;
        delete age;
        delete weight;
        delete name;

    }
}

//სხვა პლატიპუსთან ჩხუბის ფუნქცია
void Fight(vector<platypus>& animals, platypus& pl, int selected) {
    if (animals.size() < 2) {
        cout << BOLDRED << "[ERROR]: Fighters list is empty! \n" << RESET;
        return;
    }
    cout << BLUE << "Fight With: ";
    //სიის დაბეჭდვა
    for (int i = 0; i < animals.size(); i++) {
        if (selected != i)
            cout << "[" << i << "]" << " " << animals[i].getName() << endl;
        else
            cout << endl;
    }
    cout << RESET;
    int Input;
    InputInt(Input);
    //თუ არასწორად იყო არჩეული
    while (Input < 0 || Input > animals.size() || Input == selected) {
        cout << BOLDRED << "[ERROR]: Such platypus not finded! \n" << RESET;
        InputInt(Input);
    }
    pl.fight(animals[Input]);

}
//ახალშობილის შექმნა
void hatchCreate(platypus& pl, vector<platypus>& animals) {
    platypus pn = pl.hatch();
    if (pn.getAlive() == true) {
        animals.push_back(pn);
        cout << BOLDBLUE << "[INFO]:Hatch Created! \n" << RESET;
    }
}
/*!!!!*/
//პროგრამის დასასრული