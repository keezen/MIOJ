/*
- 知了的鸣叫

序号：#79
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
路边有一排N棵树，每棵树上正好有一只知了，刚开始所有的知了都在睡
觉，从早上8点开始，第一棵树上的知了被你吵醒开始鸣叫，一秒后第二
棵树上的知了听到了同类的声音被叫醒，也开始鸣叫，再过一秒后第三棵
树上的知了听到了第二棵树上知了的声音被叫醒，也开始鸣叫⋯⋯ 每一棵
树上的声音传到相邻树上的时间为1秒，且只会传到相邻的树上（其他树
距离太远，声音传不过去） 每只知了在鸣叫8秒后会休息8秒，然后继续
鸣叫8秒休息8秒⋯⋯ 现在告诉你树的数量N，请问在第k秒内，第m棵树上
的知了是否在鸣叫，是输出1,否输出0 （第一支知了开始鸣叫的时刻为第
一秒开始）

输入
输入一行数据包含N，k，m，三个数中间用','隔开,1<=N<=10000,
1<=k<=40000,1<=m<=N 例如10,2,2

输出
一个数表示第k秒内，第m棵树上的知了是否在鸣叫

输入样例
10,2,2
10,1,2
10,2,3

输出样例
1
0
0
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


bool CicadaSing(int n, int k, int m)
{
    // whether m-th one of n cicadas is singing at k-th second

    if (n <= 0 || k <= 0 || m <= 0 || m > n)
        return false;

    if (k < m)
        return false;

    int t = (k - m) % 16;

    if (0 <= t && t < 8)
        return true;
    else
        return false;
}


int main(int argc, char *argv[])
{
    string line;
    bool res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        stringstream ss(line);
        int n, k, m;
        ss >> n; ss >> k; ss >> m;

        cout << line << endl;

        // result
        res = CicadaSing(n, k, m);
        cout << res << endl;
    }

    return 0;
}