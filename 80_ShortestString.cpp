/*
- 最短字符串

序号：#80
难度：非常难
时间限制：1000ms
内存限制：10M

描述
有一个字符串S，是由字符串T变换而来的。变换规则如下： 字符串S
起始为空字符串，每次取T任意大小的前缀连接到S的末尾，形成新的S。 
比如T=abcad，S起始为空 第一步：取T的前缀abcad加到S末尾，
S=abcad 第二步：取T的前缀abc加到S末尾，S=abcadabc 第三步：
取T的前缀abcad加到S末尾，S=abcadabcabcad

现在告诉你字符串S，请你给出可以变换成S的长度最小的字符串T

输入
输入一个非空字符串S，字符串S的长度L<100000,只包含小写字母
例如abcadabcabcad

输出
一个字符串T

输入样例
abcadabcabcad
abcababcd
aaaaaa

输出样例
abcad
abcd
a
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


string ShortestString(string s)
{
    // shortest string which can generates string s

    if (s.size() <= 0)
        return "";

    // start of every segment
    vector<int> seg_start;
    int i, j, k;
    for (i = 0; i < s.size(); i++)
        if (s[i] == s[0])
            seg_start.push_back(i);

    // dp[i] indicates shortest string for first i segments
    int n = seg_start.size();
    seg_start.push_back(s.size());
    vector<string> dp(n + 1, "");
    string first, second, shortest, longer;
    for (i = 1; i <= n; i++)
    {
        shortest = "";
        for (j = 0; j <= i - 1; j++)
        {
            first = dp[j];
            second = s.substr(seg_start[j], seg_start[i] - seg_start[j]);

            int len = min(first.size(), second.size());
            if (first.substr(0, len) == second.substr(0, len))
            {
                longer = first.size() > second.size() ? first : second;
                if (shortest.size() == 0 || shortest.size() > longer.size())
                    shortest = longer;
            }
        }

        dp[i] = shortest;
    }

    return dp[n];
}


int main(int argc, char *argv[])
{
    string line;
    string res;

    // input case
    while (getline(myfile, line))
    {
        cout << line << endl;

        // result
        res = ShortestString(line);
        cout << res << endl;
    }

    return 0;
}