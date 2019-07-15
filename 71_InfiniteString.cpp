/*
- 还是字符串

序号：#71
难度：非常难
时间限制：1000ms
内存限制：10M

描述
有一个无限长的字符串，只包含数字 1 和 2 ，按照一定的规则变化后，
字符串不会发生任何变化。规则如下： 将字符串按1与2进行拆解，计算
相邻的1与2的数量，组成的新字符串。

下面是这个字符串的前19位： 1221121221221121122...... 按1与2拆解，
可得： (1) (22) (11) (2) (1) (22) (1) (22) (11) (2) (11) (22) ...... 
计算相邻的1与2的数量，组成的新字符串： 1 2 2 1 1 2 1 2 2 1 2 2 ...... 
恰好等于原字符串。字符串不变。

输入
输入正整数 Ｎ，表示这个无限长字符串的前N位子串的长度 例如Ｎ＝6，
前6位子串为 122112

输出
正整数 M，表示前N位子串中1的个数

输入样例
4
5
6

输出样例
2
3
3
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <climits>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ' ';
    cout << data.back() << endl;
}


int InfiniteString(int n)
{
    // number of 1 in first n characters of infinite string

    if (n <= 0)
        return 0;

    if (n <= 3)
        return 1;

    string s("122");
    int i = 2, j;
    int cur = 1;
    int res = 1;

    while (s.size() < n)
    {
        int k = s[i] - '0';

        for (j = 0; j < k && s.size() < n; j++)
        {
            s.push_back(cur + '0');
            if (cur == 1)
                res++;
        }

        i++; cur = 3 - cur;
    }

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int n;
    int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        ss >> n;

        cout << n << endl;

        // result
        res = InfiniteString(n);
        cout << res << endl;
    }

    return 0;
}