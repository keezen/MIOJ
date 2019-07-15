/*
- N!

序号：#89
难度：困难
时间限制：1500ms
内存限制：64M

描述
给定一个整数N，求N!的末尾有多少个0.

输入
输入为一个整数N，1 <= N <= 1000000000.

输出
输出为N!末尾0的个数

输入样例
3
60
100
1024
23456
8735373

输出样例
0
14
24
253
5861
2183837
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


int TrailingZeros(int n)
{
    // number of trailing zeros of n!

    if (n < 5)
        return 0;

    // number of factor 2 and 5 in 1~n
    int fac2 = 0, fac5 = 0;
    int i;

    for (i = n / 2; i > 0; i /= 2)
        fac2 += i;

    for (i = n / 5; i > 0; i /= 5)
        fac5 += i;

    return min(fac2, fac5);
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int n;
        ss >> n;

        cout << line << endl;

        // result
        res = TrailingZeros(n);
        cout << res << endl;
    }

    return 0;
}