#include <iostream>

using namespace std;


struct Node{
    int data;
    Node *left;
    Node *right;
    Node(int x):data(x),left(nullptr),right(nullptr){}
};

struct QueueNode{
    Node *data;
    QueueNode *next;
    QueueNode(Node *x):data(x), next(nullptr){}
};

class Queue{
    private:
    QueueNode *first;
    QueueNode *rear;
    int ctr;
    public:
    Queue():first(nullptr),rear(nullptr), ctr(0){}
    ~Queue(){
        QueueNode *p;
        while(p!=nullptr){
            p = first;
            first = first->next;
            delete(p);
        }
    }
    
    void enqueue(Node *root){
        QueueNode *newNode = new QueueNode(root);
        if(first == nullptr){
            first = rear = newNode;
        } else{
            rear->next = newNode;
            rear = newNode;
        }
        ctr++;
    }

    void dequeue(){
        QueueNode *p;
        if (first == rear){
            p = first;
            first = first->next;
            delete(p);
            rear = nullptr;
        } else{
            p = first;
            first = first->next;
            delete(p);
        }
        ctr--;
    }

    void visit(){
        cout << first->data->data << endl;
    }

    void display(){
        QueueNode *p;
        p = first;
        for(int i = 0; i<ctr; i++){
            cout << p->data->data << endl;
            p = p->next;
        }
    }
};

class Trees{
    private:
    Node *root;

    public:
    
}


int main(){
    Queue queue;
    Node *num1 = new Node(10);
    Node *num2 = new Node(11);
    Node *num3 = new Node(12);
    Node *num4 = new Node(13);
    Node *num5 = new Node(14);
    Node *num6 = new Node(15);
    queue.enqueue(num1);
    queue.enqueue(num2);
    queue.enqueue(num3);
    queue.enqueue(num4);
    queue.dequeue();
    queue.enqueue(num5);
    queue.enqueue(num6);
    queue.dequeue();
    queue.display();
    return 0;
}