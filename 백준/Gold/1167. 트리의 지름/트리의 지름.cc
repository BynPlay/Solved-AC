#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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

using namespace std;

struct Edge {
    int to;
    int weight;
};

int V;
vector<Edge> Tree[100001];
bool visited[100001];


pair<int,int> bfsSearch(int start) {
    stack<pair<int, int>>s; int max{ 0 }; int far_node{ 0 }; memset(visited, false, sizeof(visited));
    s.push({ start,0 }); visited[start] = true;

    while (!s.empty()) {
        pair<int, int>now = s.top(); s.pop();

        if (now.second > max) {
            max = now.second;
            far_node = now.first;
        }

        for (auto& next : Tree[now.first]) {
            if (visited[next.to] == false) {
                s.push({ next.to, now.second + next.weight });
                visited[next.to] = true;
            }
        }
    }

    return { far_node,max };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> V;

    for (int i = 1; i <= V; i++) {
        int u; cin >> u;
        while (true) {
            int to; cin >> to;
            if (to == -1) {
                break;
            }
            int weight; cin >> weight;
            Tree[u].push_back({ to,weight });
        }
    }

    int x = bfsSearch(1).first;
    cout << bfsSearch(x).second;
}

