/*
- 买香蕉

序号：#98
难度：一般
时间限制：1000ms
内存限制：10M

描述
我是一个爱吃香蕉的强迫症。今天我要去水果店论筐买香蕉。 现在水果店
有好多筐香蕉，我的要求是买回来的每一筐里必须有相同数量的香蕉。

为了实现这个目标，你可以每次做两件事情。
1）放弃框里的一部分香蕉 2）连筐带香蕉放弃一整筐

我想知道我能得到最多多少香蕉。

输入
以空格分割的多个正整数，每个正整数表示一筐香蕉的总香蕉数

输出
最多能得到的香蕉数

输入样例
1 2 3
5 0 29 14

输出样例
4
29
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


int MostBanana(vector<int> &data)
{
    // most banana one can get, given number of bananas
    // in every basket

    if (data.size() <= 0)
        return 0;

    sort(data.begin(), data.end());

    int n = data.size();
    int res = 0;
    for (int i = 0; i < n; i++)
        res = max(res, data[i] * (n - i));

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        vector<int> data;
        int x;
        while (ss >> x)
            data.push_back(x);

        cout << line << endl;

        // result
        res = MostBanana(data);
        cout << res << endl;
    }

    return 0;
}