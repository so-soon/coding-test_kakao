#include <string>
#include <vector>
using namespace std;


int solution(vector<int> stones, int k) {
    int answer = 0;
    int max = 400000000;
    int mid = 200000000;
    int min = 0;
    int co = 0 ;
    bool isAvail = false;
    
    while (min <= max) {
        mid = (max+min)/2;
        isAvail = true;
        co = 0;
        for(int i = 0 ; i < stones.size() ; i++){
            if ((stones[i]-mid) < 0 ) {
                co++;
            }else{
                co = 0;
            }
            if (co >= k) {
                isAvail = false;
                break;
            }
        }
        
        if (mid == 200000 && isAvail) {
            break;
        }
        else if (!isAvail) {
            
            max = mid-1;
            
        }else{
            min = mid+1;
            answer = mid;
        }
    }
    return answer;
}
