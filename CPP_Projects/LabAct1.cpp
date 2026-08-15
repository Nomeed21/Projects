#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#define MAX 5

using namespace std;
struct Record{
    string name;
    int quiz1, quiz2, quiz3;

    Record() {
        name = "";
        quiz1 = 0, quiz2 = 0, quiz3 = 0;
    } 

    Record(string nm, int q1, int q2, int q3){
        name = nm;
        quiz1 = q1;
        quiz2 = q2;
        quiz3 = q3;
    } 
};

class MyClass{
private:
    Record student[MAX];
    int last;
    bool isFull();
    bool isEmpty();
    int locatePos(string nm);
public:

    MyClass():last(-1){}
    int locate(string nm);
    void addRecord(Record data);
    void delRecord(string nm);
    void updateRecord(string nm);
    void display();
    void save();
    void retrieve();
    int menu();
    float average(Record data);
};

int main(){
    
    MyClass person;
    person.retrieve();
    while (true){
        Record data;
        
        switch(person.menu()){
            case 1:
                cout << "Enter Name: ";
                getline(cin, data.name);
                if (person.locate(data.name) > -1){
                    cout << "Duplicate Found!" << endl;
                    system("pause");
                }
                else{
                    cout << "Enter quiz 1: ";
                    cin >> data.quiz1;
                    cout << "Enter quiz 2: ";
                    cin >> data.quiz2;
                    cout << "Enter quiz 3: ";
                    cin >> data.quiz3;
                    cin.ignore();
                    person.addRecord(data);
                    system("pause");
                }
                break;

            case 2:
                cout << "Enter Name: ";
                getline(cin, data.name);
                person.delRecord(data.name);
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
void MyClass::addRecord(Record data){
    if (isFull()){
        cout << "Record full..."<< endl;
    }
    else {
        last++;
        int index = locatePos(data.name);
        for (int i = last-1; i >=index; i--){
            student[i+1] = student[i];
        }
        student[index] = data;

        system("cls");
        cout << "Name: " << right << setw(5) << student[index].name << endl
        << "Quiz 1: " << student[index].quiz1 << endl 
        << "Quiz 2: " << student[index].quiz2 << endl
        << "Quiz 3: " << student[index].quiz3 << endl 
        << "Successfully Recorded!" << endl;
    }
}

void MyClass::delRecord(string nm){
    if(isEmpty()){
        cout << "Record Empty..." << endl;
        system("pause");
    }
    else{
        int index = locate(nm);
        if (index == -1){
            cout << "Name not found..." << endl;
            system("pause");
        }
        else{
            for (int i = index; i<last; i++){
                student[i] = student[i+1];
            }
            last--;

            cout << "Record deleted" << endl;
            system("pause");
        }
    }
}

void MyClass::updateRecord(string nm){
    if (isEmpty()){
        cout << "Record empty..." << endl;
    }
    else{
        if (locate(nm) == -1){
            cout << "Name not found..." << endl;
        }
        else{
            int index = locate(nm);
            while(true){
                int choice, grade;
                system("cls");
                cout << "Name: " << right << setw(5) << student[index].name << endl
                << "Quiz 1: " << student[index].quiz1 << endl 
                << "Quiz 2: " << student[index].quiz2 << endl
                << "Quiz 3: " << student[index].quiz3 << endl
                << "Average: " << average(student[index]);

                cout << "UPDATE MENU" << endl
                << "[1] Quiz 1" << endl 
                << "[2] Quiz 2 " << endl
                << "[3] Quiz 3" << endl 
                <<"[4] Exit" << endl
                << "Choose what to change" << endl;
                cin >> choice;
                switch(choice){
                    case 1:
                        cout << "Enter new grade: ";
                        cin >> grade;
                        student[index].quiz1 = grade;
                        break;
                    
                    case 2:
                        cout << "Enter new grade: ";
                        cin >> grade;
                        student[index].quiz2 = grade;
                        break;
                    
                    case 3:
                        cout << "Enter new grade: ";
                        cin >> grade;
                        student[index].quiz3 = grade;
                        break;
                    
                    case 4:
                        return;
                    
                    default:
                        cout << "Invalid choice!!" << endl;
                }
                


            }
            
        }
    }
}
void MyClass::display(){
    if (isEmpty()){
        cout << "Nothing to display.." << endl;
    }
    else{
        cout << left << setw(5) << "No. "
        << left << setw(5) << "Name "
        << right << setw(10) << "Quiz 1 "
        << right << setw(10) << "Quiz 2 " 
        << right << setw(10) << "Quiz 3 "
        << right << setw(10) << "Average "
        << right << setw(10) << "Remarks" << endl;
        for (int i = 0; i <=last; i++){
            cout << left << setw(5) << i+1
            << left << setw(5) << student[i].name
            << right << setw(10) << student[i].quiz1
            << right << setw(10) << student[i].quiz2 
            << right << setw(10) << student[i].quiz3 
            << right << setw(10) << average(student[i])
            << right << setw(10) << fixed << setprecision(2) << (average(student[i])>=75? "Passed" : "Failed") << endl;
        } 
    }
}

void MyClass::save(){
    ofstream fp("Records.csv");
    if (fp.fail()){
        cout << "File Error " << endl;
        system("pause");
    }
    else{
        for(int i = 0; i<= last; i++){
            fp << student[i].name << ',' << student[i].quiz1 << ',' << student[i].quiz2 << ',' << student[i].quiz3 << endl;
        }
    }
    fp.close();
}

void MyClass::retrieve(){
    ifstream fp("Records.csv");
    string lineStr;

    if(fp.fail()){
        cout << "File Error" << endl;
        system("pause");
        return;
    }
    while(getline(fp, lineStr)){
        stringstream ss(lineStr);
        Record data;
        string ss1, ss2, ss3;

        if(getline(ss, data.name, ',') && getline(ss, ss1, ',') && getline(ss, ss2, ',') && getline(ss, ss3)){
            data.quiz1 = stoi(ss1);
            data.quiz2 = stoi(ss2);
            data.quiz3 = stoi(ss3);
            
            
            if(!data.name.empty()){
                addRecord(data);
            }
        }

        
    }
    fp.close();
}

int MyClass::locate(string nm){
    for (int i = 0 ; i<= last; i++){
        if (student[i].name == nm) return i;
    }
    return -1;
}

int MyClass::locatePos(string nm){
    for (int i = 0; i<=last; i++){
        if (student[i].name > nm) return i;
    }
    return last;
}

bool MyClass::isEmpty(){
    return last == -1;
}

bool MyClass::isFull(){
    return last == MAX -1;
}

int MyClass::menu(){
    system("cls");
    int choice;
    cout << "MENU" << endl
    << "[1] Add Record "<< endl
    << "[2] Delete Record "<< endl
    << "[3] Update Record " << endl
    << "[4] Display Records" << endl
    << "[5] Exit & Save" << endl
    << "Input your choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

float MyClass::average(Record data){
    return (float) (data.quiz1 + data.quiz2 + data.quiz3)/ 3.0;
}