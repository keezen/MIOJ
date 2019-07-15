/*
- 共边三角形

序号：#104
难度：非常难
时间限制：2500ms
内存限制：20M

描述
这一题实在没办法植入广告，直接感谢小米生态链企业品罗及亿联客强力赞助：

已知原点O坐标为(0,0)，给定x轴正半轴一个点A(x, 0)，再给出第一象限的nn个点
(x_1,y_1), (x_2,y_2), … , (x_n,y_n)，这n个点分别向原点O和点A连线，
得到n个三角形，某些三角形间可能存在包含关系，要求两个存在包含关系的三角形
只能有OA这一条边共线。

求三角形个数最多的包含关系，只需输出此包含关系中三角形的个数。


输入
输入数据为空格分隔的多个数：

第 1 个数字为A点横坐标x;

第 2 个数字为第一象限点的个数n;

接下来数据是n个二元组的横坐标和纵坐标，代表这n个点的坐标，以
x_1  y_1  x_2  y_2 ... x_n  y_n的顺序给出。

数据范围：0 < x < 100000000, 0 < n < 10009, 0 < x_i < 100000000,
0 < y_i < 100000000，保证无重复的点。

输出
三角形个数最多的包含关系中的三角形个数。

输入样例
5 5 1 1 2 2 3 3 4 4 5 5

输出样例
1
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <climits>
# include <cmath>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    if (data.size() <= 0)
    {
        cout << eol;
        return;
    }

    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;

    cout << data.back() << eol;
}


double xa;


bool include(int x, pair<double, double> &a, pair<double, double> &b)
{
    double x1 = a.first, y1 = a.second;
    double x2 = b.first, y2 = b.second;

    double ka1 = y1 / x1, ka2 = (x1 - x) / y1;
    double kb1 = y2 / x2, kb2 = (x2 - x) / y2;

    // triangle of a includes triangle b
    return ka1 > kb1 && ka2 > kb2;
}


bool compare_vertex(pair<double, double> &a, pair<double, double> &b)
{
    double x1 = a.first, y1 = a.second;
    double x2 = b.first, y2 = b.second;

    double ka1 = y1 / x1, ka2 = (x1 - xa) / y1;
    double kb1 = y2 / x2, kb2 = (x2 - xa) / y2;

    // inner triangle goes before outer
    if (ka1 < kb1)
        return true;

    if (ka1 == kb1 && ka2 < kb2)
        return true;

    return false;
}


int MaxIncludedTriangle_Brute(double x, vector<pair<double, double> > &vertexes)
{
    // max number of triangles in consecutive inclusion relation

    if (vertexes.size() <= 0 || x <= 0)
        return 0;

    // sort, inner triangle goes before the outer one
    xa = x;
    sort(vertexes.begin(), vertexes.end(), compare_vertex);

    int i, j, n = vertexes.size();
    vector<int> dp(n, 1);

    int res = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < i; j++)
            // j is included in i
            if (include(x, vertexes[i], vertexes[j]))
                dp[i] = max(dp[i], dp[j] + 1);

        res = max(dp[i], res);
    }

    return res;
}


class MaxSegmentTree
{
public:
    MaxSegmentTree(vector<int> &arr)
    {
        // construct segment tree

        n = arr.size();
        seg_tree = vector<int>(2 * n, 0);

        int i;
        for (i = n; i < 2 * n; i++)
            seg_tree[i] = arr[i - n];

        for (i = n - 1; i > 0; i--)
            seg_tree[i] = max(seg_tree[2 * i], seg_tree[2 * i + 1]);
    }

    void update(int pos, int val)
    {
        // set arr[pos] = val, update segment tree, 0 <= pos < n

        int i = pos + n;
        seg_tree[i] = val;

        for (i >>= 1; i > 0; i >>= 1)
            seg_tree[i] = max(seg_tree[2 * i], seg_tree[2 * i + 1]);
    }

    int query(int left, int right)
    {
        // query max in arr[left:right], while right excluded

        int l = left + n, r = right + n;
        int res = INT_MIN;

        while (l < r)
        {
            // left is out of range of parent interval, check value of
            // left node first, then shift it right in the same level
            if (l & 1)
            {
                res = max(res, seg_tree[l]);
                l += 1;
            }

            // right is out of range of current interval, shift it left
            // in the same level and then check the value
            if (r & 1)
            {
                r -= 1;
                res = max(res, seg_tree[r]);
            }

            l >>= 1; r >>= 1;
        }

        return res;
    }

// private:
    int n;
    vector<int> seg_tree;
};


struct Vertex
{
    double angle1;
    double angle2;
    int id;
    int val;

    Vertex(double a1, double a2, int i, int v)
        : angle1(a1), angle2(a2), id(i), val(v)
    {}
};


const double eps = 1e-5;


bool compare_angle1(Vertex *va, Vertex *vb)
{
    if (va == NULL || vb == NULL)
        return false;

    return (va->angle1 < vb->angle1) ||
        (va->angle1 == vb->angle1 && va->angle2 < va->angle2);
}


bool compare_angle2(Vertex *va, Vertex *vb)
{
    if (va == NULL || vb == NULL)
        return false;

    return (va->angle2 < vb->angle2) ||
        (va->angle2 == vb->angle2 && va->angle1 < va->angle1);
}


int MaxIncludedTriangle(double x, vector<pair<double, double> > &vertexes)
{
    // max number of triangles in consecutive inclusion relation,
    // implemented by segment tree

    if (vertexes.size() <= 0 || x <= 0)
        return 0;

    // compute angles with x-axis
    int n = vertexes.size(), i, j;
    vector<Vertex *> data(n);
    double xi, yi;
    Vertex *v;
    for (i = 0; i < n; i++)
    {
        xi = vertexes[i].first; yi = vertexes[i].second;
        v = new Vertex(yi / xi, (xi - x) / yi, i, 0);
        data[i] = v;
    }

    // sort by angle 2, assign id
    sort(data.begin(), data.end(), compare_angle2);
    data[0]->id = 0;
    for (i = 1; i < n; i++)
        if (data[i]->angle2 > data[i - 1]->angle2)
            data[i]->id = data[i - 1]->id + 1;
        else
            data[i]->id = data[i - 1]->id;
    int m = data.back()->id + 1;

    // sort by angle 1, track max path by segment tree
    sort(data.begin(), data.end(), compare_angle1);

    vector<Vertex *> buf;
    vector<int> path(m, 0);
    MaxSegmentTree mst(path);

    data[0]->val = 1;
    buf.push_back(data[0]);
    for (i = 1; i <= n; i++)
    {
        // angle 1 of i-th vertex is not equal to that of (i-1)-th vertex
        if (i == n || data[i]->angle1 > data[i-1]->angle1)
        {
            while (!buf.empty())
            {
                v = buf.back(); buf.pop_back();
                mst.update(v->id, v->val);
            }
        }

        if (i == n) break;

        data[i]->val = max(0, mst.query(0, data[i]->id)) + 1;
        buf.push_back(data[i]);
    }

    int res = mst.query(0, m);

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // int arr[] = {1, 2, 3, 4, 5};
    // vector<int> data(arr, arr + sizeof(arr) / sizeof(arr[0]));
    // MaxSegmentTree mst(data);
    // cout << mst.query(0, 4) << endl;
    // exit(0);

    // input case
    while (getline(myfile, line))
    {
        double xa;
        int n;
        vector<pair<double, double> > vertexes;

        stringstream ss(line);
        ss >> xa; ss >> n;
        double x, y;
        while (ss >> x)
        {
            ss >> y;
            vertexes.push_back(make_pair(x, y));
        }

        cout << line << endl;

        // result
        res = MaxIncludedTriangle(xa, vertexes);
        cout << res << endl;
        cout << "********" << endl;
    }

    return 0;
}