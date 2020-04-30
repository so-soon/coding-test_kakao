#include <string>
#include <vector>
#include <utility>
#include <map>
#include <set>
using namespace std;



vector< pair<int,int> > keys;
set<set<pair<int,int> > > visit;
vector<vector<int>> locks;
int N,M,home;
bool dfs(bool clock, bool rclock, bool down, bool up, bool left, bool right);
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    int temp_home = 0;
    bool isSucess =true;
    set< pair<int,int> > t_s;
    M = int(key.size())-1;
    N = int(lock.size())-1;
    locks = lock;
    home = 0;
    for(int i = 0 ; i < key.size(); i++){
        for(int j = 0 ; j < key[i].size(); j++){
            if (key[i][j] == 1) {
                keys.push_back(pair<int, int>(i,j));
            }
        }
    }
    
    for(int i = 0 ; i < lock.size(); i++){
        for(int j = 0 ; j < lock[i].size(); j++){
            if (lock[i][j] == 0) home++;
        }
    }
    
    
    for(int i = 0 ; i < keys.size(); i++){ //fit check
        if (keys[i].first < 0 || keys[i].first > N || keys[i].second < 0 || keys[i].second > N) {
            continue;
        }
        else if( locks[keys[i].first][keys[i].second] == 0 ){
            temp_home++;
        }
        else if(locks[keys[i].first][keys[i].second] == 1 ){
            isSucess = false;
            break;
        }
    }
    
    if (isSucess && (temp_home == home)) {
        return true;
    }
    
    
    for(int i = 0 ; i < keys.size(); i++){
        t_s.insert(pair<int,int>(keys[i].first,keys[i].second));
    }
    visit.insert(t_s);
    
    if(dfs(true, false, false,false,false,false)) return true;
    if(dfs(false, true, false,false,false,false)) return true;
    if(dfs(false, false, true,false,false,false)) return true;
    if(dfs(false, false, false,true,false,false)) return true;
    if(dfs(false, false, false,false,true,false)) return true;
    if(dfs(false, false, false,false,false,true)) return true;

    return false;
}

