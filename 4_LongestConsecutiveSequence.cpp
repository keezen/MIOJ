# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <unordered_set>
using namespace std;


template <typename T> void PrintVec(vector<T> data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


bool InArray(vector<int> data, int num)
{
    for (int i = 0; i < data.size(); i++)
        if (data[i] == num)
            return true;

    return false;
}


int LongestConsecutiveSequence_Brute(vector<int> data)
{
    if (data.size() <= 0)
        return 0;

    int longset = 0;

    for (int i = 0; i < data.size(); i++)
    {
        int cur = data[i] + 1;
        int count = 1;
        while (InArray(data, cur))
        {
            cur++; count++;
        }
        longset = max(count, longset);
    }

    return longset;
}


int LongestConsecutiveSequence(vector<int> data)
{
    // LeetCode 128

    if (data.size() <= 0)
        return 0;

    // elements set
    unordered_set<int> dataset;
    for (int i = 0; i < data.size(); i++)
        dataset.insert(data[i]);

    int longset = 0;

    for (int i = 0; i < data.size(); i++)
    {
        // num - 1 in array, shorter sequence, skip
        if (dataset.find(data[i] - 1) != dataset.end())
            continue;

        // to do, prune duplicate element

        // compute sequence length from current number
        int cur = data[i] + 1;
        int count = 1;
        while (dataset.find(cur) != dataset.end())
        {
            cur++; count++;
        }
        longset = max(count, longset);
    }

    return longset;
}


int main(int argc, char *argv[])
{
    ifstream myfile("a.txt");
    string str;
    int x;
    int res;

    // input case
    while (getline(myfile, str))
    {
        // input array
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream ss(str);
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        res = LongestConsecutiveSequence(data);
        cout << res << endl;
    }

    myfile.close();

    return 0;
}