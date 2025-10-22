#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int n, m, s, t;
vector<vector<int>> adj;
vector<int> level, ptr;
vector<int> from, to;
vector<long long> cap, flow_val;

void add_edge(int v, int u, long long c) {
    from.push_back(v);
    to.push_back(u);
    cap.push_back(c);
    flow_val.push_back(0);
    adj[v].push_back(from.size()-1);

    from.push_back(u);
    to.push_back(v);
    cap.push_back(0);
    flow_val.push_back(0);
    adj[u].push_back(from.size()-1);
}

bool bfs() {
    fill(level.begin(), level.end(), -1);
    level[s]=0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v=q.front();
        q.pop();
        for (int id:adj[v]) {
            if (cap[id]-flow_val[id]<1) continue;
            if (level[to[id]]!=-1) continue;
            level[to[id]]=level[v]+1;
            q.push(to[id]);
        }
    }
    return level[t]!=-1;
}

long long dfs(int v, long long pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int &cid=ptr[v]; cid< (int)adj[v].size(); cid++) {
        int id = adj[v][cid];
        int u = to[id];
        if (level[v] + 1!=level[u] || cap[id] - flow_val[id] < 1)
            continue;
        long long tr = dfs(u, min(pushed, cap[id] - flow_val[id]));
        if (tr == 0) continue;
        flow_val[id] += tr;
        flow_val[id ^ 1] -= tr;
        return tr;
    }
    return 0;
}

long long dinic() {
    long long f=0;
    while (true) {
        if (!bfs()) break;
        fill(ptr.begin(), ptr.end(), 0);
        while (long long pushed = dfs(s, INF))
            f += pushed;
    }
    return f;
}

int main() {
    

    cin >> n >> m >> s >> t;
    adj.assign(n, {});
    level.resize(n);
    ptr.resize(n);

    for (int i=0; i<m; i++) {
        int v, u;
        long long capacity;
        cin >> v >> u >> capacity;
        add_edge(v, u, capacity);
    }

    cout << "Max flow =" << dinic();

    return 0;
}
