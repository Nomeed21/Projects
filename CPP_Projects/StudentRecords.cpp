#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#define MAX 5
using namespace std;

struct Records{
    string name;
    int quiz1, quiz2, quiz3;

    Records(){
        name = "";
        quiz1, quiz2, quiz3 = 0;
    }
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
    void delRecord(string nm, bool isCorrect = true);
    int locate(string nm);
    void display();
    void updateRecord(string nm);
    void search(string nm);
    int locatePos(string nm);
    void save();
    void retrieve();
    int menu();
};


int main(){
    MyClass person;
    person.retrieve();
    while (1){
        Records data;
        switch(person.menu()){
            case 1:
                cout << "Enter Name: ";
                getline(cin, data.name);
                cout << "Enter quiz 1: " ;
                cin >> data.quiz1;
                cout << "Enter quiz 2: ";
                cin >> data.quiz2;
                cout << "Enter quiz 3: ";
                cin >> data.quiz3;
                cin.ignore();

                person.addRecord(data);
                break;

            case 2:
            cout << "Enter Name: ";
            cin >> data.name;

            person.delRecord(data.name);
            break; 

            case 3:
            cout << "Enter Name: ";
            cin >> data.name;
            person.updateRecord(data.name);
            break;

            case 4:
            person.display();
            break;

            case 5:
            person.save();
            exit(0);

        }
    }

    return 0;
}

int MyClass::menu(){
    system("cls");
    int choice;
    cout << "MENU" << endl   
        << "1. Add Record" << endl
        << "2. Del Record" << endl
        << "3. Update Record" << endl
        << "4. Display" << endl
        << "5. Exit & Save" << endl
        << "Select number: ";
        cin >> choice;
        cin.ignore();
        return choice;
}

void MyClass::addRecord(Records data, bool isNew){
    if (isFull()){
        cout<<"Record Full!" << endl;
        system("pause");
    }
    else{
        string choice;
        if(locate(data.name) == -1){
            if(isNew){
                system("cls");
                cout << left << setw(10) << "Name: "
                    << right << setw(10) << data.name << endl
                    << left << setw(10) << "Quiz 1: " << right << setw(10) << data.quiz1 << endl
                    << left << setw(10) << "Quiz 2: " << right << setw(10) << data.quiz2 << endl
                    << left << setw(10) << "Quiz 3: " << right << setw(10) << data.quiz3 << endl;

            
                cout << "confirm Saving?";
                getline(cin, choice);
            }
            else{
                last++;
                int p = locatePos(data.name);
                for (int i = last-1 ; i >= p; i--){
                    student[i+1] = student[i];
                }
                student[p] = data;
            }
            if ((choice == "Yes" || choice == "yes" || choice == "ye" || choice == "y")){
                last++;
                int p = locatePos(data.name);
                for (int i = last-1 ; i >= p; i--){
                    student[i+1] = student[i];
                }
                student[p] = data;
                cout <<"Saved successfully" << endl;
                system("pause");
                system("cls");
            }
        
        }
        else{
            cout << "Duplicate found" << endl;
            system("pause");
        }
    }
}

void MyClass::delRecord(string nm, bool isCorrect){
    if (isEmpty()){
        cout << "Record Empty" <<endl;
        system("pause");
    }
    else{
        if (locate(nm) == -1){
            cout << "Name not found"<< endl;
            system("pause");
        }
        else {
            int p = locate(nm);
            for (int i = p; i<last; i++){
                student[i] = student[i+1];
            }
            last--;

            if (isCorrect){
                cout << nm << " Successfully deleted" << endl;
                system("pause");
                system("cls");
            }
            
        }
    }
}

void MyClass::updateRecord(string nm){
    if(isEmpty()){
        cout << "Record is empty..." << endl;
        system("pause");
    }
    else{
        int index = locate(nm);
        if (index == -1){
            cout << "Name not found" << endl;
            system("pause");
        }
        else{
            while(true){
                int choice, newGrade;
                system("cls");
                
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
                    << "Enter your choice: ";
                cin >> choice;
                
                cout << "Enter new grade: ";
                cin >> newGrade;
                cin.ignore();

                switch(choice){
                    case 1:
                        student[index].quiz1 = newGrade;
                        break;
                    case 2:
                        student[index].quiz2 = newGrade;
                        break;
                    case 3:
                        student[index].quiz3 = newGrade;
                        break;
                    case 4:
                        return;
                }
             }
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
}
void MyClass::retrieve(){
    ifstream fp("Records.csv");
    string lineStr;

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
int MyClass::locate(string nm){
    for (int i = 0; i <= last; i++){
        if (student[i].name == nm) return i;
    }
    return -1;
}
int MyClass::locatePos(string nm){
    int i;
    for(i = 0; i<=last; i++){
        if(nm < student[i].name) return i;
    }
    return i-1;
}



void MyClass::display(){
    if (isEmpty()){
        cout<< "Record is Empty..." << endl;
        system("pause");
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
        system("pause"); 
        system("cls");
    }
}
