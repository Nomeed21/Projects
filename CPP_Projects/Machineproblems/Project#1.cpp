#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Account{
    string name;
    int account_number;
    int pincode;
    float balance;

    Account(){
        name = "";
        account_number = 0;
        pincode = 0;
        balance = 0.00;
    }

    Account(string nm,
    int acc,
    int pin,
    float bal){
        name = nm;
        account_number = acc;
        pincode = pin;
        balance = bal;
    }

};

struct Node{
    Account data;
    Node *next;

    Node(){}
}

class User {
    private:
    
}

