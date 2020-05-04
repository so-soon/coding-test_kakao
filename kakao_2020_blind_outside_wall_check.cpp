#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <deque>
using namespace std;

set<int> res;
vector<int> W;
vector<int> D;
vector<int> chk;
int N;
int init_pnt;
void dfs(int depth,int last_start,int maxn,int remain_pnt);
bool cmp(int x, int y);


int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = -1;
    sort(dist.begin(), dist.end(), cmp);
    deque<int> q;
    vector<int> t_v;
    for(int i = 0 ; i < weak.size() ;i++){
        q.push_back(weak[i]);
    }
    for(int i = 1 ; i  <= dist.size(); i++){ //how many friends
        for(int sh = 0 ; sh < weak.size(); sh++){
            
            t_v.clear();
            for(int a = 0 ; a < i ; a++) t_v.push_back(dist[a]);
            
            do{ //permutation dist.size() P i
                int pos = 0; //position which is needed to check
                for(int j = 0 ; j < i ; j++){ //combination friends (j'th friends)
                    int temp = t_v[j];
                    
                    for(int k = pos ; k < weak.size()-1; k++){ //go ahead
                        temp -= (q[k+1] - q[k]);
                        if (temp < 0) {
                            pos = k+1;
                            break;
                        }
                        else if(k == weak.size()-2){
                            return i;
                        }
                    }
                    if (pos == int(weak.size()-1) && (i-j) > 1) {
                        return i;
                    }
                    
                }
            }while(prev_permutation(t_v.begin(), t_v.end()));
            
            int t = q.front();
            q.pop_front();
            q.push_back(t+n);
        }
        
        
        
    }
    
    
    return answer;
}

bool cmp(int x, int y){
    return x>y;
}
