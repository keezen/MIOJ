# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <algorithm>
# include <utility>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i].first << ' ' << data[i].second << ' ';
    cout << data.back().first << ' ' << data.back().second << endl;
}


string BigNumAdd(string s1, string s2)
{

    if (s1.size() <= 0 || s2.size() <= 0)
        return "";

    if (s1.size() < s2.size())
        swap(s1, s2);

    string res;
    int c = 0, s, x;
    int i = s1.size() - 1, j = s2.size() - 1;

    for (; i >= 0 && j >= 0; i--, j--)
    {
        s = (s1[i] - '0') + (s2[j] - '0') + c;
        c = s / 10; x = s % 10;
        res.push_back(x + '0');
    }

    for (; i >= 0; i--)
    {
        s = s1[i] - '0' + c;
        c = s / 10; x = s % 10;
        res.push_back(x + '0');
    }

    if (c > 0)
        res.push_back(c + '0');

    reverse(res.begin(), res.end());

    return res;
}


string BigNumGreater(string s1, string s2)
{
    if (s1.size() <= 0 || s2.size() <= 0)
        return "";

    if (s1.size() > s2.size())
        return "Y";

    if (s1.size() < s2.size())
        return "N";

    // equal size
    for (int i = 0; i < s1.size(); i++)
        if (s1[i] > s2[i])
            return "Y";
        else if (s1[i] < s2[i])
            return "N";

    return "N";
}


string BigNumAddRelation(string s1, string s2, char opt)
{
    if (s1.size() <= 0 || s2.size() <= 0 || (opt != '+' && opt != '<' && opt != '>'))
        return "";

    if (opt == '+')
        return BigNumAdd(s1, s2);

    if (opt == '<')
        swap(s1, s2);

    return BigNumGreater(s1, s2);
}


int main(int argc, char *argv[])
{
    string str;
    string s1, s2;
    char opt;
    string res;

    // input case
    while (getline(myfile, str))
    {
        for (int i = 0; i < str.size(); i++)
            if (str[i] < '0' || str[i] > '9')
            {
                opt = str[i];
                str[i] = ' ';
                break;
            }

        stringstream ss(str);
        ss >> s1; ss >> s2;

        cout << s1 << ' ' << opt << ' ' << s2 << endl;

        // result
        res = BigNumAddRelation(s1, s2, opt);
        cout << res << endl;
    }

    return 0;
}