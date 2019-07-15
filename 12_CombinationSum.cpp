# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


void CombinationSum(vector<int>& data, int target, int &sum, int &count)
{
    // DFS with duplicate
    if (data.size() <= 0 || sum > target)
        return;

    if (sum == target)
    {
        count++;
        return;
    }

    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
        CombinationSum(data, target, sum, count);
        sum -= data[i];
    }
}


int CombinationSum_DFS(vector<int>& data, int target)
{
    if (data.size() <= 0)
        return 0;

    int sum = 0, count = 0;
    CombinationSum(data, target, sum, count);
    return count;
}


int CombinationSum(vector<int>& data, int target)
{
    if (data.size() <= 0 || target < 0)
        return 0;

    if (target == 0)
        return 1;

    int count = 0;
    for (int i = 0; i < data.size(); i++)
        count += CombinationSum(data, target - data[i]);

    return count;
}


int main(int argc, char *argv[])
{
    string str;
    int x, target;
    int res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> str; ss >> target;

        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream sss(str);
        vector<int> data;
        while (sss >> x)
            data.push_back(x);

        PrintVec(data);
        cout << target << endl;

        // result
        res = CombinationSum(data, target);
        cout << res << endl;
    }

    return 0;
}