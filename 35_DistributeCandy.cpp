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


int NumDistrib(int m, int n)
{
    // number of distributions of putting m elements in n buckets,
    // dp[i][j] indicates number of distributions of putting i elements
    // in j buckets

    if (m < 1 || n < 1)
        return 0;

    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
    int i, j;

    for (j = 0; j <= n; j++)
        dp[0][j] = 1;

    for (i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            if (i < j)
                dp[i][j] = dp[i][i];
            else
                dp[i][j] = dp[i][j - 1] + dp[i - j][j];

    return dp[m][n];
}


int main(int argc, char *argv[])
{
    string str;
    int m, n;
    int res;

    // input case
    while (getline(myfile, str))
    {
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream ss(str);
        ss >> m; ss >> n;

        cout << m << ',' << n << endl;

        // result
        res = NumDistrib(m, n);
        cout << res << endl;
    }

    return 0;
}