/*
- 找出单独出现的数字II

序号：#73
难度：一般
时间限制：1000ms
内存限制：10M

描述
给出一个数组，数组中的数字皆为正整数，除了某一个数字，其他的数字都会
出现三次。 找出那个只出现一次的数。

输入
3n+1的正整数数组，使用逗号(,)分隔(n>0)

输出
单独出现的数字

输入样例
2,3,2,2
5,1,4,5,4,5,4

输出样例
3
1
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


int UniqueElement(vector<int> &data)
{
    // find the unique element which appears once

    if (data.size() % 3 != 1)
        return 0;

    vector<int> freq(32, 0);
    int i, j, t;

    // count ones in every digit
    for (i = 0; i < data.size(); i++)
        for (t = data[i], j = 0; t > 0; t >>= 1, j++)
            if (t & 1)
                freq[j] = (freq[j] + 1) % 3;

    // recover unique number
    int res = 0;
    for (i = 0; i < 32; i++)
        if (freq[i])
            res |= (1 << i);

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        stringstream ss(line);
        int x;
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = UniqueElement(data);
        cout << res << endl;
    }

    return 0;
}