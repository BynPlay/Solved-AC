#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Truck{
    int weight;
    int time;
};

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    
    int pointer {0};
    int now_weight {0}; 
    int now_nums {0};
    deque<Truck>BRDIDGE;
    
    while(true){
        answer++;
        // 위에있는거 뺴서 넣기
        if(pointer < truck_weights.size() && now_weight + truck_weights[pointer] <= weight && now_nums <= bridge_length){
            BRDIDGE.push_back({truck_weights[pointer], bridge_length});
            now_weight += truck_weights[pointer];
            now_nums++;
            pointer++;
        }
        // 전체 1 감소
        for(auto &i: BRDIDGE){
            i.time--;
        }
        
        if(!BRDIDGE.empty() && BRDIDGE.front().time == 0){
            now_weight -= BRDIDGE.front().weight;
            now_nums--;
            BRDIDGE.pop_front();
        }
        
        if(pointer == truck_weights.size() && BRDIDGE.size() == 0){
            break;
        }
    }
    answer++;
    return answer;
}