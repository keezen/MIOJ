/*
- 小爱运维监控

序号：#123
难度：有挑战
时间限制：1000ms
内存限制：50M

描述
小爱后台对于每次请求服务都有一次服务质量评分告警，其数值 score 范围为 0~10, 
比如：当服务出现抖动,延迟增大或者返回不合预期时，score 会增大，当服务延迟较
小且返回正常时，score 会减小， 现在有一批某天的小爱服务日志，格式为：
id (每次请求 id ，全局唯一), start_time (服务开始时间，inclusive),
end_time(服务结束时间,exclusive),score(服务打分)， 后台系统的某一
刻t的告警分数 total_socre 为 t 时刻所有处于连接状态的服务分数之和 
为了计算简便， 已经将 start_time 与 end_time 转换为 unix timestamp 
时间戳, 现在运维想从日志中找出一天中整个系统服务的告警分数 total_score 
最大值, 要求申请的存储为常量.

输入
输入多个以空格分隔的整数，每 4 个整数为一组（组数<10^7），这 4 个整数分别
代表 id, start_time, end_time, score，其值均小于 10^6.

输出
输出一个整数，表示 total_score 的最大值

输入样例
1 6 10 4 2 3 8 3 3 7 9 1 4 5 6 2

输出样例
8
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <unordered_map>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


struct Service
{
    int id;
    int start_time;
    int end_time;
    int score;

    Service(int i, int st, int et, int s)
        : id(i), start_time(st), end_time(et), score(s)
    {}
};


ostream & operator<<(ostream &os, Service* rhs)
{
    cout << rhs->start_time << ',' << rhs->end_time << ',' << rhs->score;
    return os;
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




int MapTime(vector<Service *> &data)
{
    // map absolute time to relative

    if (data.size() <= 0)
        return 0;

    vector<int> times;
    int i;

    for (i = 0; i < data.size(); i++)
    {
        times.push_back(data[i]->start_time);
        times.push_back(data[i]->end_time - 1);
    }

    sort(times.begin(), times.end());

    // construct map
    unordered_map<int, int> hash;
    int idx = 1;
    hash[times[0]] = idx++;
    for (i = 1; i < times.size(); i++)
        if (times[i] != times[i - 1])
            hash[times[i]] = idx++;

    // map time
    for (i = 0; i < data.size(); i++)
    {
        data[i]->start_time = hash[data[i]->start_time];
        data[i]->end_time = hash[data[i]->end_time - 1];
    }

    return idx - 1;
}


int MaxTotalScore_Brute(vector<Service *> &data)
{
    // maximum total score in a day

    if (data.size() <= 0)
        return 0;

    vector<int> total_score(10, 0);
    int i, j;
    int st, et, score;
    int res = 0;

    // brute force
    for (i = 0; i < data.size(); i++)
    {
        st = data[i]->start_time;
        et = data[i]->end_time;
        score = data[i]->score;
        for (j = st; j < et; j++)
        {
            total_score[j] += score;
            res = max(total_score[j], res);
        }
    }

    return res;
}


int MaxTotalScore(vector<Service *> &data)
{
    // maximum total score in a day

    if (data.size() <= 0)
        return 0;

    int maxn = 0, i;

    // map time to positive integer
    MapTime(data);

    // maximum time
    for (i = 0; i < data.size(); i++)
        maxn = max(maxn, max(data[i]->start_time, data[i]->end_time));

    // use segment tree to track segment maximum
    vector<int> t(maxn, 0);
    SegTree st(t);
    for (i = 0; i < data.size(); i++)
        st.update(data[i]->start_time, data[i]->end_time, data[i]->score);

    return st.query(1, maxn);
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        vector<Service *> data;
        Service *p;
        int i, st, et, s;
        while (ss >> i)
        {
            ss >> st >> et >> s;
            p = new Service(i, st, et, s);
            data.push_back(p);
        }

        cout << line << endl;

        // result
        res = MaxTotalScore(data);
        cout << res << endl;

        for (i = 0; i < data.size(); i++)
            delete data[i];
    }

    return 0;
}