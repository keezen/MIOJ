/*
- 进制转换

序号：#110
难度：一般
时间限制：1000ms
内存限制：10M

描述
给出一个P进制整数N，求N的Q进制表示(0≤N≤32767，2≤P≤16,2≤Q≤16)。 
大于 9 的数字依次使用小写字母 a、b、c、d、e、f 表示。 请勿使用
已存在的进制转换库或函数，比如PHP中的base_convert()等。

输入
输入3个数，以空格分隔： 第1个数是待转换的数， 第2个数是待转换的
数的进制， 第3个数是转换后的数的进制。

输出
输入转换后的数

输入样例
31 10 16

输出样例
1f
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


string ConvertBase(string n, int p, int q)
{
    // convert base of number n of base p to base q

    if (n.size() <= 0 || p < 2 || q < 2)
        return "";

    string digit2char = "0123456789abcdef";
    int char2digit[256];
    int n10 = 0;
    int i, w;

    for (i = 0; i < digit2char.size(); i++)
        char2digit[digit2char[i]] = i;

    // base p to base 10
    for (i = n.size() - 1, w = 1; i >= 0; i--, w *= p)
        n10 += char2digit[n[i]] * w;

    // base 10 to base q
    string res;
    for (i = n10; i > 0; i /= q)
        res.push_back(digit2char[i % q]);
    reverse(res.begin(), res.end());

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    string res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        string n;
        int p, q;
        ss >> n; ss >> p; ss >> q;

        cout << line << endl;

        // result
        res = ConvertBase(n, p, q);
        cout << res << endl;
    }

    return 0;
}