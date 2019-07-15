# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


template <typename T> void PrintVec(vector<T> data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


int MedianInRotatedSortedArray(vector<int> data)
{
    if (data.size() <= 0)
        return -1;

    if (data.front() <= data.back())
        return data[data.size() / 2];

    // find separate position
    int left = 0, right = data.size() - 1, mid;
    while (left < right - 1)
    {
        mid = (left + right) / 2;

        if (data[mid] <= data.back())
            right = mid;
        else
            left = mid;
    }

    // find median
    int sep = right, len = data.size();
    int median = data[(len / 2 + sep) % len];

    return median;
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

        // result
        res = MedianInRotatedSortedArray(data);
        cout << res << endl;
    }

    myfile.close();

    return 0;
}