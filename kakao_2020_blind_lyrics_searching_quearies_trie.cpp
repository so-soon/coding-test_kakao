#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <map>

using namespace std;
map<string , int> res;

vector<int> solution(vector<string> words, vector<string> queries);
struct Trie {
    bool isWord;
    int depth;
    Trie* next[27];
    string values;
    
    Trie(int before_depth): isWord(false) , depth(before_depth+1), values(""){
        memset(next,0,sizeof(next));
    }
    ~Trie(){
            for(int i=0;i<27;i++){
                if(next[i])
                    delete next[i];
            }
        }
    
    void insert(string key){
        if (depth >= (int(key.length())-1)) {
            isWord = true;
            values = key;
            res[key] = 0;
            return;
        }
        if (key[depth+1] == '?') {
            if (next[26] == NULL) {
                next[26] = new Trie(depth);
            }
            next[26]->insert(key);
        }else{
            int curr = key[depth+1]-'a';
            if (next[curr] == NULL) {
                next[curr] = new Trie(depth);
            }
            next[curr]->insert(key);
        }
    }
    void find(string word){
        if (isWord) {
            if (depth == (int(word.length())-1)) {
                res[values]++;
                return;
            }
        }
        int curr;
        if(word[depth+1] == '?') curr = 26;
        else curr = word[depth+1]-'a';
        
        if (next[curr] != NULL) {
            next[curr]->find(word);
        }
        
        if (curr != 26 && next[26]!=NULL) {
            next[26]->find(word);
        }
    }
};

/*
 ["frodo", "front", "frost", "frozen", "frame", "kakao"]    ["fro??", "????o", "fr???", "fro???", "pro?"]    [3, 2, 4, 1, 0]
 */
vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer(queries.size(),0);
    Trie* root = new Trie(-2);
    
    for(int i = 0 ; i < queries.size(); i++){
        root->insert(queries[i]);
    }
    
    for(int i = 0 ; i < words.size(); i++){
        root->find(words[i]);
    }
    
    
    for(int i = 0 ; i < queries.size(); i++){
        answer[i] = res[queries[i]];
    }
    return answer;
}
