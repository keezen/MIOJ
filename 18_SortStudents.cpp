# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <algorithm>
# include <utility>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i].first << ' ' << data[i].second << ' ';
    cout << data.back().first << ' ' << data.back().second << endl;
}


bool is_less(pair<int, int> a, pair<int, int> b)
{
    return a.second < b.second || (a.second == b.second && a.first < b.first);
}


void SortStudents(vector<pair<int, int> > &data)
{
    if (data.size() <= 0)
        return;

    vector<pair<int, int> > copy(data);
    int i, j;

    for (i = 0; i < data.size(); i++)
    {
        // move min element to start
        for (j = copy.size() - 1; j > i; j--)
            if (is_less(copy[j], copy[j - 1]))
            {
                swap(copy[j], copy[j - 1]);
                swap(data[j], data[j - 1]);
            }

        // adjust element
        for (j = copy.size() - 1; j > i; j--)
            if (copy[j].first <= copy[i].first)
                copy[j].second -= 1;
    }
}


int main(int argc, char *argv[])
{
    string str;
    vector<pair<int, int> > data;
    int n, x, y;
    string res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> n;
        while (n--)
        {
            ss >> x; ss >> y;
            data.push_back(make_pair(x, y));
        }

        PrintVec(data);

        // result
        SortStudents(data);
        PrintVec(data);
    }

    return 0;
}