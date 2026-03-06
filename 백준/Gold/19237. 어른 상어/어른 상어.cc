#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <climits>
#include <cstring>

using namespace std; 
const int DIR[5][2] = {{},{-1,0},{1,0},{0,-1},{0,1}};

int N,M,k;

struct Smell{
    int number = 0;
    int time = 0;
};

Smell Matrix[21][21];

struct Shark{
    int number;
    int row;
    int col;
    int dir;
    int priority_dir[5][4];

    void move(){
        if(number != 0){
        bool myscentFind {false};
        int now_row = row; int now_col = col; int now_dir = dir;
        for(auto &d : priority_dir[now_dir]){
            int nr = row + DIR[d][0]; int nc = col + DIR[d][1];
            if(nr >= 1 && nr <= N && nc >= 1 && nc <= N){
                if(Matrix[nr][nc].number == 0){
                    now_row = nr; now_col = nc; now_dir = d;
                    break;
                }
                else if(Matrix[nr][nc].number == number && myscentFind == false){
                    myscentFind = true;
                    now_row = nr; now_col = nc; now_dir = d;
                }
            }
        }
        row = now_row; col = now_col; dir = now_dir;
        }
    }
};

Shark Sharks[401];

void debugMatrixSharks();
void debugMatrixSmells();

void smellLeave();
void checkStacked();
bool is_Finished(){
    for(int fish = 2; fish <= M; fish++){
        if(Sharks[fish].number != 0){
            return false;
        }
    }
    return true;
}

int main() {    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> k;

    for(int row = 1; row <= N; row++){
        for(int col = 1; col <= N; col++){
            int mat; cin >> mat;
            if(mat != 0){
                Sharks[mat].number = mat;
                Sharks[mat].row = row;
                Sharks[mat].col = col;
            }
        }
    }

    for(int i = 1; i <= M; i++){
        cin >> Sharks[i].dir;
    }

    for(int shark = 1; shark <= M; shark++){
        for(int dir = 1; dir <= 4; dir++){
            for(int pri = 0; pri < 4; pri++){
                cin >> Sharks[shark].priority_dir[dir][pri];
            }
        }
    }

    int ans {0};

    while(!is_Finished()){
        smellLeave();
        for(int i = 1; i <= M; i++){
            Sharks[i].move();
        }
        checkStacked();
        ans++;
        if(ans == 1001){
            ans = -1;
            break;
        }
    }

    cout << ans;
    

    

}

void debugMatrixSharks(){
        for(int row = 1; row <= N; row++){
        for(int col = 1; col <= N; col++){
            bool is_Shark {false};
            for(int shark = 1; shark <= M; shark++){
                if(Sharks[shark].row == row && Sharks[shark].col == col &&  Sharks[shark].number != 0){
                    cout << Sharks[shark].number << ' ';
                    is_Shark = true;
                }
            }
            if(is_Shark == false){
                cout << 0 << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

void debugMatrixSmells(){
    for(int row = 1; row <= N; row++){
        for(int col = 1; col <= N; col++){
            cout << Matrix[row][col].number << ',' <<  Matrix[row][col].time << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void smellLeave(){
     for(int row = 1; row <= N; row++){
        for(int col = 1; col <= N; col++){
            if(Matrix[row][col].number != 0){
                Matrix[row][col].time--;
                if(Matrix[row][col].time == 0){
                    Matrix[row][col].number = 0;
                }
            }
        }
     }
    
    for(int shark = 1; shark <= M; shark++){
        if(Sharks[shark].number != 0){
            Matrix[Sharks[shark].row][Sharks[shark].col].number = shark; 
            Matrix[Sharks[shark].row][Sharks[shark].col].time = k;
        }
    }
}

void checkStacked(){
    for(int i = 1; i <= M-1; i++){
        for(int j = i+1; j <= M; j++){
            if(Sharks[i].row == Sharks[j].row && Sharks[i].col == Sharks[j].col){
                Sharks[j].number = 0;  Sharks[j].row = 0;  Sharks[j].col = 0;
            }
        }
    }
}
