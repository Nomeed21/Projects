#include <iostream>

#define MAX 10
using namespace std;

struct Node{
    int value;
    Node *next;
    Node(int x):value(x),next(nullptr){}
};

class Queue{
    private:
    int array[MAX];
    int front, rear, ctr;

    public:
    Queue():front(0), rear(-1), ctr(0){}
    void enqueue(int value);
    void dequeue();
    void peek();
    bool isEmpty();
    bool isFull();
    void display();
};

class PointerQueue{
    private:
    Node *front, *rear;
    int ctr;

    public:
    PointerQueue():front(nullptr), rear(nullptr), ctr(0){}
    void enqueue(int value){
        if(isFull()){
            cout << "Record Full!!" << endl;
        }
        else{
            ctr++;
            Node *newNode =new Node(value);
            if(front == nullptr){
                front = newNode;
                rear = newNode;
            }
            else{
                rear->next = newNode;
                rear = newNode;
            }
        }
    }
    void dequeue(){
        if(isEmpty()){
            cout << "Record Empty!" << endl;
        }
        else{
            Node *p = front;
            front = p->next;
            if(front == nullptr){
                rear = nullptr;
            }
            delete(p);
            ctr--;
        }
    }
    void peek(){
        if(isEmpty()){
            cout << "Nothing on queue..." << endl;
        }
        else{
            cout << "First on queue: " << front->value << endl;
        }
    }
    bool isEmpty(){
        return ctr == 0;
    }
    bool isFull(){
        return ctr == MAX;
    }
    void display(){
        if(isEmpty()){
            cout << "Nothing to display..." << endl;
        }
        else{
            Node *p = front;
            int place = 1;
            while(p!=nullptr){
                cout << place << (place==1?"st":(place==2?"nd":place==3?"rd": "th")) << ": " << p->value << endl;
                place++;
                p = p->next;
            }
        }
    }
};


int menu();

int main(){
    Queue arr;
    PointerQueue list;
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
            << "[1] Enqueue" << endl
            << "[2] Dequeue " << endl 
            << "[3] Peek " << endl
            <<"[4] Display all" << endl
            <<"[5] Back to main Menu" << endl
            <<"[6] Exit code" << endl
            <<"Select your choice: ";
            cin >> choice;
            switch(choice){
                case 1:
                cout << "Enter value: " << endl;
                cin >> value;
                arr.enqueue(value);
                system("pause");
                break;

                case 2:
                arr.dequeue();
                system("pause");
                break;

                case 3:
                arr.peek();
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
                << "[1] Enqueue" << endl
                << "[2] Dequeue " << endl 
                << "[3] Peek " << endl
                <<"[4] Display all" << endl
                <<"[5] Back to main Menu" << endl
                <<"[6] Exit code" << endl
                <<"Select your choice: ";
                cin >> choice;
                switch(choice){
                case 1:
                cout << "Enter value: " << endl;
                cin >> value;
                list.enqueue(value);
                system("pause");
                break;

                case 2:
                list.dequeue();
                system("pause");
                break;

                case 3:
                list.peek();
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
    << "[1] Queue of Array" << endl
    << "[2] Queue of Pointers" << endl 
    << "[3] Exit" << endl
    << "Select your choice: ";
    cin >> choice;
    return choice;

}
void Queue::enqueue(int value){
    if(isFull()){
        cout << "Record Full" << endl;
    }
    else{
        rear = (rear+1) % MAX;
        ctr++;
        array[rear] = value;

        cout << "Record added..." << endl;
    }
}
void Queue::dequeue(){
    if(isEmpty()){
      cout << "Record Empty" << endl;
    }
    else{
        front = (front+1) % MAX;
        ctr--;

        cout << "Record deleted..." << endl;
    }
}
void Queue::peek(){
    if(isEmpty()){
      cout << "Record Empty" << endl;
    }
    else{
        cout << "First in queue: " << array[front]<< endl;
    }
}
bool Queue::isEmpty(){
    return ctr == 0;
}
bool Queue::isFull(){
    return ctr == MAX;
}
void Queue::display(){
    if(isEmpty()){
        cout << "Nothing to display..." << endl;
    }
    else{
        int index = front;
        for(int i = 0; i < ctr;i++){
            cout << array[index] << endl;
            index = (index+1) % MAX;
        }
    }
}