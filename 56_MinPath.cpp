/*
- 马走日

序号：#56
难度：困难
时间限制：1500ms
内存限制：10M

描述
在中国象棋中，马只能走日字型。现在给出一个由 N*M 个格子组成的中国象棋棋盘
( 有(N+1)*(M+1)个交叉点可以落子 )，以及棋盘上的两个坐标点 S,T。请计算
出从 S 到 T 使用日字型走法所需的最少步数，如果不能到达，则输出-1。

下图为一个 1x2 的棋盘，起始落子点（蓝色）为 (0, 0)，目标落子点（绿色）
为 (1,2) 的示意，此时需要的步数为 1：


输入
单组数据。

第 1 行：1 个数，表示 N 的值
第 2 行：1 个数，表示 M 的值
第 2 行：两个数，分别代表 S 点的 x,y 坐标
第 4 行：两个数，分别代表 T 点的 x,y 坐标
输入保证满足 (1<=N<=1000, 1<=M<=1000, 0<=x<=N, 0<=y<=M)

输出
所需的最少步数，不能到达则输出 -1.

输入样例
1
1
0 0
1 1

输出样例
-1
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <queue>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ' ';
    cout << data.back() << endl;
}


int MinPath(int n, int m, int sx, int sy, int ex, int ey)
{
    // minimum path steps for start (sx,sy) to end (ex,ey)
    // in a graph

    if (n < 0 || m < 0 || sx < 0 || sx > n || sy < 0 || sy > m)
        return -1;

    // BFS
    vector<vector<bool> > visited(n + 1, vector<bool>(m + 1, false));
    queue<int> q;
    int diff_x[] = {-1, 1, -1, 1, -2, -2, 2, 2};
    int diff_y[] = {2, 2, -2, -2, 1, -1, 1, -1};
    int r, c, x, y;
    int res = 0;

    q.push(sx * (m + 1) + sy);
    visited[sx][sy] = true;

    while (!q.empty())
    {

        // current step
        int k = q.size();
        while (k--)
        {
            int t = q.front(); q.pop();
            r = t / (m + 1); c = t % (m + 1);

            // reach end
            if (r == ex && c == ey)
                return res;

            // next step
            for (int i = 0; i < 8; i++)
            {
                x = r + diff_x[i]; y = c + diff_y[i];
                if (0 <= x && x <= n && 0 <= y && y <= m && !visited[x][y])
                {
                    q.push(x * (m + 1) + y);
                    visited[x][y] = true;
                }
            }
        }

        res++;
    }

    return -1;
}


int main(int argc, char *argv[])
{
    string line;
    int n, m;
    int sx, sy, ex, ey;
    int res;

    // input case
    while (myfile >> n)
    {
        myfile >> m;
        myfile >> sx; myfile >> sy;
        myfile >> ex; myfile >> ey;

        cout << n << ' ' << m << endl;
        cout << sx << ',' << sy << ' ' << ex << ',' << ey << endl;

        // result
        res = MinPath(n, m, sx, sy, ex, ey);
        cout << res << endl;
    }

    return 0;
}