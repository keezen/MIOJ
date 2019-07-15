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
        cout << data[i] << ',';
    cout << data.back() << endl;
}


bool Backpack(vector<int> &data, int pos, int volume)
{
    // whether elements[pos:] can fill backpack of given volume

    if (data.size() <= 0 || pos < 0 || pos >= data.size() || volume <= 0)
        return false;

    if (data[pos] == volume)
        return true;

    return Backpack(data, pos + 1, volume) ||
        Backpack(data, pos + 1, volume - data[pos]);
}


bool Bisection_Recur(vector<int> &data)
{
    if (data.size() <= 0)
        return false;

    // find sum
    int sum = 0, i;
    for (i = 0; i < data.size(); i++)
        sum += data[i];

    if (sum & 1)
        return false;

    // backpack
    return Backpack(data, 0, sum / 2);
}


bool Backpack(vector<int> &data, int volume)
{
    // whether elements in array can fill backpack of given volume,
    // dp[i][j] indicates whether the first i elements can fill backpack
    // of volume j

    if (data.size() <= 0 || volume <= 0)
        return false;

    for (int i = 0; i < data.size(); i++)
        if (data[i] < 0)
            return false;

    int len = data.size();
    vector<vector<bool> > dp(len + 1, vector<bool>(volume));
    int i, j;

    for (j = 0; j <= len; j++)
        dp[0][j] = false;

    for (i = 0; i <= len; i++)
        dp[i][0] = true;

    for (i = 1; i <= len; i++)
        for (j = 1; j <= volume; j++)
            dp[i][j] = dp[i - 1][j] ||
                (0 <= j - data[i] && j - data[i] <= volume && dp[i - 1][j - data[i]]);

    return dp[len][volume];
}


bool Bisection(vector<int> &data)
{
    if (data.size() <= 0)
        return false;

    // find sum
    int sum = 0, i;
    for (i = 0; i < data.size(); i++)
        sum += data[i];

    if (sum & 1)
        return false;

    // backpack
    return Backpack(data, sum / 2);
}


int main(int argc, char *argv[])
{
    string str;
    int x;
    bool res;

    // input case
    while (getline(myfile, str))
    {
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream ss(str);
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = Bisection(data);
        cout << (res ? "true" : "false") << endl;
    }

    return 0;
}