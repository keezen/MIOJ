/*
- 数7游戏

序号：#63
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
数 7 游戏，从 1 开始报数，遇到 7 的倍数以及含 7 的数字直接 pass。 
写出一个算法，计算第 N 个数是多少。

输入
一个正整数 N，表示需要计算的数为第 N 个数，1 <= N <= 100000。

输出
第 N 个数的数值。

输入样例
1
7
8
24
123
3467
88888
99999

输出样例
1
8
9
30
169
5493
168223
198026
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


int SkipSeven(int n)
{
    // n-th number ignoring multiples of 7 and number
    // containing 7

    if (n <= 0)
        return 0;

    int count = 1, i = 1, j;
    while (i < INT_MAX && count < n)
    {
        i++;

        // multiple of 7
        if (i % 7 == 0)
            continue;

        // containing 7
        for (j = i; j > 0 && j % 10 != 7; j /= 10) ;
        if (j > 0) continue;

        count++;
    }

    return i == INT_MAX ? 0 : i;
}


int main(int argc, char *argv[])
{
    string line;
    int n;
    int res;

    // input case
    while (myfile >> n)
    {
        cout << n << endl;

        // result
        res = SkipSeven(n);
        cout << res << endl;
    }

    return 0;
}