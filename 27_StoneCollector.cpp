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


int MaxValue(int volume, vector<int> weights, vector<int> values)
{
    // dp[i][j] indicates the max value of the first i elements,
    // given the backpack of volume j

    if (volume <= 0 || weights.size() <= 0 || values.size() <= 0 ||
        weights.size() != values.size())
        return 0;

    int len = weights.size();
    vector<vector<int> > dp(len + 1, vector<int>(volume + 1, 0));
    int i, j, t;

    for (i = 1; i <= len; i++)
        for (j = 1; j <= volume; j++)
        {
            dp[i][j] = dp[i - 1][j];
            t = j - weights[i - 1];
            if (0 <= t && t <= volume)
                dp[i][j] = max(dp[i - 1][t] + values[i - 1], dp[i][j]);
        }

    return dp[len][volume];
}



int main(int argc, char *argv[])
{
    string str;
    int volume, x;
    int res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss1(str);
        ss1 >> volume;

        getline(myfile, str);
        stringstream ss2(str);
        vector<int> weights;
        while (ss2 >> x)
            weights.push_back(x);

        getline(myfile, str);
        stringstream ss3(str);
        vector<int> values;
        while (ss3 >> x)
            values.push_back(x);

        cout << volume << endl;
        PrintVec(weights);
        PrintVec(values);

        // result
        res = MaxValue(volume, weights, values);
        cout << res << endl;
    }

    return 0;
}