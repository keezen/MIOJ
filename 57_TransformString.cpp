/*
- 玩转字符串

序号：#57
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
是的，又是字符串。

规定两种操作：

一种是在字符串末尾加字符 A。
另一种是先反转整个字符串，再给字符串末尾加上字符 B。
给出一个初始串 S，一个终点串 T。问能否通过这两个操作从 S 变换
到 T。如果可以输出 1（弱初始串和终点串相同，视为可以变换），不
可以输出 0。

输入
由英文空格分隔的两个字符串，每个字符串只由 AB 两个字符组成

输出
1 或 0，表示可以变换，或不可以变换。

输入样例
AB ABB
AAAB AAABA
AABB BBAAB

输出样例
0
1
1
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ' ';
    cout << data.back() << endl;
}


bool Transformable(string s, string t)
{
    // whether string s can be transformed to string t

    if (s.size() > t.size())
        return false;

    if (s.size() == t.size())
        return s == t;

    if (s.size() == 0)
        return true;

    // s shorter than t

    // reduce backward
    int m = s.size(), n = t.size();
    int i = 0, j = n - 1, k = 1;

    while (j - i + 1 > m)
    {
        char c = (k == 1 ? t[j--] : t[i++]);
        if (c == 'B')
            k = 1 - k;
    }

    string t1 = t.substr(i, m);
    if (k == 0)
        reverse(t1.begin(), t1.end());

    return s == t1;
}


int main(int argc, char *argv[])
{
    string line;
    string s, t;
    bool res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        ss >> s; ss >> t;

        cout << s << endl << t << endl;

        // result
        res = Transformable(s, t);
        cout << res << endl;
    }

    return 0;
}