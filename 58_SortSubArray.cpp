/*
- 数组重排

序号：#58
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
给出一个无序数组，只要对其中的一段子数组进行升序排列，就可以使整个
数组变为升序。试求出这个子数组的长度。

举例： 有一个数组 [2, 6, 4, 8, 10, 9, 15]，只需对其子数组
[6, 4, 8, 10, 9] 进行升序排列，整个数组即可变为升序，所以返回
子数组的长度5。

输入
使用,分隔的一组整数，0<整数<100，0<整数个数<500。

输出
一个整数，表示子数组的长度。

输入样例
2,6,4,8,10,9,15

输出样例
5
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


int MinLengthToSort(vector<int> &data)
{
    // minimum length of sub-array which will make the
    // whole array sorted if sorted

    if (data.size() <= 1)
        return 0;

    int n = data.size();
    vector<int> left_max(n, 0);
    vector<int> right_min(n, 0);
    int i, j;

    // maximum value left to each position
    for (i = 1, left_max[0] = data[0]; i < n; i++)
        left_max[i] = max(data[i], left_max[i - 1]);

    // last element smaller than max of its left
    for (j = n - 1; j >= 0; j--)
        if (data[j] < left_max[j])
            break;

    // minimum value right to each position
    for (i = n - 2, right_min[n - 1] = data[n - 1]; i >= 0; i--)
        right_min[i] = min(data[i], right_min[i + 1]);

    // first element larger than min of its right
    for (i = 0; i < n; i++)
        if (data[i] > right_min[i])
            break;

    return j - i + 1;
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
        res = MinLengthToSort(data);
        cout << res << endl;
    }

    return 0;
}