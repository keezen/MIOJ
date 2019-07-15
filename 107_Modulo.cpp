/*
- 求余

序号：#107
难度：困难
时间限制：1000ms
内存限制：10M

描述
f(N) = 3^0 + 3^1 + ... + 3^N 求 f(N) 除以 1000000007 的余数

输入
N(1 <= N <= 10^9 + 7)的值

输出
f(N) 除以 1000000007 的余数

输入样例
10

输出样例
88573
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


const long int m = 1000000007;


long int A(int n)
{
    // a(n) = 3^n % (2 * m)

    if (n == 1)
        return 3 % (2 * m);

    long res = A(n / 2);
    res = (res * res) % (2 * m);

    if (n & 1)  // n is odd
    {
        res = (res * 3) % (2 * m);
    }

    return res;
}


long int Modulo(int n)
{
    // f(n) = 3^0 + ... + 3^n, find f(n) % 10^9+7

    if (n <= 0)
        return 0;

    long int res = A(n + 1);
    res = (res - 1) / 2;

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    long int res;

    // input case
    while (getline(myfile, line))
    {
        cout << line << endl;

        stringstream ss(line);
        int n;
        ss >> n;

        // result
        res = Modulo(n);
        cout << res << endl;
    }

    return 0;
}