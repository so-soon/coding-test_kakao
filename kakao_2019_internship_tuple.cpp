#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <deque>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <string.h>

using namespace std;


bool comp(pair<int,int> x, pair<int,int> y);

vector<int> solution(string s) {
    vector<int> answer;
    const char* str = s.c_str();
    vector<int> temp;
    vector<vector<int> > group;
    vector<pair<int,int> > group_len; // group index, group len
    map<int,bool> isUsed;
    string each_num;


    for(int i = 1 ; i < int(strlen(str))-1; i++){
        if(str[i] == '{'){
            temp.clear();
        }else if(str[i] == ','){
            continue;
        }else if(str[i] == '}'){
            group.push_back(temp);
            group_len.push_back(pair<int, int>(int(group.size())-1,int(temp.size())));
        }else{
            each_num.clear();
            while (str[i] != ',' && str[i] != '}') {
                each_num.append(to_string(int(str[i])-48));
                i++;
            }
            if(str[i] == '}') i--;
            temp.push_back(atoi(each_num.c_str()));


        }
    }

    sort(group_len.begin(), group_len.end(), comp);


    for (vector<pair<int,int> >::iterator iter = group_len.begin(); iter != group_len.end(); ++iter) {
        for (vector<int>::iterator iter2 = group[(*iter).first].begin(); iter2 != group[(*iter).first].end(); ++iter2) {
            if (isUsed.find((*iter2)) == isUsed.end()) {
                answer.push_back(*(iter2));
                isUsed[*(iter2)] = true;
            }
        }
    }

    return answer;
}
bool comp(pair<int,int> x, pair<int,int> y){
    return x.second < y.second;

}
