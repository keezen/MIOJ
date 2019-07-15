/*
- 小米兔的轨迹

序号：#136
难度：一般
时间限制：1000ms
内存限制：80M

描述
有 N⋅M 的一个矩阵，小米兔今天很开心，从矩阵左上角的第一个位置开始
顺时针从外向里走，很快就走遍了所有的位置，可是小米兔想知道自己走过
的轨迹，你能告诉小米兔它走过的轨迹吗？

（输出一个字符串，由小米兔走过的位置的值组成，用空格分隔。）

输入
单组输入。

第 1 行是 2 个整数，分别代表 N 和 M 的值；
第 2 ~ N + 1 行，表示 N⋅M 的矩阵中的每一行。

输出
输出为一个字符串，由小米兔走过的位置的值组成，用空格分隔。

输入样例
3 3
1 2 3
4 5 6
7 8 9

输出样例
1 2 3 6 9 8 7 4 5
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


ostream & operator<<(ostream &os, pair<int, int> &rhs)
{
    cout << rhs.first << ',' << rhs.second;
    return os;
}


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    // print out a vector
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i];
        cout << ((i == data.size() - 1) ? eol : sep);
    }
}


vector<int> TraverseMatrix(vector<vector<int> > &mat)
{
    // traverse matrix clockwise

    if (mat.size() <= 0 || mat[0].size() <= 0)
        return vector<int>();

    vector<int> path;
    int n = mat.size(), m = mat[0].size();
    int top = 0, bottom = n - 1, left = 0, right = m - 1;
    int i, j;

    while (top <= bottom && left <= right)
    {
        for (j = left; j < right; j++)  // top
            path.push_back(mat[top][j]);

        for (i = top; i <= bottom; i++)  // right
            path.push_back(mat[i][right]);

        if (top < bottom)
            for (j = right - 1; j >= left; j--)  // bottom
                path.push_back(mat[bottom][j]);

        if (left < right)
            for (i = bottom - 1; i > top; i--)  // left
                path.push_back(mat[i][left]);

        top++; bottom--; left++; right--;
    }

    return path;
}


int main(int argc, char *argv[])
{
    string line;
    vector<int> res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int n, m;
        ss >> n >> m;

        vector<vector<int> > mat;
        while (getline(myfile, line))
        {
            stringstream ss2(line);
            vector<int> row;
            int x;
            while (ss2 >> x)
                row.push_back(x);
            mat.push_back(row);
        }

        for (auto &x: mat)
            PrintVec(x);

        // result
        res = TraverseMatrix(mat);
        PrintVec(res);
    }

    return 0;
}