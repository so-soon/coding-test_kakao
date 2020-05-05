#include <string>
#include <vector>
#include <string.h>
#include <queue>
#include <utility>

using namespace std;


void dfs(int r1,int r2,int c1,int c2,int t,int d);
bool rotating(int r1,int r2,int c1,int c2,int std,int clock);
int board[103][103];
int visit[103][103][103][103];
int n,t1,t2;

int solution(vector<vector<int>> b) {
    int answer = 0;
    
    queue<pair<int,int>> q;
    queue<int> d;
    n = int(b.size());
    memset(board,1,sizeof(board));
    memset(visit,0,sizeof(visit));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n; j++){
            board[i+1][j+1] = b[i][j];
        }
    }
    
    //for(int i = 0 ; i < 6 ; i++) dfs(1, 1, 1, 2, 0, i);
    
    q.push(pair<int, int>(1,1));
    q.push(pair<int, int>(1,2));
    d.push(0);
    visit[1][1][1][2] = 1;
    int r1,r2,c1,c2,td;
    while (!q.empty()) {
        r1 = q.front().first;
        c1 = q.front().second;
        q.pop();
        r2 = q.front().first;
        c2 = q.front().second;
        q.pop();
        td = d.front();
        d.pop();
        
        if ((r1 == n && c1 == n) || (r2==n && c2==n)){
            answer = td;
            break;
        }
        else{
            if (board[r1][c1+1] == 0 && board[r2][c2+1] == 0){ //right
                if(visit[r1][c1+1][r2][c2+1] == 0 && visit[r2][c2+1][r1][c1+1] == 0){
                    visit[r1][c1+1][r2][c2+1] = 1;
                    q.push(pair<int,int>(r1,c1+1));
                    q.push(pair<int,int>(r2,c2+1));
                    d.push(td+1);
                }
            }
            if (board[r1][c1-1] == 0 && board[r2][c2-1] == 0){ //left
                if(visit[r1][c1-1][r2][c2-1] == 0 && visit[r2][c2-1][r1][c1-1] == 0){
                    visit[r1][c1+1][r2][c2+1] = 1;
                    q.push(pair<int,int>(r1,c1-1));
                    q.push(pair<int,int>(r2,c2-1));
                    d.push(td+1);
                }
            }
            if (board[r1-1][c1] == 0 && board[r2-1][c2] == 0){ //up
                if(visit[r1-1][c1][r2-1][c2] == 0 && visit[r2-1][c2][r1-1][c1] == 0){
                    visit[r1-1][c1][r2-1][c2] = 1;
                    q.push(pair<int,int>(r1-1,c1));
                    q.push(pair<int,int>(r2-1,c2));
                    d.push(td+1);
                }
            }
            if (board[r1+1][c1] == 0 && board[r2+1][c2] == 0){ //down
                if(visit[r1+1][c1][r2+1][c2] == 0 && visit[r2+1][c2][r1+1][c1] == 0){
                    visit[r1-1][c1][r2-1][c2] = 1;
                    q.push(pair<int,int>(r1+1,c1));
                    q.push(pair<int,int>(r2+1,c2));
                    d.push(td+1);
                }
            }
            if (rotating(r1, r2, c1, c2, 0, 1)) { //r1 clock
                if(visit[r1][c1][t1][t2] == 0 && visit[t1][t2][r1][c1] == 0){
                    visit[r1][c1][t1][t2] = 1;
                    q.push(pair<int,int>(r1,c1));
                    q.push(pair<int,int>(t1,t2));
                    d.push(td+1);
                }
            }
            if (rotating(r1, r2, c1, c2, 1, 1)) { //r2 clock
                if(visit[r2][c2][t1][t2] == 0 && visit[t1][t2][r2][c2] == 0){
                    visit[r2][c2][t1][t2] = 1;
                    q.push(pair<int,int>(t1,t2));
                    q.push(pair<int,int>(r2,c2));
                    d.push(td+1);
                }
            }
            if (rotating(r1, r2, c1, c2, 0, 0)) { //r1 rclock
                if(visit[r1][c1][t1][t2] == 0 && visit[t1][t2][r1][c1] == 0){
                    visit[r1][c1][t1][t2] = 1;
                    q.push(pair<int,int>(r1,c1));
                    q.push(pair<int,int>(t1,t2));
                    d.push(td+1);
                }
            }
            if (rotating(r1, r2, c1, c2, 1, 0)) { //r2 rclock
                if(visit[r2][c2][t1][t2] == 0 && visit[t1][t2][r2][c2] == 0){
                    visit[r2][c2][t1][t2] = 1;
                    q.push(pair<int,int>(t1,t2));
                    q.push(pair<int,int>(r2,c2));
                    d.push(td+1);
                }
            }
        }
        
    }
    
    
    return answer;
}
bool rotating(int r1,int r2,int c1,int c2,int std,int clock){
    if (r1 == r2) { // horizon
        if (std == 0) { //r1 std
            if (c1<c2) { //left std
                if (clock) { //clock
                    if (board[r1+1][c1] == 0 && board[r1+1][c1+1] == 0) {
                        t1 = r1+1;
                        t2 = c1;
                        return true;
                    }
                }else{ //rclock
                    if (board[r1-1][c1] == 0 && board[r1-1][c1+1] == 0) {
                        t1 = r1-1;
                        t2 = c1;
                        return true;
                    }
                }
            }else{ //right std
                if (clock) { //clock
                    if (board[r1-1][c1] == 0 && board[r1-1][c1-1] == 0) {
                        t1 = r1-1;
                        t2 = c1;
                        return true;
                    }
                }else{ //rclock
                    if (board[r1+1][c1] == 0 && board[r1+1][c1-1] == 0) {
                        t1 = r1+1;
                        t2 = c1;
                        return true;
                    }
                }
            }
        }else{//r2 std
            if (c1<c2) { //right std
                if (clock) { //clock
                    if (board[r2-1][c2] == 0 && board[r2-1][c2-1] == 0) {
                        t1 = r2-1;
                        t2 = c2;
                        return true;
                    }
                }else{ //rclock
                    if (board[r2+1][c2] == 0 && board[r2+1][c2-1] == 0) {
                        t1 = r2+1;
                        t2 = c2;
                        return true;
                    }
                }
            }else{ //left std
                if (clock) { //clock
                    if (board[r2+1][c2] == 0 && board[r2+1][c2+1] == 0) {
                        t1 = r2+1;
                        t2 = c2;
                        return true;
                    }
                }else{ //rclock
                    if (board[r2-1][c2] == 0 && board[r2-1][c2+1] == 0) {
                        t1 = r2-1;
                        t2 = c2;
                        return true;
                    }
                }
            }
        }
        
        
    }else{ // vertical
        if(std == 0){ //r1 std
            if(r1 < r2){ //up std
                if (clock) {//clock
                    if (board[r1][c1-1] == 0 && board[r1+1][c1-1] == 0) {
                        t1 = r1;
                        t2 = c1-1;
                        return true;
                    }
                }else{//rclock
                    if (board[r1][c1+1] == 0 && board[r1+1][c1+1] == 0) {
                        t1 = r1;
                        t2 = c1+1;
                        return true;
                    }
                }
            }else{ //down std
                if (clock) {//clock
                    if (board[r1][c1+1] == 0 && board[r1-1][c1+1] == 0) {
                        t1 = r1;
                        t2 = c1+1;
                        return true;
                    }
                }else{//rclock
                    if (board[r1][c1-1] == 0 && board[r1-1][c1-1] == 0) {
                        t1 = r1;
                        t2 = c1-1;
                        return true;
                    }
                }
            }
            
            
        }else{ //r2 std
            if(r1 > r2){ //up std
                if (clock) {//clock
                    if (board[r2][c2-1] == 0 && board[r2+1][c2-1] == 0) {
                        t1 = r2;
                        t2 = c2-1;
                        return true;
                    }
                }else{//rclock
                    if (board[r2][c2+1] == 0 && board[r2+1][c2+1] == 0) {
                        t1 = r2;
                        t2 = c2+1;
                        return true;
                    }
                }
            }else{ //down std
                if (clock) {//clock
                    if (board[r2][c2+1] == 0 && board[r2-1][c2+1] == 0) {
                        t1 = r2;
                        t2 = c2+1;
                        return true;
                    }
                }else{//rclock
                    if (board[r2][c2-1] == 0 && board[r2-1][c2-1] == 0) {
                        t1 = r2;
                        t2 = c2-1;
                        return true;
                    }
                }
            }
        }
    
    }
    return false;
}

