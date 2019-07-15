/*
- 打羽毛球的小爱同学

序号：#114
难度：困难
时间限制：1000ms
内存限制：100M

描述
小爱同学加入了小米羽毛球俱乐部。羽毛球俱乐部里有nn个同学, 其中aa个
同学没有羽毛球也没有球拍，bb个同学只有一个羽毛球拍，cc个同学只有一
个羽毛球，d个同学既有一个羽毛球又有一个羽毛球拍，a+b+c+d=n.

这周，俱乐部组织同学们一起玩羽毛球，每个同学可以选择参加或者不参加，
获得最终胜利的同学可获得 Yeelight 智能护眼台灯一个。羽毛球场有且
仅有 1 个，为了打羽毛球，参加活动的同学一共至少要有 1 个羽毛球和
2 个球拍，如果没有足够的球或球拍，这个活动会被取消。

易知，同学参加活动的可能情况有2^n种（每个人可以选择参加或不参加）。
现在，小爱想知道2^n种可能里，有多少种情况下活动会被取消。

输入
4个非负整数a, b, c, d以空格分隔。

数据范围: 0≤a,b,c,d≤10000000,a+b+c+d≥1

输出
2^n种可能里，活动被取消的情况数量。答案可能很大，请输出答案
除以 998244353 之后的余数。

输入样例
1 1 1 1

输出样例
12
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


const long int m = 998244353;


long int F(int n)
{
    // F(n) = 2^n % m

    long int res;
    const int b = 2;

    if (n == 0)
        return 1 % m;

    if (n == 1)
        return b % m;

    res = F(n / b);
    res = (res * res) % m;

    if (n & 1)  // n is odd
        res = (res * (b % m)) % m;

    return res;
}


long int Cancellation(int a, int b, int c, int d)
{
    // number of cancellation circumstances,
    // f(a, b, c, d) = 2^a * (2^b + (b+d+1) * 2^c - (b+1))

    if (a < 0 || b < 0 || c < 0 || d < 0)
        return 0;

    int n = a + b + c + d;

    if (n < 1)
        return 0;

    long int res = 0, t;

    t = F(a + b);  // 2^(a+b) % m
    res = (res + t) % m;
    t = (F(a + c) * ((b + d + 1) % m)) % m;  // 2^(a+c) * (b+d+1) % m
    res = (res + t) % m;
    t = (F(a) * ((b + 1) % m)) % m;  // 2^a * (b+1) % m
    res = (res - t + m) % m;

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    long int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int a, b, c, d;
        ss >> a; ss >> b; ss >> c; ss >> d;

        cout << line << endl;

        // result
        res = Cancellation(a, b, c, d);
        cout << res << endl;
    }

    return 0;
}