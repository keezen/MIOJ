# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <unordered_map>
# include <algorithm>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


int ArithmeticProgression(vector<int> &data)
{
    if (data.size() <= 0)
        return 0;

    // record number of arithmetic progressions which ends
    // with current element
    vector<unordered_map<int, int> > map_arr(data.size());
    int i, j, count = 0, diff;
    for (i = 1; i < data.size(); i++)
        for (j = 0; j < i; j++)
        {
            diff = data[i] - data[j];

            map_arr[i][diff] += 1; count++;
            if (map_arr[j].find(diff) != map_arr[j].end())
            {
                map_arr[i][diff] += map_arr[j][diff];
                count += map_arr[j][diff];
            }
        }

    return count;
}


int main(int argc, char *argv[])
{
    string str;
    int x;
    int res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);

        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = ArithmeticProgression(data);
        cout << res << endl;
    }

    return 0;
}