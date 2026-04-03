#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <climits>

using namespace std;

const int INF = INT_MAX;
int N,M,S,T;

int MAP[301][301];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> S >> T;
    
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(i == j){
                MAP[i][j] = 0;
            }
            else{
                MAP[i][j] = INF;
            }
        }
    }
    
    for(int i = 0; i < M; i++){
        int u,v,w; cin >> u >> v >> w;
        if(w < MAP[u][v]){
            MAP[u][v] = w;
        }
    }

    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(MAP[i][k] != INF && MAP[k][j] != INF && MAP[i][k] + MAP[k][j] < MAP[i][j]){
                    MAP[i][j] = MAP[i][k] + MAP[k][j];
                }
            }
        }
    }

    int Q; cin >> Q;
    
    for(int i = 0; i < Q; i++){
        int a1,b1,c1; cin >> a1 >> b1 >> c1;
        int a2,b2,c2; cin >> a2 >> b2 >> c2; 

        int simA{INF}; int simB{INF}; int simC{INF}; int simD{INF}; int simE{INF};
        if(MAP[S][T] != INF){
            simA = MAP[S][T];
        }
        if(MAP[S][a1] != INF && MAP[b1][T] != INF){
            simB = MAP[S][a1] + c1 + MAP[b1][T];
        }
        if(MAP[S][a2] != INF && MAP[b2][T] != INF){
            simC = MAP[S][a2] + c2 + MAP[b2][T];
        }
        if(MAP[S][a1] != INF && MAP[b1][a2] != INF && MAP[b2][T] != INF){
            simD = MAP[S][a1] + c1 + MAP[b1][a2] + c2 + MAP[b2][T];
        }
        if(MAP[S][a2] != INF && MAP[b2][a1] != INF && MAP[b1][T] != INF){
            simE = MAP[S][a2] + c2 + MAP[b2][a1] + c1 + MAP[b1][T];
        }

        if(simA == INF && simB == INF && simC == INF && simD == INF && simE == INF){
            cout << -1 << '\n';
        }
        else{
        cout << min({simA,simB,simC,simD,simE}) << '\n';
        }
    }
 
}

