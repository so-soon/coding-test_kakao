#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    bool isCorrect;
    
    
    for(int i = 0 ; i < queries.size(); i++){
        answer.push_back(0);
        for(int j = 0 ; j < words.size(); j++){
            if (queries[i].length() != words[j].length()) {
                continue;
            }
            isCorrect = true;
            for(int c = 0; c < queries[i].size(); c++){
                if (queries[i][c] == '?') {
                    continue;
                }else if(queries[i][c] != words[j][c]){
                    isCorrect = false;
                    break;
                }
                
            }
            if(isCorrect) answer[i]++;
        }
        
    }
    return answer;
}
