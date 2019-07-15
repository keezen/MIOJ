/*
- 括号配对

序号：#62
难度：一般
时间限制：1000ms
内存限制：10M

描述
我们知道，在逻辑表达式中广泛使用了括号，而括号都是层次化成对出现
的。也就是任意左括号都应该存在一个在同一逻辑层级的右括号作为对应。 
现在我们有一些仅由括号组成的字符串序列，保证每个字符为大括号”{”,”}”、
中括号”[”,”]”和小括号”(”,”)”中的一种。 需要判断给定的的序列是否合法。

输入
一行仅由括号组成的字符串

输出
如果序列合法输出 1，否则输出 0

输入样例
[()]
({[])}
[()]{}

输出样例
1
0
1
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


bool LegalBracket(string s)
{
    if (s.size() <= 0)
        return false;

    if (s.size() & 1)
        return false;

    string st;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            st.push_back(s[i]);
        else if ((s[i] == ')' && st.back() == '(') ||
            (s[i] == ']' && st.back() == '[') ||
            (s[i] == '}' && st.back() == '{'))
            st.pop_back();
        else
            return false;
    }

    return true;
}


int main(int argc, char *argv[])
{
    string line;
    bool res;

    // input case
    vector<vector<int> > data;
    while (getline(myfile, line))
    {
        cout << line << endl;

        // result
        res = LegalBracket(line);
        cout << res << endl;
    }

    return 0;
}