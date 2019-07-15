/*
- 第N个丑数

序号：#96
难度：困难
时间限制：1000ms
内存限制：10M

描述
把只包含因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，
但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按
从小到大的顺序的第N个丑数。

输入
输入一个正整数N，0<N<10000

输出
输出一个正整数S，S为第N个丑数

输入样例
1
2
10

输出样例
1
2
12
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


long int UglyNumber(int n)
{
    // n-th ugly number, starting from 1

    if (n < 1)
        return 0;

    vector<long int> ugly(n + 1, 0);
    int p2, p3, p5;

    p2 = p3 = p5 = 1; ugly[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        ugly[i] = min(ugly[p2] * 2, min(ugly[p3] * 3, ugly[p5] * 5));

        if (ugly[p2] * 2 == ugly[i])
            p2++;
        if (ugly[p3] * 3 == ugly[i])
            p3++;
        if (ugly[p5] * 5 == ugly[i])
            p5++;
    }

    return ugly[n];
}


int main(int argc, char *argv[])
{
    string line;
    long int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int n;
        ss >> n;

        cout << line << endl;

        // result
        res = UglyNumber(n);
        cout << res << endl;
    }

    return 0;
}