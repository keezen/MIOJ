/*
- 寻找归一数字

序号：#43
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
有一类正整数我们叫做归一数字，对于任意一个归一数字 N，满足以下特性：

N 的每一位的平方和组成一个数，新数字的平方和再组成一个新数字，如此往复运算，
直到最终结果为 1。

若一个数字能最终归一成 1，则该数字为归一数字，否则不是归一数字。

举例： 82可以分解为8^2 + 2^2 = 68，68继续分解为6^2 + 8^2 = 100，
100可以分解为1^2 + 0^2 + 0^2 = 1。所以82可以归一。

输入
一个正整数 N（0 < N < 100000000）

输出
输出N 是否为归一数的判断结果，若是则返回 'true'，否则返回 'false'（均为字符串）。

输入样例
1
82
50

输出样例
true
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


int Next(int n)
{
    if (n <= 1)
        return 1;

    int next = 0;
    for(; n > 0; n /= 10)
        next += (n % 10) * (n % 10);

    return next;
}


bool NormalizedNumber(int n)
{
    // whether number n can be normalized to 1,
    // identical to problem whether a list has circle

    if (n <= 0)
        return false;

    if (n == 1)
        return true;

    int slow = n, fast = n;
    while (fast != 1)
    {
        slow = Next(slow);

        fast = Next(fast);
        if (fast == 1)
            break;
        fast = Next(fast);

        if (slow == fast)
            break;
    }

    // no circle
    if (fast == 1)
        return true;

    // there is circle
    return false;
}


int main(int argc, char *argv[])
{
    string line;
    int n;
    bool res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        ss >> n;

        cout << n << endl;

        // result
        res = NormalizedNumber(n);
        cout << (res ? "true" : "false") << endl;
    }

    return 0;
}