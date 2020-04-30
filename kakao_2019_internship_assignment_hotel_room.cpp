#include<vector>
#include<map>

using namespace std;


long long find_f(long long x);

map<long long, long long> root;


vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    long long temp;
    for(vector<long long>::iterator iter = room_number.begin(); iter != room_number.end(); ++iter){
        temp = find_f((*iter));
        answer.push_back(temp);
        root[temp] = temp+1;
        
    }
    
    return answer;
}
long long find_f(long long x){
    if (root[x] == 0) {
        return x;
    }
    return root[x] = find_f(root[x]);
    
}
