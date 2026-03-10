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
#include <cstring>

int N;

using namespace std; 

struct Node {
    int point;
    int next;
    int bluenext;
};

Node Board[33]; // 0 32
int Dice[10];
int Horse[5];
bool Occupied[33];
int max_ans{ -1 };

void bruteForceSelect(int depth, vector<int>& selected);
int GameSimulation(vector<int>& selected);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);


    for (int i = 0; i < 33; i++) {
        Board[i].point = 0;
        Board[i].next = -1;
        Board[i].bluenext = -1;
    }

    for (int i = 0; i <= 20; i++) {
        Board[i].point = i * 2;
        Board[i].next = i + 1;
    }

    Board[5].bluenext = 22; Board[10].bluenext = 25; Board[15].bluenext = 27;

    Board[22].point = 13; Board[22].next = 23;
    Board[23].point = 16; Board[23].next = 24;
    Board[24].point = 19; Board[24].next = 30;
    Board[25].point = 22; Board[25].next = 26;
    Board[26].point = 24; Board[26].next = 30;
    Board[27].point = 28; Board[27].next = 28;
    Board[28].point = 27; Board[28].next = 29;
    Board[29].point = 26; Board[29].next = 30;
    Board[30].point = 25; Board[30].next = 31;
    Board[31].point = 30; Board[31].next = 32;
    Board[32].point = 35; Board[32].next = 20;

    for (int i = 0; i < 10; i++) {
        cin >> Dice[i];
    }
    
    vector<int> selected;
    bruteForceSelect(0, selected);
    
    cout << max_ans;
    
}

void bruteForceSelect(int depth, vector<int>& selected) {

    if (depth == 10) {
        int sum = GameSimulation(selected);
        if (sum > max_ans) {
            max_ans = sum;
        }
        return;
    }

    for (int i = 1; i <= 4; i++) {

        selected.push_back(i);
        bruteForceSelect(depth + 1, selected);
        selected.pop_back();
    }
}

int GameSimulation(vector<int>& selected) {
    int sum{ 0 }; memset(Horse, 0, sizeof(Horse)); memset(Occupied, false, sizeof(Occupied));

    for (int i = 0; i < 10; i++) {
        int selected_horse = Horse[selected[i]];
        int cnt{ 0 };

        if (selected_horse == 21) {
            return -1;
        }

        Occupied[selected_horse] = false;

        if (Board[selected_horse].bluenext != -1) {
            Horse[selected[i]] = Board[selected_horse].bluenext;
            selected_horse = Horse[selected[i]];
            cnt++;
        }

        for (int j = cnt; j < Dice[i]; j++) {
            
            Horse[selected[i]] = Board[selected_horse].next;
            selected_horse = Horse[selected[i]];

            if (selected_horse == 21) {
                break;
            }
            //cout << selected[i] << ": " << Board[selected_horse].point << endl;
        }

        if (selected_horse != 21 && Occupied[selected_horse] == true) {
            return -1;
        }

        Occupied[selected_horse] = true;

        sum += Board[selected_horse].point;
    }

    return sum;
}

