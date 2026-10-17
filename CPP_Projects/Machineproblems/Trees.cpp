#include <iostream>
#include <string>
using namespace std;
 
#define MAX 100
 
// =========================
// Tree Node
// =========================
struct Node {
    char data;
    Node *left;
    Node *right;
 
    Node(char x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};
 
// =========================
// Stack for Tree Nodes
// =========================
class NodeStack {
private:
    Node* items[MAX];
    int top;
 
public:
    NodeStack() {
        top = MAX;
    }
 
    void push(Node* x) {
        items[--top] = x;
    }
 
    Node* pop() {
        if (top == -1)
            return NULL;
 
        return items[top++];
    }
 
    bool isempty() {
        return top == MAX;
    }
};
 
// =========================
// Stack for Operators
// =========================
class CharStack {
private:
    char items[MAX];
    int top;
 
public:
    CharStack() {
        top = MAX;
    }
 
    void push(char x) {
        items[--top] = x;
    }
 
    char pop() {
        if (isempty())//stack is isempty
            return '\0';
 
        return items[top++];
    }
 
    char tOp() {
        if (top == -1)
            return '\0';
 
        return items[top];
    }
 
    bool isempty() {
        return top == MAX;
    }
};
 
// =========================
// Check Operator
// =========================
bool isOperator(char c) {
    return c == '+' || c == '-' ||
           c == '*' || c == '/';
}
 
// =========================
// Precedence
// =========================
int precedence(char c) {
 
    if (c == '+' || c == '-')
        return 1;
 
    if (c == '*' || c == '/')
        return 2;
 
    return 0;
}
 
// =========================
// Create Subtree
// =========================
void createSubtree(NodeStack &nodes, char op) {
 
    Node *right = nodes.pop();
    Node *left = nodes.pop();
 
    Node *newNode = new Node(op);
 
    newNode->left = left;
    newNode->right = right;
 
    nodes.push(newNode);
}
 
// =========================
// Create Expression Tree
// =========================
Node* createExpressionTree(string expression) {
 
    NodeStack nodes;
    CharStack operators;
 
    for (int i = 0; i < expression.length(); i++) {
 
        char c = expression[i];
 
        if (c == ' ')
            continue;
 
        // Operand
        if (!isOperator(c) && c != '(' && c != ')') {
 
            Node *newNode = new Node(c);
 
            nodes.push(newNode);
        }
 
        // Left parenthesis
        else if (c == '(') {
 
            operators.push(c);
        }
 
        // Right parenthesis
        else if (c == ')') {
 
            while (!operators.isempty() &&
                   operators.tOp() != '(') {
 
                char op = operators.pop();
 
                createSubtree(nodes, op);
            }
 
            operators.pop();
        }
 
        // Operator
        else {
 
            while (!operators.isempty() &&
                   operators.tOp() != '(' &&
                   precedence(operators.tOp()) >= precedence(c)) {
 
                char op = operators.pop();
 
                createSubtree(nodes, op);
            }
 
            operators.push(c);
        }
    }
 
    // Process remaining operators
    while (!operators.isempty()) {
 
        char op = operators.pop();
 
        createSubtree(nodes, op);
    }
 
    return nodes.pop();
}
 
// =========================
// Evaluate Expression Tree
// =========================
double evaluate(Node *root) {
 
    // empty tree
    if (root == NULL)
        return 0;
 
    // If node is a number
    if (!isOperator(root->data)) {
 
        return root->data - '0';//ascii 49 convert to int
    }
 
    // Evaluate left subtree
    double leftValue = evaluate(root->left);
 
    // Evaluate right subtree
    double rightValue = evaluate(root->right);
 
    // Apply operator
    switch (root->data) {
 
        case '+':
            return leftValue + rightValue;
 
        case '-':
            return leftValue - rightValue;
 
        case '*':
            return leftValue * rightValue;
 
        case '/':
            return leftValue / rightValue;
    }
 
    return 0;
}
 
// =========================
// Display Tree
// =========================
void displayTree(Node *root, int space = 0) {
 
    if (root == NULL)
        return;
 
    space += 5;
 
    displayTree(root->right, space);
 
    cout << endl;
 
    for (int i = 5; i < space; i++)
        cout << " ";
 
    cout << root->data << endl;
 
    displayTree(root->left, space);
}
 
// =========================
// Traversals
// =========================
void preorder(Node *root) {
 
    if (root == NULL)
        return;
 
    cout << root->data << " ";
 
    preorder(root->left);
    preorder(root->right);
}
 
void inorder(Node *root) {
 
    if (root == NULL)
        return;
 
    inorder(root->left);
 
    cout << root->data << " ";
 
    inorder(root->right);
}
 
void postorder(Node *root) {
 
    if (root == NULL)
        return;
 
    postorder(root->left);
    postorder(root->right);
 
    cout << root->data << " ";
}
 
// =========================
// Main
// =========================
int main() {
 
    string expression;
 
    cout << "Enter expression: ";
    getline(cin, expression);
 
    Node *root = createExpressionTree(expression);
 
    cout << "\nExpression Tree:\n";
    displayTree(root);
 
    cout << "\nPreorder: ";
    preorder(root);
 
    cout << "\nInorder: ";
    inorder(root);
 
    cout << "\nPostorder: ";
    postorder(root);
 
    cout << "\n\nResult: "
    << evaluate(root);
 
    cout << endl;
 
    return 0;
}