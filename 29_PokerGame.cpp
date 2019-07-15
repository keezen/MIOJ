# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <algorithm>
# include <functional>
# include <utility>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


vector<int> Convert(vector<string> &s1)
{
    if (s1.size() != 5)
        return vector<int>();

    vector<int> cards;
    for (int i = 0; i < s1.size(); i++)
        if ('0' <= s1[i][0] && s1[i][0] <= '9')
            cards.push_back(stoi(s1[i]));
        else if (s1[i][0] == 'A')
            cards.push_back(14);
        else if (s1[i][0] == 'J')
            cards.push_back(11);
        else if (s1[i][0] == 'Q')
            cards.push_back(12);
        else if (s1[i][0] == 'K')
            cards.push_back(13);

    return cards;
}


bool compare(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second || (a.second == b.second && a.first > b.first);
}


vector<int> Normalize(vector<int> &cards)
{
    if (cards.size() != 5)
        return vector<int>();

    sort(cards.begin(), cards.end(), greater<int>());

    vector<int> count(15);
    vector<int> norm;
    vector<pair<int, int> > ele_count;
    int cat, i;

    // count
    for (i = 0; i < cards.size(); i++)
        count[cards[i]]++;

    // element and count
    for (i = 15; i > 1; i--)
        if (count[i] > 0)
            ele_count.push_back(make_pair(i, count[i]));
    sort(ele_count.begin(), ele_count.end(), compare);

    // category
    if (ele_count[0].second == 1 && ele_count[0].first - ele_count.back().first == 4)
        cat = 7;
    else if (ele_count[0].second == 4)
        cat = 6;
    else if (ele_count[0].second == 3 && ele_count[1].second == 2)
        cat = 5;
    else if (ele_count[0].second == 3 && ele_count[1].second == 1)
        cat = 4;
    else if (ele_count[0].second == 2 && ele_count[1].second == 2)
        cat = 3;
    else if (ele_count[0].second == 2 && ele_count[1].second == 1)
        cat = 2;
    else
        cat = 1;

    // normalize
    norm.push_back(cat);
    for (i = 0; i < ele_count.size(); i++)
        norm.push_back(ele_count[i].first);

    return norm;
}


int CompareCard(vector<string> &s1, vector<string> &s2)
{
    if (s1.size() != 5 || s2.size() != 5)
        return 0;

    vector<int> cards1 = Convert(s1), cards2 = Convert(s2);
    vector<int> norm1 = Normalize(cards1), norm2 = Normalize(cards2);

    if (norm1[0] > norm2[0])
        return 1;
    if (norm1[0] < norm2[0])
        return -1;

    for (int i = 1; i < norm1.size(); i++)
        if (norm1[i] > norm2[i])
            return 1;
        else if (norm1[i] < norm2[i])
            return -1;

    return 0;
}


int main(int argc, char *argv[])
{
    string str;
    string x;
    int res;

    // input case
    while (getline(myfile, str))
    {
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = '\n';

        stringstream ss(str);

        vector<string> cards1;
        getline(ss, str);
        stringstream ss1(str);
        while (ss1 >> x)
            cards1.push_back(x);

        vector<string> cards2;
        getline(ss, str);
        stringstream ss2(str);
        while (ss2 >> x)
            cards2.push_back(x);

        PrintVec(cards1);
        PrintVec(cards2);

        // result
        res = CompareCard(cards1, cards2);
        if (res > 0)
            x = "win";
        else if (res < 0)
            x = "lose";
        else
            x = "draw";
        cout << x << endl;
    }

    return 0;
}