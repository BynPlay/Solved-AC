#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;
const int INF{ INT_MAX };

int V, E;

struct Node {
    long long weight;
    int start;
    int end;
};

int sum_weight{ 0 };

int Find(int n, vector<int>& PARENT) {
    if (PARENT[n] == n) { return n; }
    return PARENT[n] = Find(PARENT[n], PARENT);
}

void Union(int node1, int node2, vector<int>& PARENT) {
    int p1 = Find(node1, PARENT);
    int p2 = Find(node2, PARENT);
    PARENT[p1] = p2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> V >> E;

    vector<Node>EDGES(E);

    for (int i = 0; i < E; i++) {
        int A, B, C; 
        cin >> A >> B >> C;
        EDGES[i] = { C,A,B };
    }

    sort(EDGES.begin(), EDGES.end(), [](const Node& A, const Node& B) {return A.weight < B.weight; });
    vector<int>PARENT(V + 1);
    for (int i = 1; i <= V ; i++) {
        PARENT[i] = i;
    }

    for (int i = 0; i < E; i++) {

        if (Find(EDGES[i].start, PARENT) != Find(EDGES[i].end, PARENT)) {
            Union(EDGES[i].start, EDGES[i].end, PARENT);
            sum_weight += EDGES[i].weight;
        }

    }
   
    cout << sum_weight;
}
