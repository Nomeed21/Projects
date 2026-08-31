#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

#define MAX 5
using namespace std;

void pause(){
    #ifdef _WIN32
        system("pause");
    #else 
        cout << "Press any key to continue...";
        cin.ignore();
    #endif
}
void clearScreen(){
    #ifdef _WIN32
        system("cls");
    
    #else
        cout << "\033[2J\033[H";
    #endif
}
struct Records{
    string name;
    int quiz1, quiz2, quiz3;

    Records(): name(""), quiz1(0), quiz2(0), quiz3(0){} 
    Records(string nm, int q1, int q2, int q3){
        name = nm;
        quiz1 = q1;
        quiz2 = q2;
        quiz3 = q3;
    }
};
class MyClass{
    private:
    Records student[MAX];
    int last;
    bool isEmpty();
    bool isFull();

    public:
    MyClass():last(-1){};
    void addRecord(Records data, bool isNew = true);
    void delRecord(const string &nm, bool isCorrect = true);
    int locate(const string &nm);
    void display();
    void updateRecord(const string &nm);
    void searchRecord(const string &nm);
    int locatePos(const string &nm);
    void save();
    void retrieve();
    int menu();
};


int main(){
    MyClass person;
    person.retrieve();
    bool running = true;
    while (running){
        Records data;
        switch(person.menu()){
            case 1:
                cout << "Enter Name: ";
                getline(cin, data.name);
                if (person.locate(data.name) > -1){
                    cout << "Duplicate Found" << endl;
                    pause();
                }
                else{
                    cout << "Enter quiz 1: " ;
                    cin >> data.quiz1;
                    cout << "Enter quiz 2: ";
                    cin >> data.quiz2;
                    cout << "Enter quiz 3: ";
                    cin >> data.quiz3;
                    cin.ignore();

                    person.addRecord(data);
                    person.save();
                }
                break;
                

            case 2:
                cout << "Enter Name: ";
                getline(cin, data.name);
                person.delRecord(data.name);
                person.save();
                break; 

            case 3:
                cout << "Enter Name: ";
                getline(cin, data.name);
                person.updateRecord(data.name);
                person.save();
                break;

            case 4:
                person.display();
                break;

            case 5:
                cout << "Enter Name: ";
                getline(cin, data.name);
                person.searchRecord(data.name);
                break; 

            case 6:
                running = false;
                exit(0);
                break;

            default:
                cout << "Invalid choice!!" << endl;
                pause();

        }
    }

    return 0;
}



int MyClass::menu(){
    clearScreen();
    int choice;
    cout << "MENU" << endl   
        << "1. Add Record" << endl
        << "2. Del Record" << endl
        << "3. Update Record" << endl
        << "4. Display" << endl
        << "5. Search Record" << endl
        << "6. Exit & Save" << endl
        << "Select number: ";
        cin >> choice;
        cin.ignore();
        return choice;
}

