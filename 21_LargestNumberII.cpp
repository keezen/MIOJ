# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <unordered_map>
# include <algorithm>
# include <stack>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


bool is_larger(string a, string b)
{
    if (a.size() > b.size())
        return true;

    if (a.size() < b.size())
        return false;

    for (int i = 0; i < a.size(); i++)
        if (a[i] > b[i])
            return true;
        else if (a[i] < b[i])
            return false;

    return false;
}


string LargestNumberII_3dDP(string a, string b, int k)
{
    // convert problem to "smallest number after removing
    // k digits"

    if (a.size() + b.size() < k)
        return "";

    int len1 = a.size(), len2 = b.size();
    vector<vector<vector<string> > > dp(len1 + 1, vector<vector<string> >(len2 + 1, vector<string>(k + 1)));
    int i, j, l;
    string t;

    for (l = 1; l <= k; l++)
        for (i = 0; i <= len1; i++)
            for (j = 0; j <= len2; j++)
            {
                if (i + j < l)
                    continue;

                if (i + j - 1 >= l)
                {
                    if (i > 0)
                        dp[i][j][l] = dp[i - 1][j][l];
                    if (j > 0 && is_larger(dp[i][j - 1][l], dp[i][j][l]))
                        dp[i][j][l] = dp[i][j - 1][l];
                }

                if (i > 0)
                {
                    t = dp[i - 1][j][l - 1] + a[i - 1];
                    if (is_larger(t, dp[i][j][l]))
                        dp[i][j][l] = t;
                }

                if (j > 0)
                {
                    t = dp[i][j - 1][l - 1] + b[j - 1];
                    if (is_larger(t, dp[i][j][l]))
                        dp[i][j][l] = t;
                }
            }

    return dp[len1][len2][k];
}


string LargestNumberII(string a, string b, int k)
{
    // convert problem to "smallest number after removing
    // k digits"

    if (a.size() + b.size() < k)
        return "";

    int len1 = a.size(), len2 = b.size();
    vector<vector<string> > dp(len1 + 1, vector<string>(len2 + 1));
    vector<vector<string> > last(dp);
    int i, j, l;
    string t;

    for (l = 1; l <= k; l++)
    {
        last = dp;

        for (i = 0; i <= len1; i++)
            for (j = 0; j <= len2; j++)
            {
                if (i + j < l)
                    continue;

                if (i + j - 1 >= l)
                {
                    if (i > 0)
                        dp[i][j] = dp[i - 1][j];
                    if (j > 0 && is_larger(dp[i][j - 1], dp[i][j]))
                        dp[i][j] = dp[i][j - 1];
                }

                if (i > 0)
                {
                    t = last[i - 1][j] + a[i - 1];
                    if (is_larger(t, dp[i][j]))
                        dp[i][j] = t;
                }

                if (j > 0)
                {
                    t = last[i][j - 1] + b[j - 1];
                    if (is_larger(t, dp[i][j]))
                        dp[i][j] = t;
                }
            }
    }

    return dp[len1][len2];
}


int main(int argc, char *argv[])
{
    string str, sa, sb;
    char c;
    int k;
    string res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> sa; ss >> sb; ss >> k;

        string a, b;
        for (int i = 0; i < sa.size(); i++)
            if ('0' <= sa[i] && sa[i] <= '9')
                a.push_back(sa[i]);
        for (int i = 0; i < sb.size(); i++)
            if ('0' <= sb[i] && sb[i] <= '9')
                b.push_back(sb[i]);

        cout << a << ' ' << b << ' ' << k << endl;

        // result
        res = LargestNumberII(a, b, k);
        cout << res << endl;
    }

    return 0;
}