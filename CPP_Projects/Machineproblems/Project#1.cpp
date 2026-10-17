#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

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
    List():accNum(0){}
};

struct Node{
    List data;
    Node *next;

    Node(List newData):data(newData){}
};

class ATM{
    private:
    Node *head;
    List currentuser;
    Card userdata;

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
    void readDatabase(int accnum);
    bool cardInserted();
    bool isNew();
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


void ATM::registerNewAccount(List newdata){
    Node *p, *q, *newNode;
    p = q = head;
    newNode = new Node(data);

    while(p!=nullptr){
        q = p;
        p = p->next;
    }
    if(p==head){
        head = newNode;
    }
    else{
        q->next = newNode;
    }
    newNode->next = p;

    cout << "Created new account successfully!" << endl
    << "Welcome! " << data.name << endl;
    saveToDatabase();
    saveToCard();
}
void ATM::balanceInquiry(){
    if (isNew()){
        cout << "No account detected yet, create an Account to start" << endl;
    }
    else{
        
    }
}
void ATM::withdraw(float amount){
    currentuser.balance -= amount;
    cout << "Processing"<< amount << ".";
    sleep(1); 
    cout << ".";
    sleep(1);
    cout << "." << endl; 
    cout << "Current balance: " << currentuser.balance << endl;
}
void ATM::deposit(float amount){
    currentuser.balance += amount;
    cout << "Adding into your balance: P"<< amount << ".";
    sleep(1); 
    cout << ".";
    sleep(1);
    cout << "." << endl; 
    cout << "Current balance: " << currentuser.balance << endl;
}
void ATM::fundTransfer(int accNum, int amount){

}
void ATM::changepin(int newPin){
    int pinver;
    cout << "Enter you new Pin again: ";
    cin >> pinver;
    cin.ignore();
    cout << ".";
    sleep(1);
    cout << ".";
    sleep(1);
    cout << ".";
    sleep(1);
    if(pinver == newPin){
        srand(time(0));
        int auth = rand() % 99 + 1;
        int ver;
        cout << auth << endl;
        cout << "Enter pin above to continue: ";
        cin >> ver;
        if(ver == auth){
            sleep(1);
            currentuser.pinCode = newPin;
            cout << "Successfully changed pin" << endl;
        }
        else{
            cout << "Wrong. Returning to menu..." << endl;
        }

    }
    else{
        cout << "Wrong pin, returning to menu..." <, endl;
    }
    
}
void ATM::paybills(int choice, float amount){}
void ATM::transactionHistory(){

}
void ATM::saveToDatabase(){
    ofstream fp("Records.csv");

    if(!fp){
        cout << "Error saving to Database..." << endl;
    }
    else{
        fp << currentuser.name << ","
        << currentuser.accNum << ","
        << currentuser.birthDay << ","
        << currentuser.contactNum << ","
        << currentuser.balance << "," 
        << currentuser.pinCode << "," << endl;
    }
    fp.close();
}
void ATM::saveToCard(){
    //USB

}
void ATM::readDatabase(int accnum){
    ifstream fp("Records.csv");

    if(!fp){
        cout <<"Error accessing the database..." << endl;
    }
    else{
        string line;
        /*string name;
        int accNum;
        int birthDay;
        int contactNum;
        float balance;
        int pinCode;*/
        string accno, bday, contactno, balance, pin;
        while(getline(fp, line)){
            if(line.empty()){
                continue;
            }
            stringstream str(line);
            getline(str, accno, ',');
            currentuser.accNum = stoi(accno);
            
            if(currentuser.accNum == accnum){
            getline(str, currentuser.name, ',');
            getline(str, bday, ',');
            getline(str, contactno, ',');
            getline(str, balance, ',');
            getline(str, pin, ',');
            currentuser.birthDay = stoi(bday);
            currentuser.contactNum = stoi(contactno);
            currentuser.balance = stof(balance);
            currentuser.pinCode = stoi(pin);
            }
        }

    }
    fp.close();
}
bool ATM::cardInserted(){
    //ScanUSB 
}
bool ATM::isNew(){
    return currentuser.accNum == 0;
}

