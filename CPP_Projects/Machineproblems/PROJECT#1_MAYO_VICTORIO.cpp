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
#include <cstring>
#include <limits>
#include <conio.h>
#include <cmath>

using namespace std;

string encryptData(const string& data);
string decryptData(const string& data);
void clearInputBuffer();
bool readInt(int &value);
bool readFloat(float &value);
bool readPin(string &pin);
bool readBirthday(string &birthday);
bool readContactNum(string &contact);

struct Card{
    int accNum; 
    string pin;

    Card(){
        accNum = 0;
        pin = "";
    }
};

struct List{
    string name;
    int accNum;
    string birthDay;
    string contactNum;
    float balance;
    string pinCode;
    List():accNum(0), balance(0){}
};

struct Node{
    List data;
    Node *next;

    Node(List newData):data(newData), next(nullptr){}
};

class ATM{
    private:
    Node *head;
    List currentuser;
    Card userdata;

    public:
    ATM():head(nullptr){}
    ~ATM(){
        Node *p = head;
        while(p!=nullptr){
            Node *temp = p;
            p = p->next;
            delete temp;
        }
    }
    void loadDatabase();
    void registerNewAccount(List newdata);
    void balanceInquiry();
    void withdraw(float amount);
    void deposit(float amount);
    void fundTransfer(int accNum, float amount);
    void changepin(const string &newPin);
    void paybills(int choice, float amount);
    void transactionHistory();
    void logTransaction(string type, float amount);
    void saveToDatabase();
    void saveToCard();
    bool readDatabase(int accnum);
    bool cardInserted();
    bool isNew();
    string findCardDrive();
    bool isCardInserted();
    bool accountNumberExists(int accNum);
};

void sleep(int seconds);
int menu();

int main(){
    srand(static_cast<unsigned int>(time(0)));
    ATM user;

    user.loadDatabase();

    while(true) {
        cout << "Welcome!!" << endl
        << "Please insert your card to continue..." << endl;

        while(!user.isCardInserted()){
            sleep(1);
        }

        if(!user.cardInserted()){
            while(user.isCardInserted()){
                sleep(1);
            }
            continue;
        }

        cout << "Reading card"; sleep(1);
        cout << "."; sleep(1);
        cout << "."; sleep(1);
        cout << "." << endl;

        bool running = true;
        
        while(running){
            switch(menu()){
                case 0:
                running = false;
                break;
                
                case 1:
                user.balanceInquiry();
                break;

                case 2:{
                    float amt;
                    cout << "Enter amount to withdraw: P";
                    if(!readFloat(amt)){
                        cout << "Invalid input" << endl;
                        break;
                    }
                    user.withdraw(amt);
                }
                break;

                case 3:{
                    float amt;
                    cout << "Enter amount to deposit: P";
                    if(!readFloat(amt)){
                        cout << "Invalid input" << endl;
                        break;
                    }
                    user.deposit(amt);
                }
                break;

                case 4:{
                    int accNum;
                    float amt;
                    cout << "Enter recipient account number: ";
                    if(!readInt(accNum)){
                        cout << "Invalid input" << endl;
                        break;
                    }
                    cout << "Enter amount to transfer: P";
                    if(!readFloat(amt)){
                        cout << "Invalid input" << endl;
                        break;
                    }
                    user.fundTransfer(accNum, amt);
                }
                break;

                case 5:{
                    string newPin;
                    cout << "Enter new 4 or 6-digit PIN: ";

                    if(!readPin(newPin)){
                        cout << "Invalid PIN! PIN must be exactly 4 or 6 digits." << endl;
                        break;
                    }

                    user.changepin(newPin);
                }
                break;

                case 7:{
                    int billChoice;
                    float amt;
                    cout << "[1] Electricity" << endl
                    << "[2] Water" << endl
                    << "[3] Internet" << endl
                    << "Select bill: ";
                    if(!readInt(billChoice)){
                        cout << "Invalid input" << endl;
                        break;
                    }
                    cout << "Enter amount: P";
                    if(!readFloat(amt)){
                        cout << "Invalid input" << endl;
                        break;
                    }
                    user.paybills(billChoice, amt);
                }
                break;

                case 8:
                user.transactionHistory();
                break;

                case 9:
                break;

                default:
                cout << "Invalid choice" << endl;
            }

            if (!running) {
                break;
            }

            cout << "Would you like to do another transaction? [1] Yes [2] No: ";
            int yn;
            if(!readInt(yn)){
                cout << "Invalid input" << endl;
                running = false;
                break;
            }
            if(yn != 1){
                running = false;
                cout << "Thank you for banking with MVB Bank!" << endl;
            }
        }

        cout << "Please remove your card..." << endl;
        while(user.isCardInserted()){
            sleep(1);
        }
        
        system("cls"); 
    }

    return 0;
}

