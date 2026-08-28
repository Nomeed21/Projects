#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#define MAX 5

using namespace std;

struct LINK{
    string name;
    int quiz1, quiz2, quiz3;
    LINK *next;
    LINK *prev;

    LINK() {
        name = "";
        quiz1 = 0;
        quiz2 = 0;
        quiz3 = 0;
        next = nullptr;
        prev = nullptr;
    }

    LINK(string nm, int q1, int q2, int q3){
        name = nm;
        quiz1 = q1;
        quiz2 = q2;
        quiz3 = q3;
        next = nullptr;
        prev = nullptr;
    }
};


class MyClass{
private:
    LINK *head;
    LINK *tail;

    bool isFull();
    bool isEmpty();
    LINK* locatePos(string nm);

public:
    MyClass():head(nullptr), tail(nullptr){}

    LINK* locate(string nm);
    void addRecord(LINK data);
    void delRecord(string nm);
    void updateRecord(string nm);
    void display();
    void save();
    void retrieve();
    int menu();
    float average(LINK data);
};


int main(){

    MyClass person;
    person.retrieve();

    while (true){
        LINK data;

        switch(person.menu()){

            case 1:
                cout << "Enter Name: ";
                getline(cin, data.name);

                cout << "Enter quiz 1: ";
                cin >> data.quiz1;

                cout << "Enter quiz 2: ";
                cin >> data.quiz2;

                cout << "Enter quiz 3: ";
                cin >> data.quiz3;

                cin.ignore();

                person.addRecord(data);
                system("pause");
                break;

            case 2:
                cout << "Enter Name: ";
                getline(cin, data.name);

                person.delRecord(data.name);
                system("pause");
                break;

            case 3:
                cout << "Enter Name: ";
                getline(cin, data.name);

                person.updateRecord(data.name);
                system("pause");
                break;

            case 4:
                person.display();
                system("pause");
                break;

            case 5:
                person.save();
                exit(0);
                break;

            default:
                cout << "Invalid choice!! " << endl;
                system("pause");
        }
    }

    return 0;
}


void MyClass::addRecord(LINK data){

    if (isFull()){
        cout << "Record is full.." << endl;
        return;
    }

    if (locate(data.name) != nullptr){
        cout << "Name already exists.." << endl;
        return;
    }

    LINK *p, *q, *newNode;

    p = q = head;
    newNode = new LINK(data);

    p = locatePos(data.name);

    if (p == head){
        newNode->next = head;
        newNode->prev = nullptr;

        if (head != nullptr){
            head->prev = newNode;
        }

        head = newNode;

        if (tail == nullptr){
            tail = newNode;
        }
    }
    else{
        while(q != nullptr && q->next != p){
            q = q->next;
        }

        q->next = newNode;
        newNode->prev = q;
        newNode->next = p;

        if (p != nullptr){
            p->prev = newNode;
        }
        else{
            tail = newNode;
        }
    }

    cout << "Record added successfully.." << endl;
}


void MyClass::delRecord(string nm){

    LINK *p = locate(nm);

    if (p == nullptr){
        cout << "Name not found.." << endl;
        return;
    }

    if (p->prev != nullptr){
        p->prev->next = p->next;
    }
    else{
        head = p->next;
    }

    if (p->next != nullptr){
        p->next->prev = p->prev;
    }
    else{
        tail = p->prev;
    }

    delete p;

    cout << "Record deleted successfully.." << endl;
}


