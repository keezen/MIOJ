/*
- 找数字对

序号：#48
难度：一般
时间限制：1000ms
内存限制：10M

描述
有一串可能含重复数字的列表，例如 N = {4,13,5,6,35,85,3}，对于任意
A ∈ N，B ∈ N, 使 A+B = 10 或 |A-B| = 10； 即两数之合为 10 或
两数之差的绝对值为 10。

找出所有满足条件的数字对 {A,B} 的个数。(A, B的顺序与原始数组保持一致)

输入
一行文本由英文逗号分隔，如 6,4,16

输出
2

输入样例
4,13,5,6,35,85,3
13,3,6,8,12,4,45,56,66,16
6,4,16

输出样例
2
4
2
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


int NumberOfPair(vector<int> &data)
{
    // number of pairs whose sum or difference is 10

    if (data.size() < 2)
        return 0;

    sort(data.begin(), data.end());

    int n = data.size();
    int i, j, k, l;
    int res = 0, target = 10;

    // sum
    i = 0; j = n - 1;
    while (i < j)
    {
        if (data[i] + data[j] == target)
        {
            for (k = i; k <= j && data[k] == data[i]; k++) ;
            for (l = j; l >= i && data[l] == data[j]; l--) ;
            if (k == j + 1 && l == i - 1)
                res += (j - i + 1) * (j - i) / 2;
            else
                res += (k - i) * (j - l);
            i = k; j = l;
        }
        else if (data[i] + data[j] < target)
            i++;
        else
            j--;
    }

    // difference
    i = 0; j = 1;
    while (j < n)
    {
        // cout << data[i] << ',' << data[j] << endl;
        if (i == j || data[j] - data[i] < target)
            j++;
        else if (data[j] - data[i] == target)
        {
            for (k = i; k < n && data[k] == data[i]; k++) ;
            for (l = j; l < n && data[l] == data[j]; l++) ;

            if (data[i] == data[j])
                res += (l - i) * (l - i - 1) / 2;
            else
                res += (k - i) * (l - j);
            i = k; j = l;
        }
        else
            i++;
    }

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int x;
    int res;

    // input case
    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == ',')
                line[i] = ' ';

        stringstream ss(line);
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = NumberOfPair(data);
        cout << res << endl;
    }

    return 0;
}