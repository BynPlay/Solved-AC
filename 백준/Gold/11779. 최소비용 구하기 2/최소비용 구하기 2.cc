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

int n, m;
vector<pair<int, int>> Graph[1001];


void dikstra(int start, vector<int>& dist, vector<int>& visited, int end) {
    priority_queue<tuple<int, int, vector<int>>, vector<tuple<int, int, vector<int>>>, greater<tuple<int, int, vector<int>>>>pq; dist[start] = 0;
    visited.push_back(start);
    pq.push({ 0, start, visited });
    
    while (!pq.empty()) {
        auto [distance, now, now_visited] = pq.top(); pq.pop();
        if (distance > dist[now]) continue;
      
        if (now == end) {
            visited = now_visited;
        }

        for (auto [next,weight] : Graph[now]) {
            if (dist[next] > dist[now] + weight) {
                dist[next] = dist[now] + weight;
                vector<int> copied_visited = now_visited;
                copied_visited.push_back(next);
                pq.push({ dist[next], next, copied_visited });
            }
        }
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> n >> m;

    for (int i = 0; i < m ; i++) {
        int u, v, w; cin >> u >> v >> w;
        Graph[u].push_back({ v, w });
    }

    int start, end; 
    cin >> start >> end;

    vector<int> dist(n + 1, INF);
    vector<int> visited;
    
    dikstra(start, dist, visited, end);
    
    cout << dist[end] << '\n';
    cout << visited.size() << endl;
    for (auto& i : visited) {
        cout << i << ' ';
    }
}