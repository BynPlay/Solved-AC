#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <climits>
#include <cstring>

using namespace std; 

//←, ↖, ↑, ↗, →, ↘, ↓, ↙ 
const int D_fish[9][2] = {{},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}};
const int D_Shark[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};

struct Shark{
    int x;
    int y;
};

int Matrix[5][5][9];
int M, S;
Shark shark;

void moveFish();
void moveShark(int shark_x,int shark_y, int depth, int& max_eat, int now_eat,int copiedMatrix[5][5][9]);
void disappearSmell();
void debugMatrix();

void duplicateMagicCast(){
    int DuplicatingMatrix[5][5][9] = {};
    memcpy(DuplicatingMatrix,Matrix,sizeof(Matrix));

    moveFish();
    
    int copiedMatrix[5][5][9];
    memcpy(copiedMatrix,Matrix,sizeof(Matrix)); int max_eat {-1};
    moveShark(shark.x, shark.y, 0, max_eat, 0, copiedMatrix);

    for(int row = 1; row <= 4; row++){
        for(int col = 1; col <= 4; col++){
            bool is_eaten {false};
            for(int depth = 1; depth <= 8; depth++){
                if(Matrix[row][col][depth] != copiedMatrix[row][col][depth]){
                    is_eaten = true;
                }
            }
            if(is_eaten == true){
                Matrix[row][col][0] = 3;
            }
        }
    }

    disappearSmell();
    
    for(int row = 1; row <= 4; row++){
        for(int col = 1; col <= 4; col++){
            for(int depth = 1; depth <= 8; depth++){
                Matrix[row][col][depth] += DuplicatingMatrix[row][col][depth];
            }
        }
    }
}

void moveFish(){
    int copiedMatrix[5][5][9] = {};
    for(int row = 1; row <= 4; row++){
        for(int col = 1; col <= 4; col++){
            for(int depth = 1; depth <= 8; depth++){
                bool moved {false};
                if(Matrix[row][col][depth] != 0){
                    for(int i = 0; i < 8; i++){
                        int nr = row + D_fish[(depth-i+7) % 8 + 1][0] ; int nc = col + D_fish[(depth-i+7) % 8 + 1][1];
                        if(nr <= 4 && nr >= 1 && nc <= 4 && nc >= 1){
                            if(Matrix[nr][nc][0] == 0){
                                if(nr != shark.x || nc != shark.y){
                                    copiedMatrix[nr][nc][(depth-i+7) % 8 + 1] += Matrix[row][col][depth];
                                    moved = true;
                                    break;
                                }
                            }
                        }
                    }
                    if(moved == false){
                        copiedMatrix[row][col][depth] += Matrix[row][col][depth];
                    }
                }
            }
        }
    }
    for(int row = 1; row <= 4; row++){
        for(int col = 1; col <= 4; col++){
            for(int depth = 1; depth <= 8; depth++){
                Matrix[row][col][depth] = copiedMatrix[row][col][depth];
            }
        }
    }
}

void moveShark(int shark_x,int shark_y, int depth, int& max_eat, int now_eat,int copiedMatrix[5][5][9]){

    if(depth == 3){
        if(now_eat > max_eat){
            max_eat = now_eat;
            shark.x = shark_x; shark.y = shark_y;
            memcpy(Matrix,copiedMatrix,sizeof(Matrix));
        }
        return;
    }
   
        for(int i = 0; i < 4; i++){
            int nr = shark_x + D_Shark[i][0]; int nc = shark_y + D_Shark[i][1];
            if(nr >= 1 && nr <= 4 && nc >= 1 && nc <= 4){
                int saved[9] = {0};
                for(int d = 1; d <= 8; d++){
                    saved[d] = copiedMatrix[nr][nc][d];
                    copiedMatrix[nr][nc][d] = 0;
                    }
                int eaten {0};
                for(int d = 1; d <= 8; d++){
                    eaten += saved[d];
                    }
                moveShark(nr,nc,depth+1,max_eat,now_eat+eaten,copiedMatrix);
                for(int d = 1; d <= 8; d++){
                    copiedMatrix[nr][nc][d] = saved[d];
                }
              
            }
        }
}

void disappearSmell(){
    for(int row = 1; row <= 4 ; row++){
        for(int col = 1; col <= 4; col++){
            if(Matrix[row][col][0] > 0){
                Matrix[row][col][0]--;
            }
        }
    }
}

void debugMatrix(){
    for(int x=1; x<=4; x++){
        for(int y=1; y<=4; y++){
            int total = 0;
            for(int d=1; d<=8; d++) total += Matrix[x][y][d];
            cout << total << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for(int x=1; x<=4; x++){
        for(int y=1; y<=4; y++){
            cout << Matrix[x][y][0] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main() {    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> M >> S;

    for(int i = 0; i < M; i++){
        int fx, fy, d;
        cin >> fx >> fy >> d;
        Matrix[fx][fy][d]++;
    }
    cin >> shark.x >> shark.y;

    while(S--){
        duplicateMagicCast();
    }

    int ans {0};
    for(int row = 1; row <= 4; row++){
        for(int col = 1; col <= 4; col++){
            for(int depth = 1; depth <= 8; depth++){
                ans += Matrix[row][col][depth];
            }
        }
    }
    cout << ans;
}
