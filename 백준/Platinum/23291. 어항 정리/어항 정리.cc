#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <climits>
#include <cstring>

using namespace std; 
const int INF = INT_MAX;
const int Dr[4] = {1,-1,0,0};
const int Dc[4] = {0,0,1,-1};

int N,K;

int Map[101][101];

void checkFishTank();
void putFishtoMinimum();
void pileFishTank();
void pullLeft();
void pullLeft(int CopiedMap[101][101]);
void pullLeft(int row);
bool TranslateFishTank1();
void MoveFish();
void pileTofloor();
void TranslateFishTank2();
int calcuateMaxandMin(){
    int max {-1}; int min {INF};
    for(int col = 1; col <= N; col++){
        if(Map[N][col] > max){
            max = Map[N][col];
        }
        if(Map[N][col] < min){
            min = Map[N][col];
        }
    }
    return max - min;
};


int main() {    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    for(int i = 1; i <= N ; i++){
        cin >> Map[N][i];
    }

    int ans {0};
    while(calcuateMaxandMin() > K){
    //checkFishTank();
    putFishtoMinimum();
    //checkFishTank();
    pileFishTank();
    while(TranslateFishTank1()){
        //checkFishTank();
    }
    MoveFish();
    //checkFishTank();
    pileTofloor();
    //checkFishTank();
    TranslateFishTank2();
    //checkFishTank();
    MoveFish();
    //checkFishTank();
    pileTofloor();
    //checkFishTank();
        ans++;
    }
    cout << ans;
}

///////////////////////////////
////////Implementation/////////
///////////////////////////////

void putFishtoMinimum(){
    int min = INF;
    for(int col = 1; col <= N ; col++){
        if(Map[N][col] < min){
            min = Map[N][col];
        }
    }
    for(int col = 1; col <= N ; col++){
        if(Map[N][col] == min){
            Map[N][col]++;
        }
    }
}

void pileFishTank(){
    Map[N-1][1] = Map[N][1];
    Map[N][1] = 0;
    pullLeft();
}

bool TranslateFishTank1(){
    int CopiedMap[101][101];
    memcpy(CopiedMap,Map,sizeof(Map));
    
    vector<vector<int>>piled_banks;
    for(int col = N; col >= 1; col--){
        int cnt {0};
        for(int row = 1; row <= N; row++){
            if(CopiedMap[row][col] != 0){
                cnt++;
            }
        }
        if(cnt > 1){
            vector<int>piled_bank;
            for(int i = N; i >= 1 ;i--){
                if(CopiedMap[i][col] != 0){
                    piled_bank.push_back(CopiedMap[i][col]);
                    CopiedMap[i][col] = 0;
                }
            }
            piled_banks.push_back(piled_bank);
        }
    }

    pullLeft(CopiedMap);

    for(int i = 0; i < piled_banks.size(); i++){
        for(int j = 0; j < piled_banks[i].size(); j++){
            CopiedMap[N-1-i][j+1] = piled_banks[i][j];
        }
    }

    int chk1 {0};
    int chk2 {0};
    for(int i = 1; i <= N ;i++){
        if(CopiedMap[N][i] != 0){
            chk1++;
        }
        if(CopiedMap[N-1][i] != 0){
            chk2++;
        }
    }
    if(chk1 < chk2){
        return false;
    }
    else{
        memcpy(Map,CopiedMap,sizeof(CopiedMap));
        return true;
    }
}

void MoveFish(){
    int CopiedMap[101][101];
    memcpy(CopiedMap,Map,sizeof(Map));

    for(int row = 1; row <= N ; row++){
        for(int col = 1; col <= N ; col++){
            if(Map[row][col] != 0){
                for(int d = 0; d < 4 ;d++){
                    int nr = row + Dr[d]; int nc = col + Dc[d];
                    if(nr >= 1 && nr <= N && nc >= 1 && nc <= N){
                        if(Map[nr][nc] != 0){
                            int d = (Map[nr][nc] - Map[row][col]) / 5;
                            if(d > 0){
                                if(Map[nr][nc] < Map[row][col]){
                                    CopiedMap[nr][nc] += d;
                                    CopiedMap[row][col] -= d;
                                }
                                else{
                                    CopiedMap[nr][nc] -= d;
                                    CopiedMap[row][col] += d;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    memcpy(Map,CopiedMap,sizeof(CopiedMap));
}

void pileTofloor(){
    int tmpMap[101][101] = {};
    int now_idx = 1;
    for(int col = 1; col <= N; col++){
        for(int row = N; row >= 1; row--){
            if(Map[row][col] != 0){
                tmpMap[N][now_idx] = Map[row][col];
                now_idx++;
            }
    }
    }
    memcpy(Map,tmpMap,sizeof(tmpMap));
}

void TranslateFishTank2(){
    int i = N; int height {0};
    for(int cnt = 0; cnt < 2 ;cnt++){
        vector<vector<int>>piled_banks;
        for(int col = 1; col <= i/2; col++){
            vector<int>piled_bank;
            for(int row = N; row >= 1 ; row--){
                if(Map[row][col] != 0){
                    piled_bank.push_back(Map[row][col]);
                    Map[row][col] = 0;
                }
            }
            height = piled_bank.size();
            piled_banks.push_back(piled_bank);
        }
        for(int i = 0; i < height ;i++){
            pullLeft(N-i);
        }

        if(piled_banks.size() > 0){
            if(piled_banks[0].size() > 0){
                int s {0};
                for(int row = N + 1 - (height * 2); row <= N-height; row++){
                    int f {0}; 
                    for(int col = i/2; col >= 1 ;col--){
                        Map[row][col] = piled_banks[f][s];
                        f++;
                    }
                    s++;
                }
                i /= 2;
            }
        }
    }
}

void pullLeft(){
    int write = 1;
    for(int read = 1; read <= N; read++){
        if(Map[N][read] != 0){
            Map[N][write] = Map[N][read];
            write++;
        }
    }
    while(write <= N){
        Map[N][write] = 0;
        write++;
    }
}

void pullLeft(int row){
    int write = 1;
    for(int read = 1; read <= N; read++){
        if(Map[row][read] != 0){
            Map[row][write] = Map[row][read];
            write++;
        }
    }
    while(write <= N){
        Map[row][write] = 0;
        write++;
    }
}

void pullLeft(int CopiedMap[101][101]){
    int write = 1;
    for(int read = 1; read <= N; read++){
        if(CopiedMap[N][read] != 0){
            CopiedMap[N][write] = CopiedMap[N][read];
            write++;
        }
    }
    while(write <= N){
        CopiedMap[N][write] = 0;
        write++;
    }
}

void checkFishTank(){
    for(int row = 1; row <= N ; row++){
        for(int col = 1; col <= N ; col++){
            if(Map[row][col] != 0){
                cout << Map[row][col] << ' ';
            }
            else{
                cout << ' ' << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}


