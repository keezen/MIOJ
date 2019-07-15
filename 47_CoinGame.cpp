/*
- 硬币比赛

序号：#47
难度：困难
时间限制：1000ms
内存限制：10M

描述
有 n 个不同价值的硬币排成一条线。有 A 与 B 两个玩家，指定由 A 开始轮流
（A 先手，然后 B，然后再 A..）从左边依次拿走 1 或 2 个硬币（不能不拿，
也不能拿其他个数），直到没有硬币为止。最后计算 A 与 B 分别拿到的硬币总价值，
价值高的人获胜。

请依据硬币的排列情况来判定，先手的玩家 A 能否找到必胜策略？

输入
使用逗号(,)分隔的一个正整数数组，表示这排硬币的排列情况与对应价值

输出
true 或 false（字符类型），表示玩家 A 能否找到必胜策略

输入样例
1,2,2
1,2,4

输出样例
true
false
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ' ';
    cout << data.back() << endl;
}


bool FirstWin(vector<int> &data)
{
    // whether first selector can win the coin game

    if (data.size() <= 2)
        return true;

    int n = data.size();
    int i;

    // rev[i] indicates the sum of data[i:]
    vector<int> rev(n, 0);
    rev[n - 1] = data[n - 1];
    for (i = n - 2; i >= 0; i--)
        rev[i] = rev[i + 1] + data[i];

    // dp[i] indicates the maximum coin sum which the first player
    // starting at position i can get
    vector<int> dp(n, 0);
    dp[n - 1] = data[n - 1]; dp[n - 2] = data[n - 1] + data[n - 2];
    for (i = n - 3; i >= 0; i--)
        dp[i] = max(rev[i + 1] - dp[i + 1] + data[i],
            rev[i + 2] - dp[i + 2] + data[i] + data[i + 1]);

    return dp[0] * 2 > rev[0];
}


int main(int argc, char *argv[])
{
    string line;
    int x;
    bool res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        stringstream ss(line);
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = FirstWin(data);
        cout << (res ? "true" : "false") << endl;
    }

    return 0;
}