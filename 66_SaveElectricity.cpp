/*
- 节约用电

序号：#66
难度：困难
时间限制：1000ms
内存限制：10M

描述
为了节约用电，星际争霸里的神族（Protoss）每天需要在战斗结束后关闭
神族水晶（Pylon）的电源。 神族的电源开关是由一个巨大的网络与水晶
连接的，每个水晶对应一个开关，其中第 i 个开关会同时改变第 i 个水晶，
第 2 * i 个水晶以及第 3 * i 个水晶... 的状态（水晶和开关的编号
都从 1 开始）。 现在给出所有 n 个水晶的初始状态，问最少需要多少次
开关操作才能使所有水晶 变为关闭状态。

输入
一个字符串，包含 N 个字符（1<= N <=1000）。其中第 i 个字符为 
1 表示为初始状态为 开，0 表示为初始状态为 关。

输出
一个整数，表示操作开关使所有水晶变为 关闭状态 最少需要的操作次数。
如果不可能关掉所有开关，输出 -1。

输入样例
111111
101010101
11101110111011011110

输出样例
1
2
4
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


int MinOps(string s)
{
    // minimum operations to turn all characters to 0

    if (s.size() <= 0)
        return 0;

    int n = s.size();
    int res = 0;
    int i, j;

    // turn the switch from left to right
    for (i = 1; i <= n; i++)
        if (s[i - 1] == '1')
        {
            for (j = i; j <= n; j += i)
                s[j - 1] = 1 - (s[j - 1] - '0') + '0';
            res++;
        }

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int n;
    int res;

    // input case
    while (getline(myfile, line))
    {
        cout << line << endl;

        // result
        res = MinOps(line);
        cout << res << endl;
    }

    return 0;
}