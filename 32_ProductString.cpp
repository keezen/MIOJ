# include <iostream>
# include <cstdlib>
# include <fstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


bool ProductString(string s)
{
    // whether a string is the product string,
    // dp[i] indicates whether string[1:i] is a product string

    if (s.size() < 3)
        return false;

    int len = s.size(), i, j, k;
    vector<bool> dp(len + 1, false);
    vector<long int> first(len + 1, 0);
    vector<long int> second(len + 1, 0);
    long int p, a, b;

    for (i = 3; i <= len; i++)
        for (j = 3; j <= i; j++)
        {
            // s[j:i] is the current number
            p = stol(s.substr(j - 1, i - j + 1));

            // s[1:j-1] is a product string
            if (dp[j - 1] && p == first[j - 1] * second[j - 1])
            {
                dp[i] = true;
                first[i] = second[j - 1];
                second[i] = p;
                break;
            }

            // s[1:j-1] is not a product string
            for (k = 2; k <= j - 1; k++)
            {
                a = stol(s.substr(0, k - 1));  // s[1:k-1]
                b = stol(s.substr(k - 1, j - k));  // s[k:j-1]
                if (p == a * b)
                {
                    dp[i] = true;
                    first[i] = b;
                    second[i] = p;
                }
            }
        }

    return dp[len];
}


int main(int argc, char *argv[])
{
    string str;
    bool res;

    // input case
    while (getline(myfile, str))
    {
        cout << str << endl;

        // result
        res = ProductString(str);
        cout << (res ? "true" : "false") << endl;
    }

    return 0;
}