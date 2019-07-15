/*
- 字符串拼颜值

序号：#78
难度：困难
时间限制：1000ms
内存限制：10M

描述
现在是拼颜值的时代。 字符串也是如此，如果相邻字符相同出现次数越
多 (即 s[i] == s[i + 1] )，那么字符串越丑，反之，颜值就越高。
我们定义字符串的丑陋度计算方法：如果对于两个相邻字符相等，加1分。
否则不加分。 现在有一个由 a, b 和 ? 组成的字符串，计算丑陋度
前需要先将字符串中的所有 ? 替换成 a 或 b。请输出能得到最低的
字符串丑陋度。

举例： ?? 可表示为 ab，最低得分为0 a?a 可表示 aba，最低得分为0
abaa ，有一处相邻相等，最低得分为1

注意：最终分数越高表示字符串越丑陋

输入
由a, b, ?组成的字符串，长度为1 ~ 50

输出
字符串能得到丑陋分数的最低值

输入样例
??
a?a
abaa


输出样例
0
0
1
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <climits>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


int LeastUglyScore(string s)
{
    // least ugly score of string

    if (s.size() <= 0)
        return 0;

    // dp_a[i] indicates least ugly score of first i characters
    // of string s, when i-th character is 'a'
    // dp_b[i] indicates least ugly score of first i characters
    // of string s, when i-th character is 'b'

    int n = s.size(), i;
    int dp_a = INT_MAX - 1, dp_b = INT_MAX - 1;
    int a, b;

    if (s[0] == '?' || s[0] == 'a')
        dp_a = 0;
    if (s[0] == '?' || s[0] == 'b')
        dp_b = 0;

    for (i = 1; i < n; i++)
    {
        a = b = INT_MAX - 1;

        if (s[i] == 'a' || s[i] == '?')
            a = min(dp_a + 1, dp_b);
        if (s[i] == 'b' || s[i] == '?')
            b = min(dp_b + 1, dp_a);

        dp_a = a; dp_b = b;
    }

    return min(dp_a, dp_b);
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        cout << line << endl;

        // result
        res = LeastUglyScore(line);
        cout << res << endl;
    }

    return 0;
}