#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <chrono>
#include <thread>


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

class ATM{
    private:
    Node *head;
    Card data;

    public:
    ATM():head(nullptr){}
    ~ATM(){
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
    void saveToDatabase();
    void saveToCard();
    void readDatabase();
    bool cardInserted();
};

void sleep(int seconds);
int menu();

int main(){
    ATM user;
    user.readDatabase();
    while(!user.cardInserted()){
        cout << "Welcome!!" << endl
        << "Please insert card to continue..." << endl;
    }
    
    cout << "Reading card"; sleep(1);
    cout << "."; sleep(1);
    cout << "."; sleep(1);
    cout << "." << endl;

    bool running = true;
    while(running){
        switch(menu()){
            case 1:
            break;

            case 2:
            break;

            case 3:
            break;

            case 4:
            break;

            case 5:
            break;

            case 6:
            break;

            case 7:
            break;

            case 8:
            break;

            case 9:
            break;

            default:
            cout << "Invalid choice" << endl;
        }
    }


    return 0;
}

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
        << "Select Choice: ";
        cin >> choice;
        return choice + 6;

    }
    return choice;

}

void sleep(int seconds){
    this_thread::sleep_for(chrono::seconds(seconds));
}


void ATM::registerNewAccount(List data){

}
void ATM::balanceInquiry(){
    
}
void ATM::withdraw(float amount){
    
}
void ATM::deposit(float amount);
void ATM::fundTransfer(int accNum, int amount);
void ATM::changepin(int newPin);
void ATM::paybills(int choice, float amount);
void ATM::transactionHistory();

