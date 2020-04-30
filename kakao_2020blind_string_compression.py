def solution(s):
    answer = len(s)

    for i in range(1,len(s)+1):
        temp = s[0:i]
        t_ans = 0
        co = 1
        ans_str = ""
        for j in range(i,len(s),i):
            t = s[j:j+i]
            if temp == t:
                co += 1
            else :
                if co != 1:
                    ans_str+=str(co)+temp
                else :
                    ans_str+=temp
                co = 1
                temp = t

            if j+i >= len(s):
                if co != 1:
                    ans_str += str(co) + temp
                else:
                    ans_str += temp

        if ans_str != '' : answer = min(answer,len(ans_str))




    return answer
