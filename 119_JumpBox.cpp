/*
- 小米兔跳格子

序号：#119
难度：一般
时间限制：1000ms
内存限制：30M

描述
米兔爸爸为了让小米兔好好锻炼身体，便给小米兔设置了一个挑战——跳格子。

要吃到自己心爱的胡萝卜，小米兔需要跳过面前一些格子。现有 N 个格子，
个格子内都写上了一个非负数，表示当前最多可以往前跳多少格，胡萝卜就
放在最后一个格子上。米兔开始站在第 1 个格子，试判断米兔能不能跳到
最后一个格子吃到胡萝卜呢？

输入
输入为 N 个数字 (N<10)，用空格隔开，第 i 个数字 s_i (0≤s_i<=10)
表示米兔站在第 i 个格子上时，最多能往前跳的格数。

输出
若米兔能跳到最后一个格子上吃到胡萝卜，输出 “true“，否则输出 “false“

输入样例
2 0 1 0 0 3 4

输出样例
false
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


bool JumpBox(vector<int> &data)
{
    // whether can jump to end

    if (data.size() <= 0)
        return false;

    int n = data.size(), i, j;
    vector<bool> dp(n, false);

    dp[0] = true;
    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (data[j] + j == i)
            {
                dp[i] = true;
                break;
            }

    return dp[n - 1];
}


int main(int argc, char *argv[])
{
    string line;
    bool res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        vector<int> data;
        int x;
        while (ss >> x)
            data.push_back(x);

        cout << line << endl;

        // result
        res = JumpBox(data);
        cout << (res ? "true" : "false") << endl;
    }

    return 0;
}