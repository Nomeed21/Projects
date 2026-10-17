#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>

#define MAX 5
using namespace std;

struct Records{
    string name;
    float Balance;
    int pin;
    int accountNum;
};

struct Node{
    Records data;
    Node *next;

    Node(Records x): data(x){}
};

class User{
    private:
    Node *head;
    
    public:
    User():head(nullptr){}
    ~User(){
        Node *p;
        while(head != nullptr){
            p = head;
            head = head->next;
            delete(p);
        }
    }

    void addRecord(Records newData);
    void delRecord(int accNum);
    void changePin(int accNum);
    void withdraw(int amount);
    void deposit(int amount);
    void balanceInquiry();
    void save();
    void retrieve();
};

int main(){
    


    return 0;
}

int menu(){
    int choice = 0;
    cout << "MENU" << endl
    << "[1] Balance Inquiry" << endl
    << "[2] Withdraw" << endl
    << "[3] Deposit " << endl
    << "[4] Change PIN" << endl
    << "[5] Exit" << endl
    <<"Select choice: " << endl;

    cin >> choice;
    cin.ignore();
    return choice;
}


    void User::addRecord(Records newData){
        Node *p, *q, *newNode;
        p = q = head;
        newNode = new Node(newData);

        while(p!=nullptr){
            q = p;
            p = p->next;
        }
        if(p==head){
            head = newNode;
        }
        else{
            q = newNode;
        }
        newNode->next = p;
    }
    void User::delRecord(int accNum){
        Node *p, *q;
        p = q = head;

        while(p!=nullptr && p->data.accountNum != accNum){
            q = p;
            p = p->next;
        }
        if(p==nullptr){
            cout << "Name not found" << endl;
        }
        else{
            if(p==head){
                head = head->next;
                delete(p);
            }else{
                q = q->next;
                delete(p);
            }
        }
    }
    void User::changePin(int accNum){
        Node *p, *q;
        p =head;
        int pin, verify;
        while(p!=nullptr && p->data.accountNum != accNum){
            p = p->next;
        }
        if(p==nullptr){
            cout << "Name not found" << endl;
        }
        else{
            cout << "Enter your current PIN: ";
            cin >> pin;
            if(pin!=p->data.pin){
                cout << "PIN does not match. Returning..." << endl;
            }else{
                do{
                    cout << "Enter new PIN: ";
                    cin >> pin;
                    cout << "Enter new PIN again to confirm: ";
                    cin >> verify;
                    if(pin!=verify){
                        cout << "PIN does not match" << endl;
                    }else {
                        cout << "PIN change success" << endl;
                        p->data.pin = pin;
                    }
                } while(pin!=verify);

            }
        }
    }
    void User::withdraw(int amount){
        
    }
    void User::deposit(int amount);
    void User::balanceInquiry();
    void User::save();
    void User::retrieve();