/*
- 发奖励

序号：#75
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
小明老师准备给一些得到小红花的小朋友发糖果做为奖励。 假设有n个
小朋友，每个小朋友拥有的小红花为m(n)个，他让这n个小朋友站成一排。
要求： 1.每个小朋友至少发一个糖果 2.如果一个小朋友比相邻的小朋
友小红花多，则发他的糖果也必须比相邻的多 问小明最少要发多少个糖果？

输入
每位小朋友的小红花数量，使用逗号(,)分隔

输出
最少需要发出的糖果

输入样例
96
19,9,35,74,22

输出样例
1
9
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


int LeastCandy(vector<int> &data)
{
    // least number of candies to distribute

    if (data.size() <= 0)
        return 0;

    int n = data.size(), i;
    vector<int> left(n, 1);

    for (i = 1; i < n; i++)
        if (data[i] > data[i - 1])
            left[i] = left[i - 1] + 1;

    for (i = n - 2; i >= 0; i--)
        if (data[i] > data[i + 1] && left[i] <= left[i + 1])
            left[i] = left[i + 1] + 1;

    int res = 0;
    for (i = 0; i < n; i++)
        res += left[i];

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        stringstream ss(line);
        int x;
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = LeastCandy(data);
        cout << res << endl;
    }

    return 0;
}