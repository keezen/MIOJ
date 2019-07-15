/*
- 数独游戏

序号：#54
难度：一般
时间限制：1000ms
内存限制：10M

描述
数独盘面是个九宫，每一宫又分为九个小格。在这八十一格中给出一定的已知数字
和解题条件，利用逻辑和推理，在其他的空格上填入1-9的数字。使1-9每个数字
在每一行、每一列和每一宫中都只出现一次，所以又称"九宫格"。 一个合法的
数独棋盘满足上面的条件，即1-9每个数字在每一行、每一列和每一宫中都只出
现一次，而并不要求一定有解。 请判断给出的数独棋盘是否合法。

举例： 有一个数独棋盘如下：

5 3 - - 7 - - - -
6 - - 1 9 5 - - -
- 9 8 - - - - 6 -
8 - - - 6 - - - 3
4 - - 8 - 3 - - 1
7 - - - 2 - - - 6
- 6 - - - - 2 8 -
- - - 4 1 9 - - 5
- - - - 8 - - 7 9
它是一个合法棋盘，输出true。

输入
从左到右从上到下，使用空格分隔每一宫，使用逗号分隔每一格，没有数字则代表
该格为空。

输出
true或false表示该数独棋盘是否合法。

输入样例
5,3,-,6,-,-,-,9,8 -,7,-,1,9,5,-,-,- -,-,-,-,-,-,-,6,- 8,-,-,4,-,-,7,-,- -,6,-,8,-,3,-,2,- -,-,3,-,-,1,-,-,6 -,6,-,-,-,-,-,-,- -,-,-,4,1,9,-,8,- 2,8,-,-,-,5,-,7,9
5,3,-,6,-,-,-,9,8 -,7,-,1,9,5,-,-,- -,-,-,-,-,-,-,6,- 8,-,-,4,-,-,7,-,- -,6,-,8,-,3,-,2,- -,-,3,-,-,1,-,-,6 -,6,-,-,-,-,-,9,- -,-,-,4,1,9,-,8,- 2,8,-,-,-,5,-,7,9

输出样例
true
false
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


bool IsSudoku(vector<vector<int> > &data)
{
    // whether given sudoku is legal

    if (data.size() != 9 || data[0].size() != 9)
        return false;

    int n = data.size();
    vector<bool> visited(n + 1, false);
    int i, j;

    // row repeat
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
            if (data[i][j] > 0)
            {
                if (visited[data[i][j]])
                    return false;
                else
                    visited[data[i][j]] = true;
            }

        visited.assign(n + 1, false);
    }

    // column repeat
    for (j = 0; j < 9; j++)
    {
        for (i = 0; i < 9; i++)
            if (data[i][j] > 0)
            {
                if (visited[data[i][j]])
                    return false;
                else
                    visited[data[i][j]] = true;
            }

        visited.assign(n + 1, false);
    }

    // box repeat
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            int t = data[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3];
            if (t > 0)
            {
                if (visited[t])
                    return false;
                else
                    visited[t] = true;
            }
        }

        visited.assign(n + 1, false);
    }

    return true;
}


int main(int argc, char *argv[])
{
    string line;
    int x;
    bool res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';
            else if (line[i] == '-')
                line[i] = '0';

        vector<vector<int> > data(9, vector<int>(9, 0));
        stringstream ss(line);
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                ss >> x;
                data[(i/3)*3+j/3][(i%3)*3+j%3] = x;
            }

        for (auto &x: data)
            PrintVec(x);

        // result
        res = IsSudoku(data);
        cout << (res ? "true" : "false") << endl;
        data.clear();
    }

    return 0;
}