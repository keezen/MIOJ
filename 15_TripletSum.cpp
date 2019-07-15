# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


int TripletSum(vector<int> &nums)
{
    if (nums.size() <= 3)
        return 0;

    sort(nums.begin(), nums.end());

    int i, j, k, sum, count = 0;
    for (i = 0; i < nums.size() - 2; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        sum = -nums[i];
        j = i + 1; k = nums.size() - 1;
        while (j < k)
        {
            // equal
            if (nums[j] + nums[k] == sum)
            {
                count++;
                while (j < k && nums[j] == nums[j + 1])
                    j++;
                while (j < k && nums[k] == nums[k - 1])
                    k--;
                j++;
            }
            else if (nums[j] + nums[k] < sum)
                j++;
            else
                k--;
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
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream ss(str);
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        // result
        res = TripletSum(data);
        PrintVec(data);
        cout << res << endl;
    }

    return 0;
}