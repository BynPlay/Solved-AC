#include <iostream>
using namespace std;

struct Node {
    char val;
    Node* left;
    Node* right;
    Node(char v) : val(v), left(nullptr), right(nullptr) {}
};

Node* nodes[26];  // 'A'~'Z'

void preorder(Node* cur) {
    if (!cur) return;
    cout << cur->val;
    preorder(cur->left);
    preorder(cur->right);
}

void inorder(Node* cur) {
    if (!cur) return;
    inorder(cur->left);
    cout << cur->val;
    inorder(cur->right);
}

void postorder(Node* cur) {
    if (!cur) return;
    postorder(cur->left);
    postorder(cur->right);
    cout << cur->val;
}

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < 26; i++) {
        nodes[i] = new Node('A' + i);
    }

    for (int i = 0; i < N; i++) {
        char parent, left, right;
        cin >> parent >> left >> right;
        if (left != '.') nodes[parent - 'A']->left = nodes[left - 'A'];
        if (right != '.') nodes[parent - 'A']->right = nodes[right - 'A'];
    }

    preorder(nodes[0]); cout << "\n";   
    inorder(nodes[0]); cout << "\n";
    postorder(nodes[0]); cout << "\n";

    return 0;
}