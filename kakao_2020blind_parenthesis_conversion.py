#include <string>
#include <vector>
#include <utility>

using namespace std;
string dfs(string p);
bool isRight(string a);
pair<string,int> getMinimumBlancedStr(string a);
string changeParen(string a);

string solution(string p) {
    string answer = "";
    if (isRight(p)) return p;
    else answer = dfs(p);
    
    
    return answer;
}

string dfs(string p){
    string u,v,temp="";
    pair<string,int> t_pair;
    
    if(p.size() == 0) return "";
    
    t_pair = getMinimumBlancedStr(p);
    u = t_pair.first;
    if (t_pair.second == p.size()) {
        v = "";
    }else v = p.substr((t_pair.second)+1);
    
    if (isRight(u)) {
        temp.append(u);
        temp.append(dfs(v));
    }else {
        temp.append("(");
        temp.append(dfs(v));
        temp.append(")");
        temp.append(changeParen(u));
    }
    
    
    
    
    return temp;
    
}

string changeParen(string a){
    string temp = a.substr(1,a.size()-2);
    
    for(int i = 0 ;  i < temp.size(); i++){
        if (temp[i] == '(') {
            temp[i] = ')';
        }else temp[i] = '(';
    }
    
    return temp;
}

bool isRight(string a){
    vector<char> s;
    for(int i = 0 ; i < a.size() ; i++){
        if (a[i] == ')') {
            if (s.empty()) {
                return false;
            }
            s.pop_back();
        }else{
            s.push_back(a[i]);
        }
    }
    
    return s.empty();
}

pair<string,int> getMinimumBlancedStr(string a){
    int co_close = 0;
    int co_open = 0;
    
    for(int i = 0 ; i < a.size() ; i++){
        if (a[i] == '(') co_open++;
        else co_close++;
        
        if(co_close == co_open) return pair<string,int>(a.substr(0,i+1),i);
    }
    return pair<string,int>(a,a.size());
}
