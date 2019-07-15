/*
- 找出面积最大的矩形

序号：#50
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
在一个平面图上，有多个宽度固定为1，高度不同的矩形并列排着，在这些
矩形所组成的图形中，能够切割出的最大矩形的面积是多少？ 数据范围：
0 < 高度 < 100

举例：高度为2,3,2的三个矩形所组成的图形，能够切割出的最大的矩形
面积为6。

输入
一组正整数，分别用逗号隔开，表示每个矩形的高度

输出
一个整数，表示组合成的最大的矩形面积

输入样例
2,3,2
5,6,7,8,3

输出样例
6
20
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


int MaxRectangle(vector<int> &data)
{
    // max area of rectangle given height

    if (data.size() <= 0)
        return 0;

    int n = data.size();
    // height[i][j] indicates min height in data[i:j]
    vector<vector<int> > height(n, vector<int>(n));
    int i, j;

    for (i = 0; i < n; i++)
    {
        height[i][i] = data[i];
        for (j = i + 1; j < n; j++)
            height[i][j] = min(height[i][j-1], data[j]);
    }

    // max area
    int area = 0;
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++)
            area = max(area, height[i][j] * (j - i + 1));

    return area;
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
        res = MaxRectangle(data);
        cout << res << endl;
    }

    return 0;
}