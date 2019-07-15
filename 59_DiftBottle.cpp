/*
- 漂流瓶

序号：#59
难度：非常难
时间限制：1000ms
内存限制：10M

描述
老板要宣传公司新产品，决定在将广告放在漂流瓶扔在大海里。 用数组
表示大海水位的高度，比如：

1 2 2 3 5
3 2 3 4 4
2 4 5 3 1
6 7 1 4 5
5 1 1 2 4 
 
其中左边界和上边界表示太平洋，右边界和下边界表示大西洋。左下
与右上两个重合点既是太平洋也在大西洋。 将漂流瓶扔到大海里，
漂流瓶会随机向上下左右四个方向漂流，但是只能漂向水位低于或
等于当前水位的方向。

请输出所有符合以下条件的位置坐标：将漂流瓶从这个位置丢下，
既可能漂到太平洋，又可能漂到大西洋。

输入
一个二维整数矩阵，表示海域水位高低情况。

输出
符合条件的位置坐标，每行 1 个，并使用空格分隔坐标的 x 与 y 值。

输入样例
1 2 2 3 5
3 2 3 4 4
2 4 5 3 1
6 7 1 4 5
5 1 1 2 4

输出样例
0 4
1 3
1 4
2 2
3 0
3 1
4 0
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


void DFS(vector<vector<int> > &data, vector<vector<bool> > &visited, int x, int y)
{
    if (data.size() <= 0 || data[0].size() <= 0)
        return;

    int m = data.size(), n = data.size();
    if (visited.size() != m || visited[0].size() != n)
        return;

    if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y])
        return;

    vector<int> s;
    int diff_x[] = {-1, 1, 0, 0};
    int diff_y[] = {0, 0, -1, 1};
    int r, c, i, j, t;
    int h;

    s.push_back(x * n + y);
    visited[x][y] = true;
    while (!s.empty())
    {
        t = s.back(); s.pop_back();
        r = t / n; c = t % n;

        h = data[r][c];
        for (int k = 0; k < 4; k++)
        {
            i = r + diff_x[k];
            j = c + diff_y[k];
            if (0 <= i && i < m && 0 <= j && j < n && data[i][j] >= h && !visited[i][j])
            {
                s.push_back(i * n + j);
                visited[i][j] = true;
            }
        }
    }
}


vector<pair<int, int> > DoubleConnected(vector<vector<int> > &data)
{
    // position which is connected both to left/top and right/down

    vector<pair<int, int> > res;
    if (data.size() <= 0 || data[0].size() <= 0)
        return res;

    int m = data.size(), n = data.size();
    vector<vector<bool> > pacific(m, vector<bool>(n, false));
    vector<vector<bool> > atlantic(m, vector<bool>(n, false));
    int i, j;

    for (j = 0; j < n; j++)  // top
        DFS(data, pacific, 0, j);
    for (i = 0; i < m; i++)  // left
        DFS(data, pacific, i, 0);

    for (j = 0; j < n; j++)  // down
        DFS(data, atlantic, m - 1, j);
    for (i = 0; i < m; i++)  // right
        DFS(data, atlantic, i, n - 1);

    // double connected
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (pacific[i][j] && atlantic[i][j])
                res.push_back(make_pair(i, j));

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int x;
    vector<pair<int, int> > res;

    // input case
    vector<vector<int> > data;
    while (getline(myfile, line))
    {
        vector<int> row;
        stringstream ss(line);

        while (ss >> x)
            row.push_back(x);

        data.push_back(row);
    }

    for (auto &x: data)
        PrintVec(x);

    // result
    res = DoubleConnected(data);
    for (auto &x: res)
        cout << x.first << ' ' << x.second << endl;

    return 0;
}