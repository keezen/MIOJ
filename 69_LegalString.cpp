/*
- 合法字符串

序号：#69
难度：困难
时间限制：1000ms
内存限制：10M

描述
假设字符串只可能由A、B、C三个字母组成，如果任何紧邻的三个字母
相同，就非法。求长度为 N 的合法字符串有多少个？ 比如： ABBBCA 
是非法，ACCBCCA 是合法的。

输入
一个正整数 N，设 0 <= N <= 40

输出
长度为N的合法字符串的个数

输入样例
1
2
4

输出样例
3
9
66
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


long int NumberOfLegalString(int n)
{
    // number of legal strings of size n

    if (n <= 0)
        return 0;

    long int uni, bi;
    int i;

    uni = 3, bi = 0;
    for (i = 1; i < n; i++)
    {
        long int t = uni;
        uni = bi * 2 + uni * 2;
        bi = t;
    }

    return uni + bi;
}


int main(int argc, char *argv[])
{
    string line;
    int n;
    long int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        ss >> n;

        cout << n << endl;

        // result
        res = NumberOfLegalString(n);
        cout << res << endl;
    }

    return 0;
}