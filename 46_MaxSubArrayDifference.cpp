/*
- 数组差

序号：#46
难度：困难
时间限制：1000ms
内存限制：10M

描述
给定一个整数数组，找出两个不重叠的子数组A和B，使两个子数组元素和的差的绝对值
|SUM(A) - SUM(B)| 最大。 返回这个最大的差值。 例如： 有一个数组{1, 2, -3, 1}，
可以从中找出两个子数组A = {1, 2}与B = {-3}，这两个子数组的元素和分别为
SUM(A) = 3，SUM(B) = -3，因此可以求得差的最大值 |SUM(A) - SUM(B)| = 6。

输入
使用逗号(,)分隔的一个整数数组

输出
一个整数，表示两个子数组元素和的差的最大值

输入样例
1,2,-3,1

输出样例
6
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


int MaxSubArrDiff(vector<int> &data)
{
    if (data.size() <= 1)
        return 0;

    int n = data.size(), i;

    // max sum of sub array left to i-th element
    vector<int> left_max(n, 0);
    for (i = 1, left_max[0] = data[0]; i < n; i++)
        left_max[i] = max(data[i], left_max[i - 1] + data[i]);
    for (i = 1; i < n; i++)
        left_max[i] = max(left_max[i - 1], left_max[i]);

    // min sum of sub array left to i-th element
    vector<int> left_min(n, 0);
    for (i = 1, left_min[0] = data[0]; i < n; i++)
        left_min[i] = min(data[i], left_min[i - 1] + data[i]);
    for (i = 1; i < n; i++)
        left_min[i] = min(left_min[i - 1], left_min[i]);

    // max sum of sub array right to i-th element
    vector<int> right_max(n, 0);
    for (i = n - 2, right_max[n - 1] = data[n - 1]; i >= 0; i--)
        right_max[i] = max(data[i], right_max[i + 1] + data[i]);
    for (i = n - 2; i >= 0; i--)
        right_max[i] = max(right_max[i + 1], right_max[i]);

    // min sum of sub array right to i-th element
    vector<int> right_min(n, 0);
    for (i = n - 2, right_min[n - 1] = data[n - 1]; i >= 0; i--)
        right_min[i] = min(data[i], right_min[i + 1] + data[i]);
    for (i = n - 2; i >= 0; i--)
        right_min[i] = min(right_min[i + 1], right_min[i]);

    // max difference of sub-arrays left and right to i-th element
    int diff = 0;
    for (i = 0; i < n - 1; i++)
        diff = max(diff, max(abs(left_min[i] - right_max[i+1]),
            abs(left_max[i] - right_min[i+1])));

    return diff;
}


int main(int argc, char *argv[])
{
    string line;
    int x;
    int res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        stringstream ss(line);
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = MaxSubArrDiff(data);
        cout << res << endl;
    }

    return 0;
}