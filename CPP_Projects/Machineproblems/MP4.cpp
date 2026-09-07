#include <iostream>

#define MAX 5
using namespace std;
/*Push
Pop
Top
Display
Exit*/
struct Node{
    int value;
    Node *next;
    Node(int x):value(x), next(nullptr){}
};

class ArrayStack{
    private:
    int array[MAX];
    int first;

    public:
    ArrayStack():first(MAX){}
    void push(int value){
        if(isFull()){
            cout << "Stack Overflow!!!" << endl;
        }
        else {
            first--;
            array[first] = value;

            cout << "Value added..." << endl;
        }
    }
    void pop(){
        if(isEmpty()){
            cout << "Record is empty..." << endl;
        }
        else {
            first++;
        }
    }
    void top(){
        if(isEmpty()){
            cout << "Record is empty..." << endl;
        }
        else {
            cout << "Top Value: " << array[first] << endl;
        }
    }
    void display(){
        if(isEmpty()){
            cout << "Nothing to display..." << endl;
        }
        else{
            for(int i = first; i <= MAX -1; i++){
                cout << array[i] << endl;
            }
        }
    }
    bool isFull(){
        return first == 0;
    }
    bool isEmpty(){
        return first == MAX;
    }
};

class PointerStack{
    private:
    Node *head;

    public:
    PointerStack():head(NULL){}
    ~PointerStack(){
        Node *p;
        while(head!=nullptr){
            p = head;
            head = head->next;
            delete(p);
        }
    }

    void push(int value){
        Node *newNode;
        newNode = new Node(value);
        newNode->next = head;
        head = newNode;

        cout << "Record added..." << endl;
    }
    void pop(){
        Node *p;
        p = head;
        if (p==nullptr){
            cout << "Record is empty.." << endl;
        }
        else{
        head = head->next;

        delete(p);
        }
    }
    void top(){
        Node *p;
        p = head;
        if (p==nullptr){
            cout << "Record is empty.." << endl;
        }
        else{
            p = head;
            cout << "Top value is: " << p->value << endl;
        }
    }
    void display(){
        Node *p;
        p = head;
        if (p==nullptr){
            cout << "Nothing to display..." << endl;
        }else {
            while(p!=nullptr){
                cout << p->value << endl;
                p = p->next;
            }
    }
    }

};

int menu();

int main(){
    ArrayStack arr;
    PointerStack list;

    while(true){
        
        system("cls");
        int choice = 0;
        bool stop;
        int value;
        switch(menu()){
            case 1:
            stop = false;
            while(!stop){
                system("cls");
            cout << "ARRAY MENU" << endl
            << "[1] Push" << endl
            << "[2] Pop" << endl
            << "[3] Top" << endl
            << "[4] Display" << endl
            << "[5] Return to Main Menu" << endl
            <<"[6] Exit" << endl
            << "Select your choice: ";
            cin >> choice;
            switch(choice){
                case 1:
                cout << "Enter value: " << endl;
                cin >> value;
                arr.push(value);
                system("pause");
                break;

                case 2:
                arr.pop();
                system("pause");
                break;

                case 3:
                arr.top();
                system("pause");
                break;

                case 4:
                arr.display();
                system("pause");
                break;

                case 5:
                stop = true;
                break;

                case 6:
                exit(0);
                break;

                default:
                cout << "Invalid choice!!" << endl;
                system("pause");

            }
        }
            break;
            
            case 2:
            stop = false;
            while(!stop){
                system("cls");
            cout << "POINTER MENU" << endl
            << "[1] Push" << endl
            << "[2] Pop" << endl
            << "[3] Top" << endl
            << "[4] Display" << endl
            << "[5] Return to Main Menu" << endl
            <<"[6] Exit" << endl
            << "Select your choice: ";
            cin >> choice;
            switch(choice){
                case 1:
                cout << "Enter value: " << endl;
                cin >> value;
                list.push(value);
                system("pause");
                break;

                case 2:
                list.pop();
                system("pause");
                break;

                case 3:
                list.top();
                system("pause");
                break;

                case 4:
                list.display();
                system("pause");
                break;

                case 5:
                stop = true;
                break;

                case 6:
                exit(0);

                default:
                cout << "Invalid choice!!" << endl;
                system("pause");

            }
        }
            break;

            case 3:
                exit(0);

            default:
            cout << "Invalid choice!!" << endl;
            system("pause");
        }
    }

    

    return 0;
}

int menu(){
    int choice = 0;
    cout << "MAIN MENU" << endl
    << "[1] Stacks of Array" << endl
    << "[2] Stacks of Pointers" << endl 
    << "[3] Exit" << endl
    << "Select your choice: ";
    cin >> choice;
    return choice;

}