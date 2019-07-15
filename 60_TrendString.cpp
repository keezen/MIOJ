/*
- 上上下下的字符串

序号：#60
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
字符串 S 由字符 + 和 - 构成。字符串 D 是一个数字字符串，其长度
比 S 要大 1，其格式要求如下：

D 中不包含数字 0；
D 中必须包含数字 1，且最大数字不大于 D 的长度；
D 中的数字不重复出现。
根据 S，可以转换得到唯一的 D，S 与 D 的关系为：

S[i] 为 + 表示 D[i] < D[i+1];
S[i] 为 - 表示 D[i] > D[i+1]，且 D[i] - D[i+1] = 1.
现给出字符串 S 的值，请构造出合法的字符串 D 。 如输入 +-+-，
输出 13254，因为 1 < 3 > 2 < 5 > 4，符合增减增减（+-+-）的趋势。

输入
只由 + 和 - 构成的一个字符串。

输出
一个不含0且没有重复数字的字符序列。

输入样例
++++
----
+-+-++

输出样例
12345
54321
1325467
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


string TrendString(string s)
{
    if (s.size() <= 0)
        return "1";

    int n = s.size() + 1;

    if (n > 9)
        return "";

    vector<bool> visited(n + 1, false);
    vector<int> st;
    string res;
    int i, j, t;
    
    for (i = 1; i <= n; i++)
        st.push_back(i);

    while (!st.empty())
    {
        t = st.back();

        if (visited[t])  // explored
        {
            st.pop_back();
            res.pop_back();
            visited[t] = false;
            continue;
        }

        res.push_back(t + '0');  // visit
        visited[t] = true;

        i = res.size();

        if (i == n)  // end
            return res;
        else  // explore neighbors
        {
            if (s[i - 1] == '+')
            {
                for (j = t + 1; j <= n; j++)
                    if (!visited[j])
                        st.push_back(j);
            }
            else
                if (t > 1 && !visited[t - 1])
                    st.push_back(t - 1);
        }
    }

    return "";
}


bool DFS(string &s, vector<bool> &visited, string &path)
{
    if (s.size() <= 0)
        return true;

    if (s.size() >= 9)
        return false;

    int n = s.size() + 1;
    if (path.size() == n)
        return true;

    int k = path.size();
    char i, j;

    if (s[k - 1] == '+')
        for (i = path.back(); i <= n + '0'; i++)
        {
            if (!visited[i - '0'])
            {
                visited[i - '0'] = true;
                path.push_back(i);
                if (DFS(s, visited, path))
                    return true;
                visited[i - '0'] = false;
                path.pop_back();
            }
        }
    else
    {
        i = path.back() - 1;
        if (i > '0' && !visited[i - '0'])
        {
            visited[i - '0'] = true;
            path.push_back(i);
            if (DFS(s, visited, path))
                return true;
            visited[i - '0'] = false;
            path.pop_back();
        }
    }

    return false;
}


string TrendString_Recur(string s)
{
    if (s.size() <= 0)
        return "1";

    if (s.size() >= 9)
        return "";

    int n = s.size() + 1;
    vector<bool> visited(n + 1, false);
    string res;
    char i;
    
    for (i = '1'; i <= n + '0'; i++)
    {
        visited[i - '0'] = true;
        res.push_back(i);

        if (DFS(s, visited, res))
            return res;

        visited[i - '0'] = false;
        res.pop_back();
    }

    return "";
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
        res = TrendString(line);
        cout << res << endl;
    }

    return 0;
}