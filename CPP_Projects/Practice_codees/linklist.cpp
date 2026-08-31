#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;
struct Record{
    string name;
    int age;

    Record(){
        name = "";
        age = 0;
    }

    Record(string nm, int ag){
        name = nm;
        age = ag;
    }
};

struct Node{
    Record data;
    Node *next;

    Node(Record x):data(x){}
};

class Student{
    private:
    Node *head;

    public:
    Student():head(nullptr){}
    ~Student(){
        Node *p;
        while(head!=nullptr){
            p = head;
            head = head->next;
            delete(p);
        }
    }
    void addRecord(Record data);
    void delRecord(string name);
    void displayRecord();
    void save();
    void retrieve();
};


int menu();
 
int main(){
    Record r;
    Student rec;//rec is an instance of class RecordLink
    rec.retrieve();
    while (true){
            switch(menu()){
            case 1 : system("cls");cout<<"Add Mode\n";
                    cout<<"Input Name: ";
                    getline(cin, r.name);

                    cout<<"Input Age: ";cin>>r.age;
                    rec.addRecord(r);
                    system("pause");
                    break;

            case 2 : system("cls");
                    cout<<"Delete Mode\n";
                    cout<<"Input Name: ";
                    getline(cin, r.name);
                    rec.delRecord(r.name);
                    system("pause");
                    break;
            case 3 : 
                rec.displayRecord();
                system("pause");
                break;


            case 4 : 
                cout<<"\nThank you for using my program...\n";
                system("pause");
                rec.save();
                exit(0);

            default: 
            cout<<"1 to 4 only.\n";
            system("pause");
            }
    
    }
    return 0;
}


int menu(){
    int op;
    system("cls");
    cout<<"MENU\n";
    cout<<"1. Add Record\n";
    cout<<"2. Delete Record\n";
    cout<<"3. Display all\n";
    cout<<"4. Exit\n";
    cout<<"\nSelect(1-4): ";
    cin>>op;
    cin.ignore();
    return op;
}


void Student::addRecord(Record data){
    Node *p, *q, *nextNode;
    p = q = head;
    nextNode = new Node(data);
    while(p!=nullptr && p->data.name != data.name){
        q = p;
        p = p->next;
    }
    
    if(p->data.name == data.name){
        cout << "duplicate found!" << endl;
    }
    else {
        if(p==head){
            head = nextNode;
        }
        else{
            q->next = nextNode;
        }
        nextNode->next = p;
    }
}

void Student::delRecord(string name){
    Node *p, *q;
    p = q = head;
    while(p!=nullptr && p->data.name != name){
        q = p;
        p = p->next;
    }
    if(p == nullptr){
        cout << "Name not found" << endl;
    }
    else{
        if(p == head){
            head = head->next;
        }
        else{
            q->next = p->next;
        }
        delete(p);
    }

}

void Student::displayRecord(){
    Node *p;
    int i = 1;
    p = head;
    cout << left << setw(10) << "No. " 
        << left << setw(10) << "Name " 
        << right << setw(30) << "Age " << endl;
    while(p!=nullptr){
        cout << left << setw(10) << i++
            << left << setw(10) << p->data.name
            << right << setw(30) << p->data.age << endl;
            p = p->next;
    }
}

void Student::save(){
    ofstream fp("Records.csv");

    if(fp.fail()){
        cout << "Error handling file... " << endl;
    }
    else{
    Node *p;
    p = head;
    
    while(p!=nullptr){
        fp << p->data.name << "," << p->data.age << endl;
        p = p->next;
    }
    }
    fp.close();
}

void Student::retrieve(){
    ifstream fp("Records.csv");

    if(fp.fail()){
        cout << "Error retrieving file" << endl;
    }
    else{
        Record data;
        string line;
        string age;
        while(getline(fp, line)){
            if(line.empty()) continue;
            stringstream ss(line);
            getline(ss, data.name, ',');
            getline(ss, age);
            data.age = stoi(age);

            addRecord(data);
        }
    }
}