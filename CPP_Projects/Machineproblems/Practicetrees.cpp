#include <iostream>
#include <string>


using namespace std;

#define MAX 100

struct Node{
    char data;
    Node *left;
    Node *right;

    Node(char c):data(c),left(nullptr),right(nullptr){}
};

class NodeStack{
    private:
    Node* items[MAX];
    int top;

    public:
    NodeStack():top(MAX){}
    void push(Node *data){
        top--;
        items[top] = data;
    }

    Node* pop(){
        if (top == -1)
            return NULL;

        return items[top++];
    }

    bool isEmpty(){
        return top == MAX;
    }
};

class CharStack{
    private:
    char items[MAX];
    int top;

    public:
    CharStack():top(MAX);

    void push(char c){
        items[--top] = c;
    }

    char pop(){
        if(isempty()){
            return '\0';
        }

        return items[top++];
    }
    char tOp {
        if(isempty()){
            return '\0';
        }
        return items[top];
    }

    bool isempty(){
        return top == MAX;
    }

};

bool isOperator(char c){
    return c == '+' || c == '-' || c == '/' || c == '*';
}

int precedence(char c){
    if(c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;

    return 0;
}

void createSubTree(Nodestack &nodes, char op){
    Node* right = nodes.pop();
    Node* left = nodes.pop();
    
    Node* newNode = new Node(op);
    newNode->right = right;
    newNode->left = left;

    nodes.push(newNode);
}

Node* createExpressionTrees(string expression){
    NodeStack nodes;
    CharStack operators;

    for(int i = 0; i < expression.length(); i++){
        if (c == ' ')
            continue;

        if (!isOperator(c) && c != '(' && c != ')'){
            Node* newNode = new Node(c);
            nodes.push(newNode);
        }
        else if(c == '(')
            operators.push(c);
        else if(c == ')'){
            while(!operators.isempty() && operators.top != '(')
        }
    }
}
int main(){

    return 0;
}