/*
- 数数字游戏
序号：#117
难度：困难
时间限制：1000ms
内存限制：10M
描述
小爱和小冰是一对好闺蜜，她们都是世界上最聪明的人工智能之一。某一天，
他们俩一起玩数数字游戏，规则如下：

首先小爱和小冰各说一个目标数字num1,num2；
小爱和小冰轮流报数（小冰报数方法与小爱相同），每次只报一个数，报数者
可以选择将这个数报给谁；
小爱先开始报数字，把这个数给自己或小冰都行，小爱和小冰各自得到的所有数
之和不能超过自己的目标数字；
最终，谁再也报不出符合条件的数字谁就算输，另一个人就赢（即谁报完数后，
两人所得数字之和都达到了各自的目标数字，谁就赢）；
由于两人智商都是非常的高，所以觉得游戏太简单了，于是两人决定每次报的数
只能是斐波那契数列中的元素（例如每次取1，2，3，5，8.......) 。
现在两人各说一个目标数字后请你判断谁会赢。如果小爱赢则输出"Xiaoai Win"，
反之小冰赢输出"Xiaobing Win"。两人都很聪明，都会使用最优策略（每次报
数是最优的）。

规定：斐波那契数列F(1)=1,F(2)=2,F(N)=F(N-1)+F(N-2)

输入
多组数据，每组输入两个正整数，用空格隔开，分别表示小爱和小冰的目标数字
num1,num2。

数据范围：num1,num2<=10000

输出
输出 "Xiaoai Win" 或 "Xiaobing Win"，分别表示小爱赢或小冰赢。
每个结果 1 行。

输入样例
1 4
3 4
4 4
1 5

输出样例
Xiaoai Win
Xiaoai Win
Xiaobing Win
Xiaobing Win
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <unordered_set>
# include <cstring>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


vector<int> ComputeSG(const int N)
{
    // compute sg function sg[i], for 0<=i<=N

    if (N < 0)
        return vector<int>();

    vector<int> sg(N + 1, 0);

    // fibonacci less than N
    vector<int> fibo;
    fibo.push_back(1); fibo.push_back(2);
    for (int i = 2; i < N; i++)
    {
        int t = fibo[i-1] + fibo[i-2];
        if (t > N)
            break;
        else
            fibo.push_back(t);
    }

    // sg function for every i
    bool hash[N];
    int i, j;

    for (i = 1; i <= N; i++)
    {
        memset(hash, 0, sizeof(hash) / sizeof(hash[0]));

        for (int j = 0; j < fibo.size() && fibo[j] <= i; j++)
            hash[sg[i - fibo[j]]] = true;
        
        // sg[i] = mex{ sg(j) | j \in C_i }, while mex{S} means
        // least non-negative integer which is not in set S, and
        // C_i means children set of node i
        for (j = 0; j <= N && hash[j]; j++) ;
        sg[i] = j;
    }

    return sg;
}


bool FirstWin(int num1, int num2, vector<int> &sg)
{
    // whether first player can win the tow-pile game theory,
    // given initial state

    if (num1 < 0 || num2 < 0)
        return false;

    if (num1 > num2)
        swap(num1, num2);

    if (num2 >= sg.size())
        return false;

    // sg function of multiple piles is xor of that of every pile
    return sg[num1] ^ sg[num2];
}


int main(int argc, char *argv[])
{
    string line;
    bool res;

    const int N = 10;
    vector<int> sg;
    sg = ComputeSG(N);

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int num1, num2;
        ss >> num1; ss >> num2;

        cout << line << endl;

        // result
        res = FirstWin(num1, num2, sg);
        cout << (res ? "Xiaoai Win" : "Xiaobing Win") << endl;
    }

    return 0;
}