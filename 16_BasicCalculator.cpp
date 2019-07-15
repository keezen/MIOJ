# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <stack>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


void ScanNum(string &s, int &pos, int &num)
{
    while (pos < s.size() && s[pos] == ' ') pos++;

    for (num = 0; pos < s.size() && '0' <= s[pos] && s[pos] <= '9'; pos++)
        num = num * 10 + s[pos] - '0';

    while (pos < s.size() && s[pos] == ' ') pos++;
}


void MulDiv(string &s, int &pos, int &first, bool &err)
{

    int second;
    char opt;

    ScanNum(s, pos, first);

    for (opt = s[pos]; opt == '*' || opt == '/'; opt = s[pos])
    {
        ScanNum(s, ++pos, second);

        if (opt == '*')
            first *= second;
        else
        {
            if (second == 0)
            {
                err = true;
                return;
            }
            first /= second;
        }
    }
}


int EvalRegularExpr_Iter(string &s, bool &err)
{
    if (s.size() <= 0)
    {
        err = true;
        return 0;
    }

    int pos = 0, first, second;
    char opt;

    MulDiv(s, pos, first, err);
    while (pos < s.size())
    {
        opt = s[pos];
        MulDiv(s, ++pos, second, err);
        if (opt == '+')
            first += second;
        else if (opt == '-')
            first -= second;
    }

    return first;
}


int EvalBasicExpr_Stack(string &s, bool &err)
{
    if (s.size() <= 0)
    {
        err = true;
        return 0;
    }

    stack<int> st;
    int num = 0;
    char opt = '+';
    for (int i = 0; i < s.size(); i++)
    {
        // digits
        if ('0' <= s[i] && s[i] <= '9')
        {
            num = num * 10 + s[i] - '0';
        }

        // operator
        if ((!('0' <= s[i] && s[i] <= '9') && s[i] != ' ') || i == s.size() - 1)
        {
            if (opt == '+')
                st.push(num);
            else if (opt == '-')
                st.push(-num);
            else if (opt == '*')
            {
                int t = st.top(); st.pop();
                st.push(t * num);
            }
            else if (opt == '/')
            {
                if (num == 0)
                {
                    err = true;
                    return 0;
                }
                int t = st.top(); st.pop();
                st.push(t / num);
            }

            opt = s[i];
            num = 0;
        }
    }

    int res = 0;
    while (!st.empty())
    {
        res += st.top();
        st.pop();
    }

    return res;
}


int EvalBasicExpr(string &s, bool &err)
{
    if (s.size() <= 0)
    {
        err = true;
        return 0;
    }

    int sum = 0, top = 0;
    int num = 0;
    char opt = '+';
    for (int i = 0; i < s.size(); i++)
    {
        // digits
        if ('0' <= s[i] && s[i] <= '9')
        {
            num = num * 10 + s[i] - '0';
        }

        // operator
        if ((!('0' <= s[i] && s[i] <= '9') && s[i] != ' ') || i == s.size() - 1)
        {
            if (opt == '+')
                top = num;
            else if (opt == '-')
                top = -num;
            else if (opt == '*')
            {
                top *= num;
            }
            else if (opt == '/')
            {
                if (num == 0)
                {
                    err = true;
                    return 0;
                }
                top /= num;
            }

            opt = s[i];
            num = 0;

            if (opt == '+' || opt == '-' || i == s.size() - 1)
                sum += top;
        }
    }

    return sum;
}


int main(int argc, char *argv[])
{
    string str;
    int res;
    bool err;

    // input case
    while (getline(myfile, str))
    {
        cout << str << endl;

        // result
        err = false;
        res = EvalBasicExpr(str, err);
        if (err)
            cout << "err" << endl;
        else
            cout << res << endl;
    }

    return 0;
}