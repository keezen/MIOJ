/*
- 数数有几个岛

序号：#55
难度：非常难
时间限制：1000ms
内存限制：10M

描述
有一个二维的网格地图，其中1代表陆地0代表水，并且该网格的四周
全部由水包围。我们对岛屿的定义是四面环水，由相邻的陆地水平或
垂直连接形成，现在需要统计岛屿的数量。

举例： 有一个二维地图如下： 11110 11010 11000 00000 
其中的岛屿数量为1。

输入
使用空格分隔二维地图的每一行，使用逗号分隔每一项，地图范围
在 1000 x 1000 以内。

输出
岛屿的数量。

输入样例
1,1,1,1,0 1,1,0,1,0 1,1,0,0,0 0,0,0,0,0
1,1,0,0,0 1,1,0,0,0 0,0,1,0,0 0,0,0,1,1

输出样例
1
3
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
    // traverse all vertexes connected by (x,y)

    if (data.size() <= 0 || data[0].size() <= 0)
        return;

    int m = data.size(), n = data[0].size();
    if (visited.size() != m || visited[0].size() != n)
        return;

    if (x < 0 || x >= m || y < 0 || y >= n || data[x][y] == 0 || visited[x][y])
        return;

    vector<int> s;
    int r, c;
    int diff_x[4] = {-1, 1, 0, 0};
    int diff_y[4] = {0, 0, -1, 1};

    s.push_back(x * n + y);
    while (!s.empty())
    {
        int t = s.back(); s.pop_back();
        r = t / n; c = t % n;
        visited[r][c] = true;

        for (int i = 0; i < 4; i++)
        {
            x = r + diff_x[i];
            y = c + diff_y[i];

            if (0 <= x && x < m && 0 <= y && y < n && data[x][y] == 1 && !visited[x][y])
                s.push_back(x * n + y);
        }
    }
}


int NumberOfIslands(vector<vector<int> > &data)
{
    // number of islands

    if (data.size() <= 0 || data[0].size() <= 0)
        return 0;

    int m = data.size(), n = data[0].size();
    int res = 0;
    int i, j;

    // number of connected sub-graph
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (data[i][j] == 1 && !visited[i][j])
            {
                DFS(data, visited, i, j);
                res++;
            }

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    string row;
    int x;
    int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        vector<vector<int> > data;

        int i;
        while (ss >> row)
        {
            vector<int> t;
            for (i = 0; i < row.size(); i++)
                if (row[i] == ',')
                    row[i] = ' ';

            stringstream sss(row);
            while (sss >> x)
                t.push_back(x);

            data.push_back(t);
        }

        for (auto &x: data)
            PrintVec(x);

        // result
        res = NumberOfIslands(data);
        cout << res << endl;
    }

    return 0;
}