void MyClass::updateRecord(string nm){

    LINK *p;

    p = locate(nm);

    if (p == nullptr){
        cout << "Name not found.." << endl;
        return;
    }

    while(true){

        int choice, grade;

        system("cls");

        cout << "Name: " << right << setw(5) << p->name << endl
        << "Quiz 1: " << p->quiz1 << endl
        << "Quiz 2: " << p->quiz2 << endl
        << "Quiz 3: " << p->quiz3 << endl
        << "Average: " << fixed << setprecision(2) << average(*p) << endl
        << endl;

        cout << "UPDATE MENU" << endl
        << "[1] Quiz 1" << endl
        << "[2] Quiz 2" << endl
        << "[3] Quiz 3" << endl
        << "[4] Exit" << endl
        << "Choose what to change: ";

        cin >> choice;

        switch(choice){

            case 1:
                cout << "Enter new grade: ";
                cin >> grade;
                p->quiz1 = grade;
                break;

            case 2:
                cout << "Enter new grade: ";
                cin >> grade;
                p->quiz2 = grade;
                break;

            case 3:
                cout << "Enter new grade: ";
                cin >> grade;
                p->quiz3 = grade;
                break;

            case 4:
                return;

            default:
                cout << "Invalid choice!!" << endl;
                system("pause");
        }
    }
}


void MyClass::display(){

    if (isEmpty()){
        cout << "Nothing to display.." << endl;
        return;
    }

    LINK *p = head;

    cout << left << setw(5) << "No."
    << left << setw(20) << "Name"
    << right << setw(10) << "Quiz 1"
    << right << setw(10) << "Quiz 2"
    << right << setw(10) << "Quiz 3"
    << right << setw(10) << "Average"
    << right << setw(10) << "Remarks"
    << endl;


    int i = 0;

    while (p != nullptr){

        float ave = average(*p);

        cout << left << setw(5) << i + 1
        << left << setw(20) << p->name
        << right << setw(10) << p->quiz1
        << right << setw(10) << p->quiz2
        << right << setw(10) << p->quiz3
        << right << setw(10) << fixed << setprecision(2) << ave
        << right << setw(10) << (ave >= 75 ? "Passed" : "Failed")
        << endl;

        i++;
        p = p->next;
    }
}


void MyClass::save(){

    ofstream fp("Records.csv");

    if (fp.fail()){
        cout << "File Error" << endl;
        return;
    }

    LINK *p = head;

    while(p != nullptr){

        fp << p->name << ','
           << p->quiz1 << ','
           << p->quiz2 << ','
           << p->quiz3 << endl;

        p = p->next;
    }

    fp.close();

    cout << "Records saved successfully.." << endl;
}


void MyClass::retrieve(){

    ifstream fp("Records.csv");
    string lineStr;

    if(fp.fail()){
        return;
    }

    while(getline(fp, lineStr)){

        stringstream ss(lineStr);
        LINK data;

        string ss1, ss2, ss3;

        if(getline(ss, data.name, ',') &&
           getline(ss, ss1, ',') &&
           getline(ss, ss2, ',') &&
           getline(ss, ss3)){
                data.quiz1 = stoi(ss1);
                data.quiz2 = stoi(ss2);
                data.quiz3 = stoi(ss3);

                if(!data.name.empty()){
                    addRecord(data);
                }
                cout << "Invalid record found in file.." << endl;
        }
    }

    fp.close();
}


LINK* MyClass::locate(string nm){

    LINK *p;

    p = head;

    while(p != nullptr && p->name != nm){
        p = p->next;
    }

    return p;
}


LINK* MyClass::locatePos(string nm){

    LINK *p;

    p = head;

    while(p != nullptr && p->name < nm){
        p = p->next;
    }

    return p;
}


bool MyClass::isEmpty(){

    return head == nullptr;
}


bool MyClass::isFull(){

    LINK *p = head;
    int count = 0;

    while(p != nullptr){
        count++;
        p = p->next;
    }

    return count >= MAX;
}


int MyClass::menu(){

    system("cls");

    int choice;

    cout << "MENU" << endl
    << "[1] Add Record " << endl
    << "[2] Delete Record " << endl
    << "[3] Update Record " << endl
    << "[4] Display Record" << endl
    << "[5] Exit & Save" << endl
    << "Input your choice: ";

    cin >> choice;
    cin.ignore();

    return choice;
}

float MyClass::average(LINK data){

    return (float)(data.quiz1 + data.quiz2 + data.quiz3) / 3.0;
}