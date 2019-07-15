/*
- 抢劫！

序号：#85
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
你是一名专业劫匪，并且正在计划抢劫一条街道上的所有房子。每个房子
有一定数量的现金。 唯一能够阻止你的就是安保系统被触发，当有两个
相邻的房子在同一晚被劫时，安保系统才会自动触发。 现在给你一个正
整数数组表示每家现金数，请求出这一晚你能在不触发安保系统时抢到的
最大金额。

输入
由逗号(,)分隔的一串正整数，表示这一条街上每个房子内的现金数。

输出
一个正整数，表示你能抢到的最大金额。

输入样例
1,2

输出样例
2
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <cmath>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


int MaxMoney(vector<int> &data)
{
    // maximum money which the robber can rob in one night

    if (data.size() <= 0)
        return 0;

    // dp[i] indicates max money robbed of first i elements
    int n = data.size(), i;
    vector<int> dp(n + 1, 0);

    dp[1] = data[0];
    for (i = 2; i <= n; i++)
        dp[i] = max(data[i - 1] + dp[i - 2], dp[i - 1]);

    return dp[n];
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        vector<int> data;
        stringstream ss(line);
        int x;
        while (ss >> x)
            data.push_back(x);

        cout << line << endl;

        // result
        res = MaxMoney(data);
        cout << res << endl;
    }

    return 0;
}