void MyClass::addRecord(Records data, bool isNew){
    if (isFull()){
        cout<<"Record Full!" << endl;
        pause();
    }
    else{
        string choice;
        if(isNew){
                clearScreen();
                cout << left << setw(10) << "Name: "
                    << right << setw(10) << data.name << endl
                    << left << setw(10) << "Quiz 1: " << right << setw(10) << data.quiz1 << endl
                    << left << setw(10) << "Quiz 2: " << right << setw(10) << data.quiz2 << endl
                    << left << setw(10) << "Quiz 3: " << right << setw(10) << data.quiz3 << endl;

            
                cout << "confirm Saving?: ";
                getline(cin, choice);
                cin.ignore();
        }
        if ((choice == "YES" || choice == "yes") || !isNew){
                last++;
                int p = locatePos(data.name)-1;
                for (int i = last-1 ; i >= p; i--){
                    student[i+1] = student[i];
                }
                student[p] = data;
                if (isNew){
                    cout <<"Saved successfully" << endl;
                    pause();
                    clearScreen();
                }
        }
    }
}
void MyClass::delRecord(const string &nm, bool isCorrect){
    if (isEmpty()){
        cout << "Record Empty" <<endl;
        pause();
    }
    else{
        if (locate(nm) == -1){
            cout << "Name not found"<< endl;
            pause();
        }
        else {
            int p = locate(nm);
            for (int i = p; i<last; i++){
                student[i] = student[i+1];
            }
            last--;

            if (isCorrect){
                cout << nm << " Successfully deleted" << endl;
                pause();
                clearScreen();
            }
            
        }
    }
}
void MyClass::updateRecord(const string &nm){
    if(isEmpty()){
        cout << "Record is empty..." << endl;
        pause();
    }
    else{
        int index = locate(nm);
        if (index == -1){
            cout << "Name not found" << endl;
            pause();
        }
        else{
            while(true){
                int choice, newGrade;
                clearScreen();
                
                float average = (float)(student[index].quiz1 + student[index].quiz2 + student[index].quiz3) / 3;
                cout << "Name: " << right << setw(10) << student[index].name << endl 
                    << "Quiz 1: " << right << setw(10) << student[index].quiz1 << endl
                    << "Quiz 2: " << right << setw(10) << student[index].quiz2 << endl
                    << "Quiz 3: " << right << setw(10) << student[index].quiz3 << endl
                    << "Average: " << right << setw(10) << fixed << setprecision(2) << average << endl;

                cout << "MENU" << endl
                    << "[1] Quiz 1" << endl
                    << "[2] Quiz 2" << endl
                    << "[3] Quiz 3" << endl
                    << "[4] Exit" << endl
                    << "Enter your choice: ";
                cin >> choice;
                
                

                switch(choice){
                    case 1:
                        cout << "Enter new grade: ";
                        cin >> newGrade;
                        cin.ignore();
                        student[index].quiz1 = newGrade;
                        break;
                    case 2:
                        cout << "Enter new grade: ";
                        cin >> newGrade;
                        cin.ignore();
                        student[index].quiz2 = newGrade;
                        break;
                    case 3:
                        cout << "Enter new grade: ";
                        cin >> newGrade;
                        cin.ignore();
                        student[index].quiz3 = newGrade;
                        break;
                    case 4:
                        save();
                        return;
                        break;
                    default:
                        cout << "Invalid choice!!" << endl;
                        pause();
                }
             }
        }
    }
}
void MyClass::searchRecord(const string &nm){
    if(isEmpty()){
        cout << "Record Empty..." << endl;
        pause();
    }
    else{
        int index = locate(nm);
        if(index == -1){
            cout << "Name not found!!" << endl;
            pause();
        }
        else{
            float average  = (float)(student[index].quiz1 + student[index].quiz2 + student[index].quiz3) / 3;
            clearScreen();
            cout << "Name: " << right << setw(5) << student[index].name << endl
                << "Quiz 1: "<< right << setw(4) << student[index].quiz1 << endl 
                << "Quiz 2: " << right << setw(4) << student[index].quiz2 << endl 
                << "Quiz 3: " << right << setw(4) << student[index].quiz3 << endl 
                << "Average: " << right << setw(4) << fixed << setprecision(2) << average << endl
                << (average>=75? "Passed":"Failed!!") << endl;
            
            pause();

        }
    }
}

void MyClass::save(){

    ofstream fp("Records.csv");
    if(fp.fail()){
        cout << "File Error" <<endl;
        return;
    }
    else{
        for (int i = 0; i <= last; i++){
            fp << student[i].name << "," << student[i].quiz1 << "," << student[i].quiz2 << "," << student[i].quiz3 << endl;
        }
    }
    fp.close();
}
void MyClass::retrieve(){
    ifstream fp("Records.csv");
    string lineStr;

    if(fp.fail()){
        cout << "Error Finding File" << endl;
        pause();
    }
    while (getline(fp, lineStr)){
        stringstream ss(lineStr);

        Records data;
        string ss1, ss2, ss3;
        

        if (getline(ss, data.name, ',') && getline(ss, ss1, ',') && getline(ss, ss2, ',') && getline(ss, ss3) ){
            data.quiz1 = stoi(ss1);
            data.quiz2 = stoi(ss2);
            data.quiz3 = stoi(ss3);

            if(!data.name.empty()){
                addRecord(data, false);
            }
        }
    }
    fp.close();
}

bool MyClass::isFull(){
    return last == MAX -1;
}
bool MyClass::isEmpty(){
    return last == -1;
}
int MyClass::locate(const string &nm){
    for (int i = 0; i <= last; i++){
        if (student[i].name == nm) return i;
    }
    return -1;
}
int MyClass::locatePos(const string &nm){
    for(int i  = 0; i<=last; i++){
        if(nm < student[i].name) return i;
    }
    return last + 1;
}



void MyClass::display(){
    if (isEmpty()){
        cout<< "Record is Empty..." << endl;
        pause();
    }   
    else{
        cout << left << setw(5) << "No." << " "
        << left << setw(10) << "Name" << " "
        << right << setw(5) << "Quiz1" << " "
        << right << setw(5) << "Quiz2" << " "
        << right << setw(5) << "Quiz3" << " "
        << right << setw(8) << "Average" << " "
        << right << setw(8) << "Remarks" << endl;
        for (int i = 0; i<=last; i++){
            float ave = (student[i].quiz1 + student[i].quiz2 + student[i].quiz3) / 3.0;
            cout << left << setw(5) << i+1 << " "
            << left << setw(10) << student[i].name << " "
            << right << setw(5) << student[i].quiz1 << " "
            << right << setw(5) << student[i].quiz2 << " "
            << right << setw(5) << student[i].quiz3 << " "
            << right << setw(8) <<fixed << setprecision(2)<< ave << " "
            << right << setw(8) << (ave >= 75? "Passed" : "Failed") << endl;;
        }
        pause(); 
        clearScreen();
    }
}
