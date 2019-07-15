/*
- 找出矩阵中相同的行

序号：#61
难度：一般
时间限制：1000ms
内存限制：10M

描述
给一个由 0 和 1 组成的矩阵，其中有两行相同，仅通过遍历找到相同的行。
输出行数。

如：

1 0 0 1 0
0 1 1 0 0
1 0 0 1 0
0 0 1 1 0
0 1 0 0 0 
 
输出重复的行号为 1 和 3（行号从1开始）

输入
单组数据。表示由0和1组成的矩阵，使用换行符分隔行，使用空格分隔
每行内的元素。

矩阵必然存在且只有一对重复的行。

输出
输出 1 行，使用空格分隔代表行号的两个整数，表示重复的两行。

输入样例
1 0 0 1 0
0 1 1 0 0
1 0 0 1 0
0 0 1 1 0
0 1 0 0 0

输出样例
1 3
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


pair<int, int> RepeatedRow(vector<vector<int> > &data)
{
    if (data.size() <= 0 || data[0].size() <= 0)
        return pair<int, int>();

    int m = data.size(), n = data[0].size();
    int i, j, k;
    for (i = 0; i < m; i++)
        for (j = i + 1; j < m; j++)
        {
            for (k = 0; k < n; k++)
                if (data[i][k] != data[j][k])
                    break;

            if (k == n)
                return make_pair(i + 1, j + 1);
        }

    return pair<int, int>();
}


int main(int argc, char *argv[])
{
    string line;
    pair<int, int> res;

    // input case
    vector<vector<int> > data;
    while (getline(myfile, line))
    {
        stringstream ss(line);
        vector<int> row;
        int x;
        while (ss >> x)
            row.push_back(x);

        data.push_back(row);
    }

    for (auto &x: data)
        PrintVec(x);

    // result
    res = RepeatedRow(data);
    cout << res.first << ' ' << res.second << endl;

    return 0;
}