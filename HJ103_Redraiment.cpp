/*
Redraiment是走梅花桩的高手。Redraiment可以选择任意一个起点，
从前到后，但只能从低处往高处的桩子走。他希望走的步数最多，
你能替Redraiment研究他最多走的步数吗？
本题含有多组样例输入
输入描述:
输入多行，先输入数组的个数，再输入相应个数的整数
输出描述:
输出结果
input:
6
2 5 1 5 4 5 
3
3 2 1
output:
3
1
*/
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
    int num;
    while (cin >> num)
    {
        vector<int> nums(num, 0);
        for(int i = 0; i < num; ++i){
            cin >> nums[i];
        }
        vector<int> dp(num, 0);
        dp[0] = 1;
        int maxVal = 1;
        for(int i = 1; i < num; ++i){
            for(int j = 0; j < i; ++j){
                if(nums[i] > nums[j]){
                    dp[i] =  max(dp[i], dp[j] +1);
                    maxVal = maxVal > dp[i] ? maxVal : dp[i];
                }
                    
            }
        }
        cout << maxVal <<endl;
    }
    
    return 0;
}