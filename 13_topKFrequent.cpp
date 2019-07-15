# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <map>
# include <algorithm>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


bool is_greater(const pair<int, int> a, const pair<int, int> b)
{
    return a.second > b.second;
}


bool is_less(const pair<int, int> a, const pair<int, int> b)
{
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}


vector<int> topKFrequent(vector<int> &nums, int k)
{
    if (nums.size() <= 0 || nums.size() < k)
        return vector<int>();

    // count frequency
    map<int, int> freq;
    int i;
    for (i = 0; i < nums.size(); i++)
        if (freq.find(nums[i]) == freq.end())
            freq[nums[i]] = 1;
        else
            freq[nums[i]] += 1;

    // top k frequent, using min heap
    vector<pair<int, int> > heap;
    map<int, int>::iterator it;
    for (it = freq.begin(); it != freq.end(); it++)
    {
        if (heap.size() == k && !is_greater(*it, heap.front()))
            continue;

        if (heap.size() == k && is_greater(*it, heap.front()))
        {
            pop_heap(heap.begin(), heap.end(), is_greater);
            heap.pop_back();
        }

        heap.push_back(*it);
        push_heap(heap.begin(), heap.end(), is_greater);
    }

    // yield result
    sort(heap.begin(), heap.end(), is_less);
    vector<int> res;
    for (i = 0; i < heap.size(); i++)
        res.push_back(heap[i].first);

    return res;
}


int main(int argc, char *argv[])
{
    string str;
    int x, k;
    vector<int> res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> str; ss >> k;

        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream sss(str);
        vector<int> data;
        while (sss >> x)
            data.push_back(x);

        PrintVec(data);
        cout << k << endl;

        // result
        res = topKFrequent(data, k);
        PrintVec(res);
    }

    return 0;
}