bool ATM::isCardInserted(){
    return !findCardDrive().empty();
}

int menu(){
    system("cls");
    int choice = 0;
    cout << "MVB Bank"<< endl
    <<"Select transaction:" << endl
    <<"[1] Balance Inquiry" << endl
    << "[2] Withdraw" << endl
    << "[3] Deposit " << endl
    <<"[4] Fund Transfer(for enrolled accounts only)" << endl
    <<"[5] Change PIN Code" << endl
    <<"[6] Other Transactions" << endl
    <<"Input your choice(0 to exit): ";
    if(!readInt(choice)){
        return -1;
    }
    
    if(choice == 6){
        cout << "MVB Bank"<< endl
        <<"Select transaction:" << endl
        <<"[1] Pay Bills" << endl
        << "[2] Transaction History" << endl
        << "[3] Back " << endl
        << "Select Choice: ";
        if(!readInt(choice)){
            cout << "Invalid choice" << endl;
            return 9;
        }
        return choice + 6;

    }
    return choice;
}

string encryptData(const string& data){
    int key = 3;
    string result = "";
    for(char c : data){
        result += c + key;
    }
    return result;
}

string decryptData(const string& data){
    int key = 3;
    string decrypted = "";
    for(char c : data){
        decrypted += c - key;
    }

    return decrypted;
}

void clearInputBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool readInt(int &value){
    if(cin >> value){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    clearInputBuffer();
    return false;
}

bool readFloat(float &value){
    if(cin >> value){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    clearInputBuffer();
    return false;
}

bool readPin(string &pin){
    string input;
    int c;

    while (true) {
        c = _getch();

        if (c == '\r') {
            break;
        }
        else if (c == 27) {
            // ESC cancels the entry instead of falling through to
            // whatever partial digits were already typed.
            input.clear();
            break;
        }
        else if (c == '\b') {
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b";
            }
        }
        else if (c == 0 || c == 224) {
            // Arrow keys / function keys send a two-byte sequence:
            // _getch() first returns 0 or 224, then a second call
            // returns the scan code. Without this, that scan-code byte
            // falls through to the next loop iteration and can get
            // misread as ordinary input. Consume and discard it here.
            _getch();
        }
        else if (isdigit(static_cast<unsigned char>(c)) && input.length() < 6) {
            // Cast to unsigned char: isdigit() is undefined behavior
            // when passed a negative char value, which _getch() can
            // return for extended keys on some Windows setups.
            input += static_cast<char>(c);
            cout << '*';
        }
    }

    cout << endl;

    if(input.length() != 4 && input.length() != 6){
        return false;
    }

    // Keep the PIN as the exact string the user typed rather than
    // converting to int. stoi() silently drops leading zeros, which
    // used to mean a 6-digit PIN like "004000" and a 4-digit PIN like
    // "4000" both collapsed to the same value (4000) and were treated
    // as identical/interchangeable PINs. Storing the string preserves
    // the exact digits typed.
    pin = input;
    return true;
}

bool readBirthday(string &birthday){
    string input;

    getline(cin, input);

    if(input.length() != 8){
        return false;
    }

    for(char c : input){
        if(!isdigit(static_cast<unsigned char>(c))){
            return false;
        }
    }

    int month = stoi(input.substr(0, 2));
    int day = stoi(input.substr(2, 2));
    int year = stoi(input.substr(4, 4));

    if(month < 1 || month > 12){
        return false;
    }

    static const int daysInMonth[] = {31,29,31,30,31,30,31,31,30,31,30,31};
    if(day < 1 || day > daysInMonth[month - 1]){
        return false;
    }

    time_t now = time(0);
    int currentYear = 1900 + localtime(&now)->tm_year;
    if(year < 1900 || year > currentYear){
        return false;
    }

    birthday = input.substr(0, 2) + "/" + input.substr(2, 2) + "/" + input.substr(4, 4);
    return true;
}

bool readContactNum(string &contact){
    string input;

    getline(cin, input);

    if(input.length() != 11){
        return false;
    }

    if(input[0] != '0' || input[1] != '9'){
        return false;
    }

    for(char c : input){
        if(!isdigit(c)){
            return false;
        }
    }

    contact = input;
    return true;
}

void sleep(int seconds){
    this_thread::sleep_for(chrono::seconds(seconds));
}

void ATM::loadDatabase(){
    ifstream fp("Records.csv");

    if(!fp){
        cout << "No existing database found. Starting fresh..." << endl;
        return;
    }

    string line;
    while(getline(fp, line)){
        if(line.empty()){
            continue;
        }
        stringstream str(line);
        string accno, name, bday, contactno, balance, pin;
        getline(str, accno, ',');
        getline(str, name, ',');
        getline(str, bday, ',');
        getline(str, contactno, ',');
        getline(str, balance, ',');
        getline(str, pin, ',');

        List newdata;
        try{
            newdata.accNum = stoi(accno);
            newdata.name = name;
            newdata.birthDay = bday;
            newdata.contactNum = contactno;
            newdata.balance = stof(balance);
        }
        catch(...){
            continue;
        }

        string decryptedPin = decryptData(pin);
        if(decryptedPin.length() != 4 && decryptedPin.length() != 6){
            continue;
        }
        newdata.pinCode = decryptedPin;

        Node *newNode = new Node(newdata);

        if(head == nullptr){
            head = newNode;
        }
        else{
            Node *p = head;
            while(p->next != nullptr){
                p = p->next;
            }
            p->next = newNode;
        }
    }
    fp.close();
}

void ATM::registerNewAccount(List newdata){
    Node *p, *q, *newNode;
    p = q = head;
    newNode = new Node(newdata);

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

    currentuser = newdata;

    cout << "Created new account successfully!" << endl
    << "Welcome! " << newdata.name << endl;
    saveToDatabase();
    saveToCard();
}
void ATM::balanceInquiry(){
    if (isNew()){
        cout << "No account detected yet, create an Account to start" << endl;
    }
    else{
        cout << "Current balance: P" << fixed << setprecision(2) << currentuser.balance << endl;
    }
}
void ATM::withdraw(float amount){
    if(isNew()){
        cout << "No account detected yet, create an Account to start" << endl;
        return;
    }
    float remainder = fmod(amount, 100.0f);
    if(amount <= 0 || (remainder > 0.001f && remainder < 99.999f)){
        cout << "Withdrawal amount must be a multiple of P100." << endl;
        return;
    }
    if(amount > currentuser.balance){
        cout << "Insufficient balance!" << endl;
        return;
    }
    currentuser.balance -= amount;
    cout << "Processing P"<< amount << ".";
    sleep(1); 
    cout << ".";
    sleep(1);
    cout << "." << endl; 
    cout << "Current balance: " << currentuser.balance << endl;
    saveToDatabase();
    logTransaction("Withdraw", amount);
}
void ATM::deposit(float amount){
    if(isNew()){
        cout << "No account detected yet, create an Account to start" << endl;
        return;
    }
    if(amount <= 0){
        cout << "Deposit amount must be greater than 0." << endl;
        return;
    }
    currentuser.balance += amount;
    cout << "Adding into your balance: P"<< amount << ".";
    sleep(1); 
    cout << ".";
    sleep(1);
    cout << "." << endl; 
    cout << "Current balance: " << currentuser.balance << endl;
    saveToDatabase();
    logTransaction("Deposit", amount);
}
void ATM::fundTransfer(int accNum, float amount){
    if(isNew()){
        cout << "No account detected yet, create an Account to start" << endl;
        return;
    }
    if(amount <= 0){
        cout << "Transfer amount must be greater than 0." << endl;
        return;
    }
    if(accNum == currentuser.accNum){
        cout << "You cannot transfer funds to your own account." << endl;
        return;
    }
    if(amount > currentuser.balance){
        cout << "Insufficient balance!" << endl;
        return;
    }

    Node *p = head;
    bool found = false;
    while(p!=nullptr){
        if(p->data.accNum == accNum){
            found = true;
            p->data.balance += amount;
            break;
        }
        p = p->next;
    }
    if(!found){
        cout << "Recipient account not found!" << endl;
        return;
    }

    currentuser.balance -= amount;
    cout << "Transferring P" << amount << " to account " << accNum << ".";
    sleep(1);
    cout << ".";
    sleep(1);
    cout << "." << endl;
    cout << "Current balance: " << currentuser.balance << endl;
    saveToDatabase();
    logTransaction("Fund Transfer", amount);
}
void ATM::changepin(const string &newPin){
    string pinver;
    cout << "Enter your new PIN again: ";
    if(!readPin(pinver)){
        cout << "Invalid PIN! PIN must be exactly 4 or 6 digits." << endl;
        return;
    }
    cout << ".";
    sleep(1);
    cout << ".";
    sleep(1);
    cout << ".";
    sleep(1);
    if(pinver == newPin){
        int auth = rand() % 99 + 1;
        int ver;
        cout << auth << endl;
        cout << "Enter pin above to continue: ";
        if(!readInt(ver)){
            cout << "Invalid input. Returning to menu..." << endl;
            return;
        }
        if(ver == auth){
            sleep(1);
            currentuser.pinCode = newPin;
            saveToDatabase();
            cout << "Successfully changed pin" << endl;
        }
        else{
            cout << "Wrong. Returning to menu..." << endl;
        }

    }
    else{
        cout << "Wrong pin, returning to menu..." << endl;
    }
    
}
void ATM::paybills(int choice, float amount){
    if(isNew()){
        cout << "No account detected yet, create an Account to start" << endl;
        return;
    }
    if(amount <= 0){
        cout << "Payment amount must be greater than 0." << endl;
        return;
    }
    if(amount > currentuser.balance){
        cout << "Insufficient balance!" << endl;
        return;
    }

    string billName;
    switch(choice){
        case 1: 
            billName = "MERALCO";
            break;
        case 2: 
            billName = "MAYNILAD"; 
            break;
        case 3: 
            billName = "PLDT"; 
            break;
        default: 
            cout << "Invalid bill selection." << endl;
            return;
    }

    currentuser.balance -= amount;
    cout << "Paying " << billName << " bill: P" << amount << ".";
    sleep(1);
    cout << ".";
    sleep(1);
    cout << "." << endl;
    cout << "Current balance: " << currentuser.balance << endl;
    saveToDatabase();
    logTransaction(billName + " Bill", amount);
}
void ATM::transactionHistory(){
    if(isNew()){
        cout << "No account detected yet, create an Account to start" << endl;
        return;
    }

    ifstream fp("History.csv");
    if(!fp){
        cout << "No transaction history yet." << endl;
        return;
    }

    string line;
    bool any = false;
    cout << "----- Transaction History -----" << endl;
    while(getline(fp, line)){
        if(line.empty()){
            continue;
        }
        stringstream str(line);
        string accno, type, amount, when;
        getline(str, accno, ',');
        getline(str, type, ',');
        getline(str, amount, ',');
        getline(str, when, ',');

        try{
            if(stoi(accno) == currentuser.accNum){
                any = true;
                time_t t = stol(when);
                cout << type << " - P" << amount << " - " << ctime(&t);
            }
        }
        catch(...){
            continue;
        }
    }
    if(!any){
        cout << "No transactions found for this account." << endl;
    }
    fp.close();
}
void ATM::logTransaction(string type, float amount){
    ofstream fp("History.csv", ios::app);

    if(!fp){
        cout << "Error logging transaction..." << endl;
        return;
    }

    time_t now = time(0);
    fp << currentuser.accNum << "," << type << "," << amount << "," << now << endl;
    fp.close();
}
void ATM::saveToDatabase(){
    Node *p = head;
    while(p != nullptr){
        if(p->data.accNum == currentuser.accNum){
            p->data = currentuser;
            break;
        }
        p = p->next;
    }

    ofstream fp("Records.csv");

    if(!fp){
        cout << "Error saving to Database..." << endl;
        return;
    }

    p = head;
    while(p != nullptr){
        fp << p->data.accNum << ","
        << p->data.name << ","
        << p->data.birthDay << ","
        << p->data.contactNum << ","
        << p->data.balance << ","
        << encryptData(p->data.pinCode) << endl;
        p = p->next;
    }
    fp.close();
}
void ATM::saveToCard(){
    string drive = findCardDrive();

    if(drive.empty()){
        cout << "No card detected. Could not save card." << endl;
        return;
    }

    ofstream fp(drive + "card.dat");
    if(!fp){
        cout << "Error writing to card..." << endl;
        return;
    }
    fp << encryptData(to_string(currentuser.accNum)) << endl;
    fp.close();
    cout << "Account saved to card." << endl;
}
string ATM::findCardDrive(){
    char drives[MAX_PATH];
    DWORD len = GetLogicalDriveStringsA(MAX_PATH, drives);
    char *drive = drives;

    while(*drive){
        if(GetDriveTypeA(drive) == DRIVE_REMOVABLE){
            return string(drive);
        }
        drive += strlen(drive) + 1;
    }
    return "";
}
bool ATM::readDatabase(int accnum){
    Node *p = head;
    while(p != nullptr){
        if(p->data.accNum == accnum){
            currentuser = p->data;
            return true;
        }
        p = p->next;
    }
    return false;
}
bool ATM::cardInserted(){
    string drive = findCardDrive();

    if(drive.empty()){
        return false;
    }

    ifstream fp(drive + "card.dat");

    if(!fp){
        cout << "New user detected!" << endl;
        List newdata;

        bool validName = false;
        for(int attempts = 0; attempts < 3 && !validName; attempts++){
            cout << "Enter your name: ";
            getline(cin, newdata.name);
            if(!newdata.name.empty()){
                validName = true;
            } else {
                cout << "Name cannot be blank." << endl;
            }
        }
        if(!validName){
            cout << "Too many invalid attempts. Registration cancelled." << endl;
            return false;
        }

        bool valid = false;
        for(int attempts = 0; attempts < 3 && !valid; attempts++){
            cout << "Enter your birthday (MMDDYYYY): ";
            if(readBirthday(newdata.birthDay)){
                valid = true;
            } else {
                cout << "Invalid birthday! Please enter exactly 8 digits (MMDDYYYY)." << endl;
            }
        }
        if(!valid){
            cout << "Too many invalid attempts. Registration cancelled." << endl;
            return false;
        }

        valid = false;
        for(int attempts = 0; attempts < 3 && !valid; attempts++){
            cout << "Enter your contact number (09XXXXXXXXX): ";
            if(readContactNum(newdata.contactNum)){
                valid = true;
            } else {
                cout << "Invalid contact number! Format must be 09XXXXXXXXX (11 digits)." << endl;
            }
        }
        if(!valid){
            cout << "Too many invalid attempts. Registration cancelled." << endl;
            return false;
        }

        valid = false;
        for(int attempts = 0; attempts < 3 && !valid; attempts++){
            cout << "Set your 4 or 6-digit PIN: ";
            if(readPin(newdata.pinCode)){
                valid = true;
            } else {
                cout << "Invalid PIN! PIN must be exactly 4 or 6 digits." << endl;
            }
        }
        if(!valid){
            cout << "Too many invalid attempts. Registration cancelled." << endl;
            return false;
        }

        newdata.balance = 5000;

        int newAccNum;
        do {
            newAccNum = 10000 + (rand() % 89999);
        } while(accountNumberExists(newAccNum));
        newdata.accNum = newAccNum;

        registerNewAccount(newdata);
        cout << "Your account number is " << newdata.accNum << ". Please remember it!" << endl;
        return true;
    }

    string encryptedCard;
    getline(fp, encryptedCard);
    fp.close();

    string decryptedCard = decryptData(encryptedCard);

    try{
        userdata.accNum = stoi(decryptedCard);
    }
    catch(...){
        cout << "Invalid card data!" << endl;
        return false;
    }

    if(!readDatabase(userdata.accNum)){
        cout << "Account not found in bank records!" << endl;
        return false;
    }

    cout << "Card recognized." << endl;
    const int maxAttempts = 3;
    int attempts = 0;
    while(true){
        cout << "Enter your 4 or 6-digit PIN: ";
        if(!readPin(userdata.pin)){
            attempts++;
            cout << "Invalid PIN! PIN must be exactly 4 or 6 digits." << endl;
        }
        else if(userdata.pin != currentuser.pinCode){
            attempts++;
            cout << "Incorrect pin!" << endl;
        }
        else{
            break;
        }

        if(attempts >= maxAttempts){
            cout << "Too many incorrect attempts. Card rejected." << endl;
            return false;
        }
        cout << "Attempts remaining: " << (maxAttempts - attempts) << endl;
    }

    return true;
}
bool ATM::isNew(){
    return currentuser.accNum == 0;
}
bool ATM::accountNumberExists(int accNum){
    Node *p = head;
    while(p != nullptr){
        if(p->data.accNum == accNum){
            return true;
        }
        p = p->next;
    }
    return false;
}