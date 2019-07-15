# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


bool Interleaving(string &s1, int p1, string &s2, int p2, string &s3, int p3)
{
    if (p1 >= s1.size() && p2 >= s2.size() && p3 >= s3.size())
        return true;

    if (p1 < s1.size() && s3[p3] == s1[p1] && Interleaving(s1, p1 + 1, s2, p2, s3, p3 + 1))
        return true;

    if (p2 < s2.size() && s3[p3] == s2[p2] && Interleaving(s1, p1, s2, p2 + 1, s3, p3 + 1))
        return true;

    return false;
}


bool InterleavingString_Recur(string &s1, string &s2, string &s3)
{
    if (s3.size() != s1.size() + s2.size())
        return false;

    return Interleaving(s1, 0, s2, 0, s3, 0);
}


bool InterleavingString_2D_DP(string &s1, string &s2, string &s3)
{
    // dynamic programming, dp[i][j] indicates whether first i
    // characters of s1 and first j characters of s2 can be
    // interleaved to form first (i + j) characters of s3
    if (s3.size() != s1.size() + s2.size())
        return false;

    vector<vector<bool> > dp(s1.size() + 1, vector<bool>(s2.size() + 1, false));
    dp[0][0] = true;
    for (int i = 0; i <= s1.size(); i++)
        for (int j = 0; j <= s2.size(); j++)
        {
            if (i > 0 && s1[i - 1] == s3[i + j - 1])
                dp[i][j] = dp[i - 1][j] || dp[i][j];
            if (j > 0 && s2[j - 1] == s3[i + j - 1])
                dp[i][j] = dp[i][j - 1] || dp[i][j];
        }

    return dp[s1.size()][s2.size()];
}


bool InterleavingString(string &s1, string &s2, string &s3)
{
    // 1-d dynamic programming, dp[i][j] indicates whether first i
    // characters of s1 and first j characters of s2 can be
    // interleaved to form first (i + j) characters of s3
    if (s3.size() != s1.size() + s2.size())
        return false;

    vector<bool> dp(s2.size() + 1, false);
    dp[0] = true;
    for (int i = 0; i <= s1.size(); i++)
        for (int j = 0; j <= s2.size(); j++)
        {
            if (i > 0)
                dp[j] = dp[j] && s1[i - 1] == s3[i + j - 1];
            if (j > 0)
                dp[j] = dp[j] || (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
        }

    return dp[s2.size()];
}


int main(int argc, char *argv[])
{
    string str;
    string s1, s2, s3;
    string res;

    // input case
    while (getline(myfile, str))
    {
        // input array
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream ss(str);
        ss >> s1 >> s2 >> s3;

        cout << s1 << endl << s2 << endl << s3 << endl;

        // result
        res = InterleavingString(s1, s2, s3) ? "true" : "false";
        cout << res << endl << endl;
    }

    return 0;
}