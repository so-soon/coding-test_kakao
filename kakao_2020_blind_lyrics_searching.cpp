#include <string>
#include <vector>
#include <algorithm>
#include <string.h>


using namespace std;

vector<int> answer;

int n = 0;
vector<int> solution(vector<string> words, vector<string> queries);
struct Trie {
    bool isWord;
    int num;
    Trie* next[27];
    
    Trie(): isWord(false) , num(-1){
        memset(next,0,sizeof(next));
    }
    ~Trie(){
            for(int i=0;i<27;i++){
                if(next[i])
                    delete next[i];
            }
        }
    
    void insert(const char* key){
        if ((*key) == '\0') {
            isWord = true;
            if (num != -1) {
                answer[n] = -(num+1);
            }
            else num = n;
            return;
        }
        if ((*key) == '?') {
            if (next[26] == NULL) {
                next[26] = new Trie();
            }
            next[26]->insert(key+1);
        }else{
            int curr = (*key)-'a';
            if (next[curr] == NULL) {
                next[curr] = new Trie();
            }
            next[curr]->insert(key+1);
        }
    }
    void find(const char* word){
        
        if (isWord) {
            if (*(word) == '\0') {
                answer[num]++;
                return;
            }
        }
        int curr;
        curr = *(word)-'a';
        
        if (next[curr] != NULL) {
            next[curr]->find(word+1);
        }
        
        if (next[26]!=NULL) {
            Trie* temp = next[26];
            while (temp->next[26] != NULL) {
                word++;
                if (temp->next[(*word)-'a'] != NULL) {
                    temp->next[(*word)-'a']->find(word+1);
                }
                temp = temp->next[26];
                
            }
            
            temp->find(word+1);
        }
        
        
    }
};

Trie* tree[10001];


vector<int> solution(vector<string> words, vector<string> queries) {
    
    
    
    for(int i = 0 ; i < queries.size(); i++){
        answer.push_back(0);
        if(tree[queries[i].size()] == NULL) tree[queries[i].size()] = new Trie();
        const char* temp = queries[i].c_str();
        tree[queries[i].size()]->insert(temp);
        n++;
    }
    
    for(int i = 0 ; i < words.size(); i++){
        if(tree[words[i].size()] == NULL) continue;
        const char* temp = words[i].c_str();
        tree[words[i].size()]->find(temp);
    }
    
    for(int i = 0 ; i < answer.size(); i++){
        if(answer[i] < 0 ){
            answer[i] = answer[(-answer[i])-1];
        }
    }
    
    
    return answer;
}