bool dfs(bool clock, bool rclock, bool down, bool up, bool left, bool right){
    pair<int,int> temp;
    set< pair<int,int> > t_s;
    bool isSucess =true;
    int temp_home = 0;
    int co_out_of_bound = 0;
    
    
    if (clock) {
        for(int i = 0 ; i < keys.size(); i++){
            temp.second = (M-(keys[i].first));
            temp.first = keys[i].second;
            
            keys[i] = temp;
        }
        
    }else if(rclock){
        for(int i = 0 ; i < keys.size(); i++){
            temp.second = keys[i].first;
            temp.first = (M-(keys[i].second));
            keys[i] = temp;
        }
    }else if(down){
        for(int i = 0 ; i < keys.size(); i++){
            keys[i].first += 1;
        }
    }else if(up){
        for(int i = 0 ; i < keys.size(); i++){
            keys[i].first -= 1;
        }
    }else if(left){
        for(int i = 0 ; i < keys.size(); i++){
            keys[i].second -= 1;
        }
    }else if(right){
        for(int i = 0 ; i < keys.size(); i++){
            keys[i].second += 1;
        }
    }
    
    
    for(int i = 0 ; i < keys.size(); i++){
        t_s.insert(pair<int,int>(keys[i].first,keys[i].second));
        if(keys[i].first < -N || keys[i].first > N || keys[i].second < -N || keys[i].second > N){
            co_out_of_bound++;
        }
    }
    
    if(visit.insert(t_s).second == false || (co_out_of_bound==int(keys.size()))) {
        if (clock) {
             
             for(int i = 0 ; i < keys.size(); i++){
                 temp.second = keys[i].first;
                 temp.first = (M-(keys[i].second));
                 keys[i] = temp;
             }
         }else if(rclock){
             
             for(int i = 0 ; i < keys.size(); i++){
                 temp.second = (M-(keys[i].first));
                 temp.first = keys[i].second;
                 
                 keys[i] = temp;
             }
         }else if(down){
             for(int i = 0 ; i < keys.size(); i++){
                 keys[i].first -= 1;
             }
         }else if(up){
             for(int i = 0 ; i < keys.size(); i++){
                 keys[i].first += 1;
             }
         }else if(left){
             for(int i = 0 ; i < keys.size(); i++){
                 keys[i].second += 1;
             }
         }else if(right){
             for(int i = 0 ; i < keys.size(); i++){
                 keys[i].second -= 1;
             }
         }
        
        return false; // double check
    }
    for(int i = 0 ; i < keys.size(); i++){ //fit check
        if (keys[i].first < 0 || keys[i].first > N || keys[i].second < 0 || keys[i].second > N) {
            continue;
        }
        else if( locks[keys[i].first][keys[i].second] == 0 ){
            temp_home++;
        }
        else if(locks[keys[i].first][keys[i].second] == 1 ){
            isSucess = false;
            break;
        }
    }
    
    if (isSucess && (temp_home == home)) {
        return true;
    }
    
    
    
    if (clock) {
        if(dfs(true, false, false,false,false,false)) return true;
        if(dfs(false, false, true,false,false,false)) return true;
        if(dfs(false, false, false,true,false,false)) return true;
        if(dfs(false, false, false,false,true,false)) return true;
        if(dfs(false, false, false,false,false,true)) return true;
        
    }else if(rclock){
        if(dfs(false, true, false,false,false,false)) return true;
        if(dfs(false, false, true,false,false,false)) return true;
        if(dfs(false, false, false,true,false,false)) return true;
        if(dfs(false, false, false,false,true,false)) return true;
        if(dfs(false, false, false,false,false,true)) return true;
        
    }else if(down){
        if(dfs(true, false, false,false,false,false)) return true;
        if(dfs(false, true, false,false,false,false)) return true;
        if(dfs(false, false, true,false,false,false)) return true;
        if(dfs(false, false, false,false,true,false)) return true;
        if(dfs(false, false, false,false,false,true)) return true;
    }else if(up){
        if(dfs(true, false, false,false,false,false)) return true;
        if(dfs(false, true, false,false,false,false)) return true;
        if(dfs(false, false, false,true,false,false)) return true;
        if(dfs(false, false, false,false,true,false)) return true;
        if(dfs(false, false, false,false,false,true)) return true;
    }else if(left){
        if(dfs(true, false, false,false,false,false)) return true;
        if(dfs(false, true, false,false,false,false)) return true;
        if(dfs(false, false, true,false,false,false)) return true;
        if(dfs(false, false, false,true,false,false)) return true;
        if(dfs(false, false, false,false,true,false)) return true;
    }else if(right){
        if(dfs(true, false, false,false,false,false)) return true;
        if(dfs(false, true, false,false,false,false)) return true;
        if(dfs(false, false, true,false,false,false)) return true;
        if(dfs(false, false, false,true,false,false)) return true;
        if(dfs(false, false, false,false,false,true)) return true;
    }
    
    if (clock) {
        
        for(int i = 0 ; i < keys.size(); i++){
            temp.second = keys[i].first;
            temp.first = (M-(keys[i].second));
            keys[i] = temp;
        }
    }else if(rclock){
        
        for(int i = 0 ; i < keys.size(); i++){
            temp.second = (M-(keys[i].first));
            temp.first = keys[i].second;
            
            keys[i] = temp;
        }
    }else if(down){
        for(int i = 0 ; i < keys.size(); i++){
            keys[i].first -= 1;
        }
    }else if(up){
        for(int i = 0 ; i < keys.size(); i++){
            keys[i].first += 1;
        }
    }else if(left){
        for(int i = 0 ; i < keys.size(); i++){
            keys[i].second += 1;
        }
    }else if(right){
        for(int i = 0 ; i < keys.size(); i++){
            keys[i].second -= 1;
        }
    }
    
    return false;
}
