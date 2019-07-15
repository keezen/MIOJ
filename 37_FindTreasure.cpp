# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <queue>
# include <utility>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, void show(T&))
{
    for (int i = 0; i < data.size(); i++)
    {
        show(data[i]);
        if (i < data.size() - 1)
            cout << ' ';
        else
            cout << endl;
    }
}


void show(pair<int, int> &x)
{
    cout << '(' << x.first << ',' << x.second << ')';
}

void show(int &x)
{
    cout << x;
}


bool IsCircularGraph(vector<vector<int> > &adj)
{
    // whether a circle exists in a graph with n nodes,
    // given adjacent matrix

    if (adj.size() <= 0 || adj[0].size() <= 0)
        return false;

    // topological sort

    int n = adj.size();  // number of nodes
    vector<int> indegree(n, 0);  // in-degree of each node
    queue<int> q;
    int t;
    int i, j;

    // count in-degree
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (adj[i][j] > 0)
                indegree[j]++;

    // push nodes whose in-degree is 0
    for (i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push(i);

    while (!q.empty())
    {
        // remove a node whose in-degree is 0
        t = q.front(); q.pop();

        // update in-degree pointed from current node
        for (i = 0; i < n; i++)
            if (adj[t][i] > 0 && indegree[i] > 0)
                if (--indegree[i] == 0)
                    q.push(i);
    }

    // check whether a circle exists
    for (i = 0; i < n; i++)
        if (indegree[i] > 0)
            return true;

    return false;
}


bool IsAvailableTreasure(vector<pair<int, int> > &dep, int n)
{
    // whether treasure is available
    if (n <= 0)
        return false;

    if (dep.size() <= 0)
        return true;

    // adjacent matrix
    vector<vector<int> > adj(n, vector<int>(n));
    for (int i = 0; i < dep.size(); i++)
        adj[dep[i].first][dep[i].second] = 1;

    return !IsCircularGraph(adj);
}



int main(int argc, char *argv[])
{
    string str;
    int n;
    int a, b;
    vector<pair<int, int> > data;
    int res;

    // input case
    getline(myfile, str);
    stringstream ss(str);
    ss >> n;
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> a; ss >> b;
        data.push_back(make_pair(a, b));
    }

    cout << n << endl;
    PrintVec(data, show);

    // result
    res = IsAvailableTreasure(data, n);
    cout << (res ? "true" : "false") << endl;

    return 0;
}