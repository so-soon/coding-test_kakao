#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    
    int answer = 0;
    vector<int> basket;
    
    int target_crain;
    
    for(vector<int>::iterator iter = moves.begin(); iter!=moves.end(); ++iter){
        target_crain = (*iter)-1;
        
        //catch doll
        
        for(int i = 0 ; i < board[0].size(); i++){
            if(board[i][target_crain] == 0) continue;
            else{
                //if boom
                if (!basket.empty()) {
                    if(basket.back() == board[i][target_crain]){
                        answer+=2;
                        basket.pop_back();
                    }
                    else basket.push_back(board[i][target_crain]);
                }else basket.push_back(board[i][target_crain]);
                
                
                board[i][target_crain] = 0;
                break;
            }
        }
    }
    
    
    return answer;
}
