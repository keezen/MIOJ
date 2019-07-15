/*
- 解救我 mi

序号：#102
难度：一般
时间限制：300ms
内存限制：32M

描述
给定一个只包含小写字母的字符串，现在我 mi 被众友商品牌的字符串围困
在其中，需要我们将字符串中的 mi 全部移除然后输出，保证最后输出的
字符串中没有 "mi"。

输入
一行数据包含一个字符串，长度 <= 100000，字符串仅包含小写字母。

输出
输出处理后的字符串

输入样例
huaweimivivo
chuizimmmiioppo
samsungmimiapple

输出样例
huaweivivo
chuizimoppo
samsungapple
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


string RemoveMi(string s)
{
    // remove 'mi' in string

    if (s.size() <= 0)
        return "";

    string res;

    for (int i = 0; i < s.size(); i++)
        if (!res.empty() && res.back() == 'm' && s[i] == 'i')
            res.pop_back();
        else
            res.push_back(s[i]);

    return res;
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
        res = RemoveMi(line);
        cout << res << endl;
    }

    return 0;
}