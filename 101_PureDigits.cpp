/*
- 纯位数

序号：#101
难度：非常难
时间限制：2000ms
内存限制：20M

描述
在数学中，所谓“纯位数”是指由相同位元重复而组成的自然数。比如在十进制
中，1，22，333，555 都是纯位数。 很显然，15 在十进制中不是一个纯位数，
但是在二进制 15(10) = 1111(2) 却是一个纯位数。

一个显然的事实是，对于正整数 N，其在 N+1 进制中必然是一个一位数，也就
必然是个纯位数。

对于一个正整数 N，试找出使其成为纯位数的最小进制 K。

输入
一个正整数 N (0 < N < 10^8)

输出
使 N 为纯位数的最小进制 K

输入样例
22
15

输出样例
10
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


int PureDigit_Brute(int n)
{
    // find the least base k to make the given number n a
    // pure-digit number

    if (n <= 0)
        return 0;

    int k, d, t;

    for (k = 2; k <= n; k++)
    {
        d = n % k;

        if (d == 0)
            continue;

        for (t = n / k; t > 0; t /= k)
            if (t % k != d)
                break;

        // least base
        if (t == 0)
            break;
    }

    return k;
}


int PureDigit(int n)
{
    // find the least base k to make the given number n a
    // pure-digit number

    if (n <= 0)
        return 0;

    if (n <= 2)
        return n + 1;

    int b, a, t;

    // base smaller than square root of n
    for (b = 2; b * b <= n; b++)
    {
        a = n % b;
        if (a == 0)
            continue;

        // every digit is a
        for (t = n / b; t > 0 && t % b == a; t /= b)
            ;

        if (t == 0)
            return b;
    }

    // base larger than square root of n, only consider two
    // digits
    a = b - 1;
    if (a * a >= n)
        a--;

    for (; a >= 1; a--)
        // n = a * (b + 1)
        if (n % a == 0)
            return n / a - 1;

    return n + 1;
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
        res = PureDigit(n);
        cout << res << endl;
    }

    return 0;
}