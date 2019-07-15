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


int MininumSwap_Brute(vector<int> &data)
{
    if (data.size() <= 1)
        return 0;

    int count = 0;
    for (int i = 0; i < data.size(); i++)
        for (int j = i + 1; j < data.size(); j++)
            if (data[i] > data[j])
                count++;
    return count;
}


int MergeSort(vector<int> &data, vector<int> &copy, int start, int end)
{
    // number of reverse pairs, by merge sort
    if (data.size() <= 1 || start < 0 || end < 0 || start >= end)
        return 0;

    int mid = (start + end) / 2;
    int left = MergeSort(data, copy, start, mid);  // left
    int right = MergeSort(data, copy, mid + 1, end);  // right

    // between
    int between = 0;
    int i = mid, j = end, k = end;
    while (i >= start && j >= mid + 1)
    {
        if (data[i] > data[j])
        {
            copy[k--] = data[i--];
            between += (j - mid);
        }
        else
            copy[k--] = data[j--];
    }

    while (i >= start)
        copy[k--] = data[i--];
    while (j >= mid + 1)
        copy[k--] = data[j--];

    for (i = start; i <= end; i++)
        data[i] = copy[i];

    return left + right + between;
}


int MininumSwap(vector<int> &data)
{
    // number of reverse pairs, by merge sort
    if (data.size() <= 1)
        return 0;

    vector<int> copy(data);
    return MergeSort(data, copy, 0, data.size() - 1);
}


int main(int argc, char *argv[])
{
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

        // PrintVec(data);

        // result
        res = MininumSwap(data);
        cout << res << endl;
    }

    return 0;
}