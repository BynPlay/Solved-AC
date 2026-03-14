#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <queue>
#include <cstdio>
#include <stack>
#include <cstring>
#include <deque>

using namespace std;
const int INF { INT_MAX };

struct Tree {
    int num;
    Tree* leftPtr;
    Tree* rightPtr;

    Tree(int val) {
        num = val; leftPtr = nullptr; rightPtr = nullptr;
    }
};


Tree* InsertTree(Tree *root, int val) {
    
    if (root == nullptr) {
        return new Tree(val);
    }

    if (val < root->num) {
        root->leftPtr = InsertTree(root->leftPtr,val);
    }
    else if (val > root->num) {
        root->rightPtr = InsertTree(root->rightPtr, val);
    }

    return root;

}

void preOrder(Tree* root) {

    if (root == nullptr) return;

    preOrder(root->leftPtr);
    preOrder(root->rightPtr);
    cout << root->num << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    Tree* root = nullptr;

    int node;
    while (cin >> node) {
        root = InsertTree(root, node);
    }

    preOrder(root);

}