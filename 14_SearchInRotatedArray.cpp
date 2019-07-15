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


int search(vector<int> &nums, int target)
{
    if (nums.size() <= 0)
        return -1;

    // binary search
    int start = 0, end = nums.size() - 1, mid;
    while (start <= end)
    {
        mid = (start + end) / 2;

        if (nums[mid] == target)
            return mid;

        // left
        if ((nums[start] <= nums[mid] && nums[start] <= target && target < nums[mid]) ||
            (nums[start] > nums[mid] && (target >= nums[start] || target < nums[mid])))
            end = mid - 1;
        else  // right
            start = mid + 1;
    }

    return -1;
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
        res = search(data, target);
        cout << res << endl;
    }

    return 0;
}