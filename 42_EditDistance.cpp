/*
- 字符串替换

序号：#42
难度：非常难
时间限制：5000ms
内存限制：10M

描述
给出两个字符串S1、S2，对S1进行插入、删除、替换的操作，每次只能操作一个字符，
最少操作多少步，使其等于S2。

举例： S1 = abc, S2 = badc，abc插入字符b变为 babc，字符b替换为字符d变
为 badc，估最少操作两步。

输入
两个字符串S1、S2，以逗号（,）分开，操作S1使其等于S2

输出
一个整数，表示最少操作步数

输入样例
abc,badc

输出样例
2
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ' ';
    cout << data.back() << endl;
}


int EditDistance(string a, string b)
{
    // edit distance of string a and b

    if (a.size() <= 0 || b.size() <= 0)
        return 0;

    // dp[i][j] indicates the edit distance of first i characters
    // of string a and first j characters of string b
    int m = a.size(), n = b.size();
    vector<int> dp(n + 1, 0);
    int p, t;
    int i, j;

    for (j = 0; j <= n; j++)
        dp[j] = j;

    for (i = 1; i <= m; i++)
    {
        p = dp[0];  // dp[i-1][j-1]
        dp[0] = i;
        for (j = 1; j <= n; j++)
        {
            t = dp[j];  // dp[i-1][j]

            if (a[i - 1] == b[j - 1])
                dp[j] = p;
            else
                dp[j] = 1 + min(p, min(dp[j - 1], dp[j]));

            p = t;
        }
    }

    return dp[n];
}


int main(int argc, char *argv[])
{
    string line;
    string a, b;
    int res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        stringstream ss(line);
        ss >> a; ss >> b;

        cout << a << endl << b << endl;

        // result
        res = EditDistance(a, b);
        cout << res << endl;
    }

    return 0;
}