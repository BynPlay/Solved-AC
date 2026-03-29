#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

struct Edge {
    int next;
    int weight;
};

struct Node {
    int position;
    int dist;

    bool operator<(const Node& rhs) const { return dist > rhs.dist; }
};

int n, m, t;
int s, g, h;

vector<int> makeMinDistance(const vector<vector<Edge>>& Graph, int s) {
    priority_queue<Node>pq; vector<int>dist(n + 1, INF);
    pq.push({ s, 0 }); dist[s] = 0;

    while (!pq.empty()) {
        Node now = pq.top(); pq.pop();

        if (now.dist > dist[now.position]) {
            continue;
        }

        for (auto& next : Graph[now.position]) {
            if (now.dist + next.weight < dist[next.next]) {
                dist[next.next] = now.dist + next.weight;
                pq.push( {next.next, dist[next.next] });
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int T; cin >> T;

    for (int i = 0; i < T; i++) {

        cin >> n >> m >> t;
        cin >> s >> g >> h;

        vector<vector<Edge>> Graph(n + 1); int distgh{ 0 };

        for (int i = 0; i < m; i++) {
            int a, b, d; cin >> a >> b >> d;
            Graph[a].push_back({ b,d });
            Graph[b].push_back({ a,d });

            if ((a == g && b == h) || (a == h && b == g)) {
                distgh = d;
            }
        }

        vector<int>diststart = makeMinDistance(Graph, s);
        vector<int>distg = makeMinDistance(Graph, g);
        vector<int>disth = makeMinDistance(Graph, h);

        vector<int>ans;

        for (int i = 0; i < t; i++) {
            int x; cin >> x;
            if (diststart[x] == diststart[g] + distgh + disth[x] || diststart[x] == diststart[h] + distgh + distg[x]) {
                ans.push_back(x);
            }
        }
        sort(ans.begin(), ans.end());
        for (auto& i : ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }

}