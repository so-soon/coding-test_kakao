#include <string>
#include <vector>
#include <map>
#include <utility>
#include <string.h>
#include <algorithm>

using namespace std;

map<pair<int,int>, int[2] >info;

bool check(int x,int y,int kind);
bool cmp(vector<int> a,vector<int> b);
vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    
    
    for(int i = 0 ; i < n+1 ; i++){
        for(int j = 0 ; j <n+1 ; j++){
            info[pair<int, int>(i,j)][0] = 0;
            info[pair<int, int>(i,j)][1] = 0;
        }
    }
    
    for(int i = 0 ; i < build_frame.size(); i++){
        if (build_frame[i][3] == 1) { //insert
            info[pair<int, int>(build_frame[i][0],build_frame[i][1])][build_frame[i][2]] = 1;
            if(check(build_frame[i][0], build_frame[i][1], build_frame[i][2])){ //possible insert
                
            }else{//impossible
                info[pair<int, int>(build_frame[i][0],build_frame[i][1])][build_frame[i][2]] = 0;
            }
            
        }else{ //delete
            
            info[pair<int, int>(build_frame[i][0],build_frame[i][1])][build_frame[i][2]] = 0;
            bool isDeletable = true;
            for(map<pair<int,int>, int[2] >::iterator iter = info.begin() ; iter != info.end(); ++iter){ //all direction that effected by delete
                if (iter->second[0] == 0 && iter->second[1] == 0) {
                    continue;
                }
                else{ //
                    if (iter->second[0]  && !(check(iter->first.first, iter->first.second, 0))) {
                        isDeletable = false;
                        break;
                    }
                    if (iter->second[1]  && !(check(iter->first.first, iter->first.second, 1))) {
                        isDeletable = false;
                        break;
                    }
                }
            }
            if (!isDeletable) {
                info[pair<int, int>(build_frame[i][0],build_frame[i][1])][build_frame[i][2]] = 1;
            }
            
        }
    }
    
    vector<int> temp(3,0);
    for(map<pair<int,int>, int[2] >::iterator iter = info.begin() ; iter != info.end(); ++iter){
        if (iter->second[0] == 0 && iter->second[1] == 0) {
            continue;
        }else if (iter->second[0] == 1 && iter->second[1] == 1) {
            
            temp[0] = iter->first.first;
            temp[1] = iter->first.second;
            temp[2] = 0;
            answer.push_back(temp);
            temp[2] = 1;
            answer.push_back(temp);
        }else{
            temp[0] = iter->first.first;
            temp[1] = iter->first.second;
            if (iter->second[0] == 1) {
                temp[2] = 0;
            }else if(iter->second[1] == 1){
                temp[2] = 1;
            }
            
            answer.push_back(temp);
        }
    }
    sort(answer.begin(), answer.end(), cmp);
    return answer;
}

bool check(int x,int y,int kind){
    
    if (kind == 0) { //column
        if (y == 0) { //is floor
            return true;
        }else if(info[pair<int, int>(x,y)][1] == 1){ // is bow from rifgt
            return true;
        }else if(info[pair<int, int>(x-1,y)][1] == 1){ //is bow from left
            return true;
        }else if(info[pair<int, int>(x,y-1)][0] == 1){ // is upper from column
            return true;
        }
        
        
        
        
    }else{ //bow
        if(info[pair<int, int>(x,y-1)][0] == 1){ // is upper from column
            return true;
        } else if(info[pair<int, int>(x+1,y-1)][0] == 1){ // is upper from column(right-down)
            return true;
        } else if(info[pair<int, int>(x-1,y)][1] == 1 && info[pair<int, int>(x+1,y)][1] == 1){ // between bow
            return true;
        }
        
        
    }
    return false;
}


bool cmp(vector<int> a,vector<int> b){
    if (a[0] == b[0]) {
        if (a[1] == b[1]) {
            return a[2] < b[2];
        }else{
            return a[1] < b[1];
        }
    }else{
        return a[0] < b[0];
    }
    
}
