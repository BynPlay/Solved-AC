#include <string>
#include <vector>
#include <iostream>

using namespace std;

const vector<string> DAYS = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
vector<vector<string>>Calender(13,vector<string>(32));
int now;

string solution(int a, int b) {
    string answer = "";
    now = 5;
    
    for(int m = 1; m <= 12; m++){
        for(int d = 1; d <= 31; d++){
            
            if(m == 4 || m == 6 || m == 9 || m == 11){
                if(d == 31){
                    continue;
                }
            }
            else if(m == 2){
                if(d >= 30){
                    continue;
                }
            }
            
            Calender[m][d] = DAYS[now];
            now = (now + 1) % 7;
            
        }
    }
    
    answer = Calender[a][b];
    return answer;
}