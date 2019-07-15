/*
- 开始报数

序号：#67
难度：一般
时间限制：1000ms
内存限制：10M

描述
有 500 个小孩围成一圈，编号从 1 到 500，从第一个开始报数：
1，2，3，1，2，3，1，2，3，……每次报到 3 的小孩退出。问
第 n 个被淘汰的小孩，在最开始 500 人里是的编号是几？

输入
正整数 N，表示要计算的为第 N 个淘汰的小孩的编号，0 < N <= 500

输出
第 N 个淘汰的小孩的编号

输入样例
1
2
206
311

输出样例
3
6
176
223
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


int NthCirclePop(int n)
{
    // n-th element popped from circle, when popping every
    // 3 elements from a circle of size 500

    int N = 500, M = 3;

    if (n <= 0 || n > N)
        return 0;

    // f(N, n, m) = [f(N-1, n-1, m) + m] % N
    int i, j;
    int res = (M - 1) % (N - n + 1);

    for (i = 1; i < n; i++)
    {
        j = N - n + i;
        res = (res + M) % (j + 1);
    }
    res++;

    return res;
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
        res = NthCirclePop(n);
        cout << res << endl;
    }

    return 0;
}