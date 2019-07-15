/*
- Game

序号：#149
难度：一般
时间限制：2000ms
内存限制：128M

描述
Alice 和 Bob 玩起了掷骰子的游戏，为了增加趣味性，他们制定了一套新的判断规则。

两人同时掷 n 个骰子，每个骰子会等概率掷出 1...6 这六种点数中的一种，
总点数大的人获胜，总点数一样就继续掷，重复如此直到游戏结束。

为了避免偶然性，每次游戏他们会玩 k 局，Alice 想知道她赢的局的期望。

输入
输入第一行有一个正整数 T，代表游戏的次数。 第二行到第 T+1 行每行有两个正整数 
n，k 分别代表本次游戏每一局掷骰子的数量和局数。

1≤T≤100,000
1≤n,k≤1,000,000,000

输出
输出有 T 行，每一行一个数代表 Alice赢得局数的期望，结果保留两位小数。

输入样例
1 
1 1

输出样例
0.50
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


double Expect(int n, int k)
{
    return k / 2.0;
}


int main(int argc, char *argv[])
{
    string line;
    double res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int t;
        ss >> t;
        
        int n, k;
        while (t--)
        {
            getline(myfile, line);
            stringstream ss2(line);
            ss2 >> n >> k;

            cout << line << endl;

            // result
            res = Expect(n, k);
            printf("%.2f\n", res);
        }
    }

    return 0;
}