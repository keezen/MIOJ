/*
- 简单直接全排列

序号：#72
难度：困难
时间限制：2000ms
内存限制：15M

描述
给一个无重复数字的整数列，输出这些整数的全排列，按升序排列所有组合。

输入
一组数字，用英文逗号隔开，如：1,2,3

输出
输出由这组数字能组成的所有组合，按升序排列，使用英文逗号(,)隔开每个数字，
使用英文分号(;)隔开所有组合，如：1,2,3;1,3,2;2,1,3;2,3,1;3,1,2;3,2,1

输入样例
1,2,3

输出样例
1,2,3;1,3,2;2,1,3;2,3,1;3,1,2;3,2,1
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


void Permutation(vector<int> &data, int pos, vector<vector<int> > &res)
{
    if (data.size() <= 0 || pos < 0 || pos >= data.size())
        return;

    if (pos == data.size() - 1)
    {
        res.push_back(data);
        return;
    }

    for (int i = pos; i < data.size(); i++)
    {
        swap(data[pos], data[i]);
        Permutation(data, pos + 1, res);
        swap(data[pos], data[i]);
    }
}


bool compare(vector<int> &a, vector<int> &b)
{
    int i;

    for (i = 0; i < a.size() && i < b.size(); i++)
        if (a[i] < b[i])
            return true;
        else if (a[i] > b[i])
            return false;

    if (i < a.size())
        return false;

    if (i < b.size())
        return true;

    return false;
}


vector<vector<int> > Permutation(vector<int> &data)
{
    vector<vector<int> > res;

    if (data.size() <= 0)
        return res;

    Permutation(data, 0, res);

    sort(res.begin(), res.end(), compare);

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int n;
    vector<vector<int> > res;

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
        res = Permutation(data);
        
        for (int i = 0; i < res.size(); i++)
            PrintVec(res[i], ',', i == res.size() - 1 ? '\n' : ';');
    }

    return 0;
}