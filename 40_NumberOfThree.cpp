/*
- 找小“3”

序号：#40
难度：困难
时间限制：1000ms
内存限制：10M

描述
给定一个奇数n，可得到一个由从1到n的所有奇数所组成的数列，求这一数列中
数字3所出现的总次数。例如当n=3时，可得到奇数列：1,3，其中有一个数字3，故可得1

输入
一个奇数。表示n，0<n<9999999999。

输出
一个整数，表示从 1 到 n 的奇数列中，数字 3 出现的次数。

输入样例
1
3
35

输出样例
0
1
7
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ' ';
    cout << data.back() << endl;
}


long int NumberOfThree(long int n)
{
    // number of digit 3 in odd numbers from 1 to n,
    // given odd number n

    if (n < 3)
        return 0;

    long int i, a, b;
    long int count = 0;
    for (i = 1; i <= n; i *= 10)
    {
        a = n / i;
        b = n % i;

        count += (a + 6) / 10 * ((i + 1) / 2) + (a % 10 == 3) * (b == 0 ? 1 : (b + 1) / 2);
    }

    return count;
}


long int NumberOfThree_Brute(long int n)
{
    if (n < 3)
        return 0;

    long int i, j, count = 0;
    for (i = 1; i <= n; i += 2)
        for (j = i; j > 0; j /= 10)
            if (j % 10 == 3)
                count++;

    return count;
}


int main(int argc, char *argv[])
{
    string line;
    long int n;
    long int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        ss >> n;

        cout << n << endl;

        // result
        res = NumberOfThree(n);
        cout << res << endl;
    }

    return 0;
}