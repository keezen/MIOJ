/*
- 国王招驸马

序号：#38
难度：困难
时间限制：1000ms
内存限制：10M

描述
国王为了给公主找到这个世界上最聪明的人作为驸马，发明了一个游戏。
在游戏中，国王设置了多个连续的屋子，从第一个屋子开始，每个屋子
都会有n(n>=0)个门来进入接下来的1~n个屋子（例如这个屋子有2个门，
那么就是第一个门可以进入之后第一个屋子，第二个门可以进入之后第二个屋子)，
最后经过屋子最少的人将获得胜利，迎娶美丽的公主。

输入
一组数据，分别用(,)隔开，每一个数字表示对应的屋子共有多少扇门。

输出
一个整数，表示到达最后屋子时经过的最少的屋子数，如果不能到达则返回-1。

输入样例
2,3,1,1,4
1,1,1,0,1

输出样例
2
-1
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
        cout << data[i] << ',';
    cout << data.back() << endl;
}


int MinHouse(vector<int> &houses)
{
    // compute the minimum number of houses past when
    // reaching the last house

    if (houses.size() <= 0)
        return -1;
    
    // dp[i] indicates minimum number of houses past when
    // reaching the i-th house
    int len = houses.size();
    vector<int> dp(len + 1, -1);
    int i, j;

    dp[1] = 0;
    for (i = 2; i <= len; i++)
        for (j = 1; j < i; j++)
            // j-th house is reachable and can reach i-th house
            if (dp[j] >= 0 && houses[j - 1] >= i - j)
                // shorter path
                if (dp[i] == -1 || dp[j] + 1 < dp[i])
                    dp[i] = dp[j] + 1;

    return dp[len];
}


int main(int argc, char *argv[])
{
    string str;
    int x;
    int res;

    // input case
    while (getline(myfile, str))
    {
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream ss(str);
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = MinHouse(data);
        cout << res << endl;
    }

    return 0;
}