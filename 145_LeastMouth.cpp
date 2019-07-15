/*
- 大胃王的烦恼

序号：#145
难度：有挑战
时间限制：2000ms
内存限制：128M

描述
又到了大胃王 xyq 进食的时间啦！

腰缠万贯他雇了 n 个厨师，每个厨师都会做一种不同的菜肴，而且他们
每个人只会在某个确定的时间点做菜给他吃。

现在天气越来越热了，厨师提醒大胃王，每道菜都有它的保质期，过了
保质期就不能再吃了。这么好吃的菜，怎么能浪费呢？他想一口气把这
n 个菜都吃完，然而他只有一张嘴，而且必须先吃完一道菜才能吃下一道菜。

大胃王现在很着急，因为他不想少吃一样菜。忽然，他有个大胆的想法：
如果多长几张嘴，就能同时吃很多道菜了！请你帮他计算一下最少需要
多少张嘴才能吃完这 n 道菜呢？

输入
第一行包含一个整数 n ,表示厨师的数量, 1≤N≤2⋅10^5.

接下来有 n 行，第 i 行包含两个整数 l_i, r_i，1≤l_i≤r_i≤10^18，
表示第 i 个厨师在 l_i 点做完菜并且大胃王开始吃，在 r_i 点大胃王
吃完这盘菜。

输出
输出一个数表示 xyq 至少需要多少张嘴巴可以同时吃完 n 个食物。

输入样例
2
1 2
2 3

输出样例
2
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <unordered_map>
using namespace std;


ifstream myfile("a.txt");


template <typename T> ostream & operator<<(ostream &os, pair<T, T> &rhs)
{
    cout << rhs.first << ',' << rhs.second;
    return os;
}


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    // print out a vector
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i];
        cout << ((i == data.size() - 1) ? eol : sep);
    }
}


class SegTree
{
public:
    SegTree(vector<int> &arr)
    {
        if (arr.size() <= 0)
            return;

        n = arr.size();
        seg_tree.assign(n << 2, 0);
        flag.assign(n << 2, 0);
        
        int pos = 0;
        build(arr, pos, 1, n, 1);
    }

    void PushUp(int rt)
    {
        // merge info from child nodes upward
        if (rt < 1 || rt >= seg_tree.size())
            return;

        seg_tree[rt] = max(seg_tree[rt << 1], seg_tree[rt << 1 | 1]);
    }

    void PushDown(int rt)
    {
        // propagate last update info downward to children

        if (rt < 1 || rt >= seg_tree.size())
            return;

        if (flag[rt])
        {
            int v = flag[rt];
            seg_tree[rt << 1] += v;  // left child
            flag[rt << 1] += v;
            seg_tree[rt << 1 | 1] += v;  // right child
            flag[rt << 1 | 1] += v;
            flag[rt] = 0;
        }
    }

    void build(vector<int> &arr, int &pos, int l, int r, int rt)
    {
        // build segment tree of current root (l,r,rt) given array

        if (arr.size() <= 0 || pos < 0 || pos >= arr.size())
            return;

        if (l < 1 || r > n || l > r || rt < 1 || rt >= seg_tree.size())
            return;

        if (l == r)  // leaf node
        {
            seg_tree[rt] = arr[pos++];
            return;
        }

        int m = (l + r) >> 1;
        build(arr, pos, l, m, rt << 1);  // build left tree
        build(arr, pos, m + 1, r, rt << 1 | 1);  // build right tree
        PushUp(rt);  // merge
    }

    void update(int L, int R, int v, int l, int r, int rt)
    {
        // update segment [L:R] by adding v to current root (l,r,rt)

        if (L > r || R < l)
            return;

        if (L <= l && r <= R)  // root covered
        {
            flag[rt] += v;
            seg_tree[rt] += v;
            return;
        }

        PushDown(rt);  // propagate last update downside

        int m = (l + r) >> 1;
        if (L <= m)
            update(L, R, v, l, m, rt << 1);  // update left tree
        if (m < R)
            update(L, R, v, m + 1, r, rt << 1 | 1);  // update right tree
        PushUp(rt);  // merge info
    }

    void update(int L, int R, int v)
    {
        // update segment [L:R] by adding v
        if (L < 1 || R > n)
            return;

        update(L, R, v, 1, n, 1);
    }

    int query(int L, int R, int l, int r, int rt)
    {
        // query maximum in segment [L:R], given root (l,r,rt)

        if (L > r || R < l)
            return 0;

        if (L <= l && r <= R)  // root covered
            return seg_tree[rt];

        PushDown(rt);  // last update downward

        int m = (l + r) >> 1;
        int res = 0;
        if (L <= m)
            res = max(res, query(L, R, l, m, rt << 1));  // query left tree
        if (m < R)
            res = max(res, query(L, R, m + 1, r, rt << 1 | 1));  // right

        return res;
    }

    int query(int L, int R)
    {
        // query maximum in segment [L:R]

        if (L < 1 || R > n)
            return 0;

        return query(L, R, 1, n, 1);
    }

// private:
    vector<int> seg_tree;
    vector<int> flag;
    int n;
};


int LeastMouth(vector<pair<long int, long int> > &data)
{
    // max value after segment operation

    if (data.size() <= 0)
        return 0;

    // collect all time
    vector<long int> time;
    int i;
    for (i = 0; i < data.size(); i++)
    {
        time.push_back(data[i].first);
        time.push_back(data[i].second);
    }

    // sort
    sort(time.begin(), time.end());

    // time map
    vector<long int> ix2time;
    ix2time.push_back(time[0]);
    for (i = 1; i < time.size(); i++)
    {
        if (time[i] != time[i - 1])
            ix2time.push_back(time[i]);
    }

    unordered_map<long int, int> time2ix;
    for (i = 0; i < ix2time.size(); i++)
        time2ix[ix2time[i]] = i;

    // max value by segment tree
    int n = ix2time.size();
    vector<int> arr(n, 0);
    SegTree st(arr);
    int l, r;
    for (i = 0; i < data.size(); i++)
    {
        l = time2ix[data[i].first] + 1;
        r = time2ix[data[i].second] + 1;

        st.update(l, r, 1);
    }

    int max_val = st.query(1, n);

    return max_val;
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int n;
        ss >> n;
        
        vector<pair<long int, long int> > data;
        long int l, r;
        while (n--)
        {
            getline(myfile, line);
            stringstream ss2(line);
            ss2 >> l >> r;
            data.push_back(make_pair(l, r));
        }

        PrintVec(data);

        // result
        res = LeastMouth(data);
        cout << res << endl;
    }

    return 0;
}