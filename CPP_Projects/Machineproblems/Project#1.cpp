#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>


using namespace std;

struct Card{
    int accNum; 
    int pin;

    Card(){
        accNum = 0;
        pin = 0;
    }
};

struct List{
    string name;
    int accNum;
    int birthDay;
    int contactNum;
    float balance;
    int pinCode;
};

struct Node{
    List data;
    Node *next;

    Node(List newData):data(newData){}
};

class atmUser{
    private:
    Node *head;
    Card data;

    public:
    atmUser():head(nullptr){}
    ~atmUser(){
        Node *p;
        while(p!=nullptr){
            p = head;
            head = head->next;
            delete(p);
        }
    }
    void registerNewAccount(List data);
    void balanceInquiry();
    void withdraw(float amount);
    void deposit(float amount);
    void fundTransfer(int accNum, int amount);
    void changepin(int newPin);
    void paybills(int choice, float amount);
    void transactionHistory();
};

int menu();

int main(){


    return 0;
}

void atmUser::registerNewAccount(List data){

}
void atmUser::balanceInquiry(){
    
}
void atmUser::withdraw(float amount){
    
}
void atmUser::deposit(float amount);
void atmUser::fundTransfer(int accNum, int amount);
void atmUser::changepin(int newPin);
void atmUser::paybills(int choice, float amount);
void atmUser::transactionHistory();

int menu(){
    int choice = 0;
    int otherChoice = 0;
    cout << "MVB Bank"<< endl
    <<"Select transaction:" << endl
    <<"[1] Balance Inquiry" << endl
    << "[2] Withdraw" << endl
    << "[3] Deposit " << endl
    <<"[4] Fund Transfer(for enrolled accounts only)" << endl
    <<"[5] Change PIN Code" << endl
    <<"[6] Other Transactions" << endl
    <<"Input your choice: ";
    cin >> choice;
    
    if(choice == 6){
        cout << "MVB Bank"<< endl
        <<"Select transaction:" << endl
        <<"[1] Pay Bills" << endl
        << "[2] Transaction History" << endl
        << "[3] Back " << endl
        cin >> 
    }

}

