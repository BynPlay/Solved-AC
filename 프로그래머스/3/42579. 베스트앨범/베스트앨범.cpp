#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Genre{
    string name;
    int play;
    
    bool operator< (const Genre &rhs) const { return play > rhs.play;}
};

struct Music{
    int name;
    int play;
    
    bool operator< (const Music &rhs) const { 
        if(play == rhs.play){
            return name < rhs.name;
        }
        return play > rhs.play;}
};

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    map<string,int>m;
    
    for(int i = 0; i < genres.size();i++){
        m[genres[i]] += plays[i];
    }
    
    vector<Genre>v;
    
    for(auto it = m.begin(); it != m.end(); ++it){
        v.push_back({it->first,it->second});
    }
    
    sort(v.begin(),v.end());
    
    for(auto &n : v){
        vector<Music>tmp;
        for(int i = 0; i < genres.size();i++){
            if(n.name == genres[i]){
                tmp.push_back({i,plays[i]});
            }
        }
        sort(tmp.begin(),tmp.end());
        for(int s = 0; s < 2; s++){
            if(s == 1 && tmp.size() == 1){
                break;
            }
            answer.push_back(tmp[s].name);
        }
    }
    
    return answer;
}