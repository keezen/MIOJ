/*
- 跳跳看

序号：#64
难度：困难
时间限制：1000ms
内存限制：10M

描述
给定一个数字串 (均为正整数)，现在需要从第一个数跳跃到最后一个，
所在位置的数字表示可以跳跃的最大步数。求出从第一个位置跳跃到最
后位置所需的最少步数。

输入
一个数字串，每个数字用空格隔开，如 1 2 3 4 5 6 7。

输出
需要从第一位 1 跳到最后一位 7，则 1->2->4->7，最少需要3步。

输入样例
1 2 3 4 5 6 7
3 1 1 1 1
2 3 2 3 2 3 2 3 2 3
2 3 4 2 5 2 3 5 1 2 3 4

输出样例
3
2
5
4
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <climits>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ' ';
    cout << data.back() << endl;
}


int MinSteps(vector<int> &data)
{
    // minimum steps jumping from first position to
    // last position

    if (data.size() <= 0)
        return 0;

    // dp[i] indicates minimum steps jumping from first
    // to i-th position
    int n = data.size();
    vector<int> dp(n, 0);
    int i, j;

    for (i = 0; i < n; i++)
        dp[i] = i;

    for (i = 0; i < n; i++)
        for (j = i + 1; j < n && j <= i + data[i]; j++)
            dp[j] = min(dp[j], dp[i] + 1);

    return dp[n - 1];
}


int main(int argc, char *argv[])
{
    string line;
    int n;
    int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int x;
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = MinSteps(data);
        cout << res << endl;
    }

    return 0;
}