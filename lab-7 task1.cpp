
#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};
Node* buildTree(string s, int& i) {
    if (i >= s.length() || s[i] == ',' || s[i] == ')')
        return NULL;

    Node* root = new Node(s[i++]);

    if (i < s.length() && s[i] == '(') {
        i++;
        root->left = buildTree(s, i);

        if (i < s.length() && s[i] == ',')
            i++;

        root->right = buildTree(s, i);

        if (i < s.length() && s[i] == ')')
            i++;
    }
    return root;
}
void preorder(Node* root) {
    if (root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void inorder(Node* root) {
    stack<Node*> s;
    Node* curr = root;

    while (curr != NULL || !s.empty()) {
        while (curr != NULL) {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        cout << curr->data << " ";
        curr = curr->right;
    }
}
void postorder(Node* root) {
    stack<Node*> s;
    Node* curr = root;
    Node* last = NULL;

    while (curr != NULL || !s.empty()) {
        if (curr != NULL) {
            s.push(curr);
            curr = curr->left;
        } else {
            Node* top = s.top();

            if (top->right != NULL && last != top->right) {
                curr = top->right;
            } else {
                cout << top->data << " ";
                last = top;
                s.pop();
            }
        }
    }
}
bool validate(string s, int& i) {
    if (i >= s.length() || s[i] == ',' || s[i] == ')' ||
        s[i] == '(')
        return false;
    i++;
    if (i < s.length() && s[i] == '(') {
        i++;

        if (i < s.length() && s[i] != ',') {
            if (!validate(s, i))
                return false;
        }

        if (i >= s.length() || s[i] != ',')
            return false;

        i++;

        if (i < s.length() && s[i] != ')') {
            if (!validate(s, i))
                return false;
        }

        if (i >= s.length() || s[i] != ')')
            return false;

        i++;
    }

    return true;
}
int height(Node* root) {
    if (root == NULL)
        return 0;

    int l = height(root->left);
    int r = height(root->right);

    return 1 + (l > r ? l : r);
}
void showDepth(Node* root, int d) {
    if (root == NULL)
        return;

    cout << root->data << ": " << d << endl;
    showDepth(root->left, d + 1);
    showDepth(root->right, d + 1);
}
struct BNode {
    int data;
    BNode* left;
    BNode* right;

    BNode(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};
BNode* insert(BNode* root, int x) {
    if (root == NULL)
        return new BNode(x);

    if (x < root->data)
        root->left = insert(root->left, x);
    else if (x > root->data)
        root->right = insert(root->right, x);

    return root;
}
void bstInorder(BNode* root) {
    if (root == NULL)
        return;

    bstInorder(root->left);
    cout << root->data << " ";
    bstInorder(root->right);
}
int main() {
    string s = "a(b(d,e),c(,f(g,)))";
    int i = 0;
    Node* root = buildTree(s, i);

    cout << "Preorder: ";
    preorder(root);
    cout << "\nInorder: ";
    inorder(root);
    cout << "\nPostorder: ";
    postorder(root);
    int j = 0;
    bool valid = validate(s, j) && j == s.length();

    cout << "\nValid tree string: ";
    cout << (valid ? "Yes" : "No") << endl;
    cout << "Tree height: " << height(root) << endl;
    cout << "Node depths:" << endl;
    showDepth(root, 0);

    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    BNode* bst = NULL;
    for (int k = 0; k < n; k++)
        bst = insert(bst, arr[k]);

    cout << "BST inorder: ";
    bstInorder(bst);
    cout << endl;
    return 0;
}
