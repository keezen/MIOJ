/*
- 硬币排序

序号：#41
难度：困难
时间限制：1000ms
内存限制：15M

描述
小明目前在一家银行的IT部门工作。 银行每天经常会有很多存款业务，
所以每天总会收到大量硬币。如何给这些硬币分类排序成了令业务部门
十分头疼的一个问题。 这一天，业务部门向IT部门提交了一个需求，
希望IT部门能够出一套为硬币进行排序的解决方案，使得面值小的硬币
排到前面，其中最核心的算法部门交给了小明来实现。 如果你是小明，
你会给出一个什么样的算法呢？

注： 1.要求不使用任何系统排序函数或库排序函数！！！ 2.要求时间
复杂度为O(n)，空间复杂度为O(1)，也就是不允许建立新数组，
只能在原数组上进行排序！！！

输入
一个字符串，只包含a、b、c三种字符，分别表示1元，2元，5元三种硬币

输出
一个字符串，已按照a、b、c完成排序，表示经过排序后的一排硬币

输入样例
cba
acba

输出样例
abc
aabc
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


string SortString(string s)
{
    if (s.size() <= 1)
        return s;

    vector<int> freq(3, 0);
    int i, j;

    // count frequency
    for (i = 0; i < s.size(); i++)
        switch (s[i])
        {
            case 'a': freq[0]++; break;
            case 'b': freq[1]++; break;
            case 'c': freq[2]++; break;
            default: break;
        }

    // sort
    i = 0; j = 0;
    while (i < s.size() && j < freq.size())
    {
        s[i++] = 'a' + j;
        if (--freq[j] == 0)
            j++;
    }
    
    return s;
}


int main(int argc, char *argv[])
{
    string line;
    string res;

    // input case
    while (getline(myfile, line))
    {
        cout << line << endl;

        // result
        res = SortString(line);
        cout << res << endl;
    }

    return 0;
}