#include <iostream>

using namespace std;

struct Node{
    char data;
    Node *left;
    Node *right;

    Node(char letter){
        left = right = nullptr;
        data = letter;
    }
};
struct QueueNode{
    Node *data;
    QueueNode *next;
    QueueNode(Node *x):data(x),next(nullptr){}
};

/*MENU
INORDER
PREORDER
POSTORDER
LEVEL ORDER (do not use library, use your own queue)
BUILD A BINARY TREE
EXIT*/
class Queue{
    private:
    QueueNode *first;
    QueueNode *rear;
    int ctr;
    public:
    Queue():first(nullptr),rear(nullptr),ctr(0){}
    void enqueue(Node* node){
        QueueNode *newNode = new QueueNode(node);
        if(first == nullptr){
            first = rear = newNode;
        }
        else{
            rear->next = newNode;
            rear = newNode;
        }
        ctr++;
    }
    void dequeue(){
        if(!first) cout << "Nothing to delete" << endl;
        else{
            QueueNode *p = first;
            first = p->next;
            if(first == nullptr) rear = nullptr;
            delete(p);
            ctr--;
        }
    }
    Node* front(){
        return first->data;
    }
    bool isempty(){
        return ctr == 0;
    }
};
class BinTree{
    private:
    int ctr;
    public:
    BinTree():ctr(0){}

    void inorder(Node *node);
    void preorder(Node *node);
    void postorder(Node *node);
    void levelorder(Node *node);
    Node* build();
    bool isEmpty(); 
};

int menu();

int main(){
    BinTree tree;
    Node *value;
    char val;
    while(true){
        switch(menu()){
            case 1:
                if(tree.isEmpty()){
                    cout << "Nothing to display" << endl;
                }
                else{
                    tree.inorder(value);
                }
                    system("pause");
                break;

            case 2:
                if(tree.isEmpty()){
                    cout << "Nothing to display"<< endl;
                }
                else{
                    tree.preorder(value);
                }
                    system("pause");
                break;

            case 3:
                if(tree.isEmpty()){
                    cout << "Nothing to display"<< endl;
                }
                else{
                    tree.postorder(value);
                }
                    system("pause");
                break;

            case 4:
                if(tree.isEmpty()){
                    cout << "Nothing to display"<< endl;
                }
                else{
                    tree.levelorder(value);
                }
                    system("pause");
                break;

            case 5:
                value = tree.build();
                system("pause");
                break;

            case 6:
                cout << "Thank you for using my program! Exiting..." << endl;
                system("pause");
                exit(0);

            default:
                cout << "Invalid value!!" << endl;
                system("pause");
        }
    }

    return 0;
}

int menu(){
    system("cls");
    int choice;
    cout << "MENU" << endl
    << "1. Inorder" << endl
    <<"2. Preorder" << endl
    << "3. Postorder " << endl
    <<"4. Level Order" << endl
    <<"5. Build a Binary Tree" << endl
    <<"6. Exit" << endl
    << "Select your choice: ";
    cin >> choice;
    return choice;
}
void BinTree::inorder(Node *node){
    if (!node) return;
    inorder(node->left);
    cout << node->data<< " ";
    inorder(node->right);
}
void BinTree::preorder(Node *node){
    if(!node) return;
    cout <<node->data << " ";
    preorder(node->left);
    preorder(node->right);
}
void BinTree::postorder(Node *node){
    if(!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}
void BinTree::levelorder(Node *node){
    if(!node) return;
    Queue q;
    q.enqueue(node);

    while(!q.isempty()){
        Node* currentnode = q.front();
        cout << currentnode->data << " ";
        q.dequeue();

        if (currentnode->left) q.enqueue(currentnode->left);
        if(currentnode->right) q.enqueue(currentnode->right);
    }

}
Node* BinTree::build(){
    Node *root;
    char values[7];
    for (int i = 0;i < 7; i++){
        cout << "Enter value #" << i+1 << ":  ";
        cin >> values[i];
        ctr++;
    }
    root = new Node(values[0]);
    root->left = new Node(values[1]);
    root->right = new Node(values[2]);
    root->left->left = new Node(values[3]);
    root->left->right = new Node(values[4]);
    root->right->left = new Node(values[5]);
    root->right->right = new Node(values[6]);
    return root;
}
bool BinTree::isEmpty(){
    return ctr == 0;
} 