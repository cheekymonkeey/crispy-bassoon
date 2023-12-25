#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int data;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* parseBracketNotation(const std::string& s) {
    if (s.empty()) {
        return nullptr;
    }

    std::stack<Node*> st;
    Node* root = nullptr;
    int i = 0;

    while (i < s.length()) {
        if (isdigit(s[i])) {
            int value = s[i] - '0';
            Node* newNode = new Node(value);
            if (st.empty()) {
                root = newNode;
            }
            else {
                Node* top = st.top();
                if (top->left == nullptr) {
                    top->left = newNode;
                }
                else if (top->right == nullptr) {
                    top->right = newNode;
                }
            }
            st.push(newNode);
        }
        else if (s[i] == ')') {
            st.pop();
        }
        i++;
    }

    return root;
}

void printInorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

void inorderVal(Node* root, std::vector<int>& values) {
    if (root == nullptr) {
        return;
    }
    inorderVal(root->left, values);
    values.push_back(root->data);
    inorderVal(root->right, values);
}

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

int height(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNode* insertNode(AVLNode* root, int value) {
    if (root == nullptr) {
        return new AVLNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    else {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && value < root->left->data) {
        return rotateRight(root);
    }
    if (balance < -1 && value > root->right->data) {
        return rotateLeft(root);
    }
    if (balance > 1 && value > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && value < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

AVLNode* deleteNode(AVLNode* root, int value) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            AVLNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == nullptr) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void preorderTraversal(AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

void postorderTraversal(AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

void levelOrderTraversal(AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    queue<AVLNode*> q;
    q.push(root);
    while (!q.empty()) {
        AVLNode* current = q.front();
        cout << current->data << " ";
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
        q.pop();
    }
}

AVLNode* convertBinaryTreeToAVL(Node* root) {
    std::vector<int> values;
    inorderVal(root, values);

    AVLNode* avlRoot = nullptr;
    for (int value : values) {
        avlRoot = insertNode(avlRoot, value);
    }

    return avlRoot;
}

int main() {
    setlocale(LC_ALL, "Russian");
    ifstream File("input.txt");
    if (!File.is_open()) {
        cout << "Файл не найден." << endl;
        return 1;
    }

    string expression;
    getline(File, expression);
    File.close();

    cout << "Скобочная запись : " << expression << endl;
    Node* root1 = parseBracketNotation(expression);

    cout << "Полученное бинарное дерево (Центрированный обход в глубину): ";
    printInorder(root1);
    cout << endl;

    AVLNode* avlRoot = convertBinaryTreeToAVL(root1);

    cout << "АВЛ - дерево (Центрированный обход в глубину): ";
    inorderTraversal(avlRoot);
    cout << endl;

    cout << "Прямой обход в глубину: ";
    preorderTraversal(avlRoot);
    cout << endl;

    cout << "Обратный обход в глубину: ";
    postorderTraversal(avlRoot);
    cout << endl;

    cout << "Обход в ширину: ";
    levelOrderTraversal(avlRoot);
    cout << endl;

    return 0;
}
