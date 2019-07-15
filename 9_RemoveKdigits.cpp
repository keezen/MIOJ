# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


string removeKdigits(string num, int k)
{
    if (num.size() <= 0 || k < 0 || k >= num.size())
        return string("0");

    string res;
    int i = 0, size = num.size() - k;
    for (i = 0; i < num.size(); i++)
    {
        // when current number smaller than stack top, remove top
        while (k > 0 && !res.empty() && num[i] < res.back())
        {
            res.pop_back(); k--;
        }
        res.push_back(num[i]);
    }

    // corner case like "12345 2"
    while (k--)
        res.pop_back();

    for (i = 0; i < res.size() && res[i] == '0'; i++) ;
    res = string(res.begin() + i, res.end());

    return res.empty() ? string("0") : res;
}


int main(int argc, char *argv[])
{
    string str;
    string num;
    int k;
    string res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> num; ss >> k;

        cout << num << ' ' << k << endl;

        // result
        res = removeKdigits(num, k);
        cout << res << endl;
    }

    return 0;
}