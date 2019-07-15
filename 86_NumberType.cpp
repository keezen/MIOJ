/*
- 优秀数字

序号：#86
难度：一般
时间限制：300ms
内存限制：10M

描述
判断一个数字是否为优秀数字。优秀数字定义为，一个整数M(M>=0)，有2条
规则： 规则1：存在一个正整数N(N>=0)，使得M=2^N+1； 
规则2：存在一个正整数N(N>=0)，使得M=2^N-1； 
若同时满足规则1和规则2，则输出Very Good 若满足规则1而不满足规则2，
则输出Good 若不满足规则1而满足规则2，则输出Bad 若都不满足，则
输出Normal

输入
一个整数M(M>=0)

输出
输出该数属于的类型

输入样例
3
5
7
8

输出样例
Very Good
Good
Bad
Normal
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <cmath>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


string NumType(long int m)
{
    // type of number

    if (m < 0)
        return "";

    if (m <= 1)
        return "Bad";

    bool first = true, second = true;
    long int t;

    for (t = m - 1; t > 1; t >>= 1)
        if (t & 1)
        {
            first = false; break;
        }

    for (t = m + 1; t > 1; t >>= 1)
        if (t & 1)
        {
            second = false; break;
        }

    if (first && second)
        return "Very Good";

    if (first)
        return "Good";

    if (second)
        return "Bad";

    return "Normal";
}


int main(int argc, char *argv[])
{
    string line;
    string res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        long int n;
        ss >> n;

        cout << line << endl;

        // result
        res = NumType(n);
        cout << res << endl;
    }

    return 0;
}