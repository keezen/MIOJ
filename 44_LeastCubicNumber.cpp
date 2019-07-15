/*
- 需要多少个立方数？

序号：#44
难度：困难
时间限制：1000ms
内存限制：10M

描述
给出一个数字 N (0≤N≤1000000)，将 N 写成立方数和的形式，求出
需要的最少的立方数个数。

举例： 
假设 N=17，可得 1+8+8 = 17，最少需要 3 个立方数，则输出 3
假设 N= 28，可得 1+1+1+1+8+8+8 = 28，需要 7 个立方数，
又得 1+27=28，需要 2 个立方数，所以最少立方数为 2，则输出 2

输入
一个正整数N(0≤N≤1000000)

输出
需要的最少的立方数个数（整型）

输入样例
1
17
28

输出样例
1
3
2
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


int LeastCubicNumber(int n)
{
    // least cubic numbers which n can be decomposed to

    if (n <= 0)
        return 0;

    // dp[i] indicates least cubic number which i can be
    // decomposed to
    vector<int> dp(n + 1, INT_MAX);
    vector<int> cubic;
    int i, j, k;

    // record cubic number
    for (i = 1; i * i * i <= n; i++)
        cubic.push_back(i * i * i);

    dp[0] = 0; dp[1] = 1; j = 0;
    for (i = 2; i <= n; i++)
        if (i == cubic[j + 1])
        {
            dp[i] = 1; j++;
        }
        else
            for (k = j; k >= 0; k--)
                dp[i] = min(dp[cubic[k]] + dp[i - cubic[k]], dp[i]);

    return dp[n];
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
        ss >> n;

        cout << n << endl;

        // result
        res = LeastCubicNumber(n);
        cout << res << endl;
    }

    return 0;
}