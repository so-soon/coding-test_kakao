#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<utility>
#include <string>
#include <string.h>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

vector<vector<string> > possible_string;
set<string> combi;
set<set<string> > res;

int solution(vector<string> user_id, vector<string> banned_id);
bool comp(string x, string y);
void dfs(int depth);

int solution(vector<string> user_id, vector<string> banned_id);
bool comp(string x, string y);
void dfs(int depth);



int solution(vector<string> user_id, vector<string> banned_id) {
    
    bool isEqual;
    int co = 0;
    vector<string> temp;
    
    sort(user_id.begin(),user_id.end(),comp);
    
    for(vector<string>::iterator banned_iter = banned_id.begin(); banned_iter != banned_id.end();++banned_iter){
        temp.clear();
        for(vector<string>::iterator user_iter = user_id.begin(); user_iter != user_id.end(); ++user_iter){
            isEqual = true;
            if ((*user_iter).length() < (*banned_iter).length()) {
                continue;
            }else if((*user_iter).length() > (*banned_iter).length()){
                break;
            }else{
                for(int i = 0 ; i < (*user_iter).length();i++){
                    if ((*banned_iter)[i] == '*') {
                        continue;
                    }else{
                        if ((*user_iter)[i] != (*banned_iter)[i]) {
                            isEqual = false;
                            break;
                        }
                    }
                }
                if(isEqual) {
                    temp.push_back((*user_iter));
                }
                
            }
        }
        possible_string.push_back(temp);
        co++;
    }
    
    dfs(0);
    
    
    return int(res.size());
}
void dfs(int depth){
    
    if(depth == possible_string.size()){
        if (combi.size() == possible_string.size()) {
            res.insert(combi);
            return;
        }else{
            return;
        }
    }else{
        for(int i = 0 ; i < possible_string[depth].size(); i++){
            if(!(combi.insert(possible_string[depth][i])).second) continue;
            dfs(depth+1);
            combi.erase(possible_string[depth][i]);
        }
        
    }
    
}

bool comp(string x, string y){
    return x.length() < y.length();
}
int combination(int r,int c){
    int parent = 1,child = 1;
    
    for(int i = c ; i >= 1 ; i--) parent*=i;
    for(int i = 0 ; i < c ; i++) child*=(r-i);
    
    return child/parent;
    
}
