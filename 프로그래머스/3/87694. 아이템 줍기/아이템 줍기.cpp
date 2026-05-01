#include <string>
#include <queue>
#include <vector>

using namespace std;

struct Position {
    int x; // 기존 row
    int y; // 기존 col
};

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    
    // 1. 좌표 뻥튀기 및 보드 초기화 (최대 50*2 = 100이므로 102 정도가 안전)
    int board[102][102] = {0,};
    int VISITED[102][102];
    for(int i=0; i<102; i++) for(int j=0; j<102; j++) VISITED[i][j] = -1;

    // 모든 좌표 2배 확대
    for(auto &rect : rectangle) {
        for(int i=0; i<4; i++) rect[i] *= 2;
    }
    characterX *= 2; characterY *= 2;
    itemX *= 2; itemY *= 2;

    // 2. 테두리 그리기 (사용자님이 하려고 하셨던 "내부 파내기"의 확실한 버전)
    for(auto rect : rectangle) {
        for(int i=rect[0]; i<=rect[2]; i++) {
            for(int j=rect[1]; j<=rect[3]; j++) {
                board[i][j] = 1; // 일단 다 채움
            }
        }
    }
    for(auto rect : rectangle) {
        for(int i=rect[0]+1; i<rect[2]; i++) {
            for(int j=rect[1]+1; j<rect[3]; j++) {
                board[i][j] = 0; // 내부는 다시 비움 -> 테두리만 1로 남음
            }
        }
    }

    // 3. 기존 BFS 로직 유지 (좌표만 2배 상태)
    queue<Position> q;
    q.push({characterX, characterY});
    VISITED[characterX][characterY] = 0;

    while(!q.empty()){
        Position now = q.front(); q.pop();

        if(now.x == itemX && now.y == itemY){
            answer = VISITED[now.x][now.y] / 2; // 마지막에 2로 나눔
            break;
        }

        for(int r = 0; r < rectangle.size(); r++){
            // 현재 위치가 이 사각형의 x축 경계선(좌/우)에 있을 때
            if(now.x == rectangle[r][0] || now.x == rectangle[r][2]){
                // 위로 이동 (y+1)
                if(now.y < rectangle[r][3] && board[now.x][now.y + 1] == 1 && VISITED[now.x][now.y + 1] == -1){
                    q.push({now.x, now.y + 1});
                    VISITED[now.x][now.y + 1] = VISITED[now.x][now.y] + 1;
                }
                // 아래로 이동 (y-1)
                if(now.y > rectangle[r][1] && board[now.x][now.y - 1] == 1 && VISITED[now.x][now.y - 1] == -1){
                    q.push({now.x, now.y - 1});
                    VISITED[now.x][now.y - 1] = VISITED[now.x][now.y] + 1;
                }
            }
            // 현재 위치가 이 사각형의 y축 경계선(상/하)에 있을 때
            if(now.y == rectangle[r][1] || now.y == rectangle[r][3]){
                // 오른쪽 이동 (x+1)
                if(now.x < rectangle[r][2] && board[now.x + 1][now.y] == 1 && VISITED[now.x + 1][now.y] == -1){
                    q.push({now.x + 1, now.y});
                    VISITED[now.x + 1][now.y] = VISITED[now.x][now.y] + 1;
                }
                // 왼쪽 이동 (x-1)
                if(now.x > rectangle[r][0] && board[now.x - 1][now.y] == 1 && VISITED[now.x - 1][now.y] == -1){
                    q.push({now.x - 1, now.y});
                    VISITED[now.x - 1][now.y] = VISITED[now.x][now.y] + 1;
                }
            }
        }
    }
    return answer;
}