#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n; 
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs (int s, int t, vector<int>& parent) {
    parent.assign(n, -1);
    
    parent[s] = -2;
    queue<pair<int, int>> q;
    
    q.push({s,INF}); //teme, protok do toa teme

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                //dali e neposeteno i ima uste kapcitet
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int fulkerson(int s, int f) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;
    int iteration = 1;

    while ((new_flow = bfs(s, f, parent))) {
        flow += new_flow;

        cout << "Iteracija " << iteration++ << ": ";
        
        vector<int> path;
        for (int cur = f; cur != s; cur = parent[cur])
            path.push_back(cur);
        path.push_back(s);
        reverse(path.begin(), path.end());

        cout << "Pat: ";
        for (int v : path) cout << v << " ";
        
        
        cout << " ... Protok: " << new_flow << "\n";

        int cur = f;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    

    cout << "Vnesi broj na teminja i rabovi: ";
    int m;
    cin >> n >> m;

    capacity.assign(n, vector<int>(n, 0));
    adj.assign(n, vector<int>());

    cout << "Vnesi rabovi vo format: u v w (od, do, kapacitet)\n";
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += w; // 0->1 w=5 0->1 w=7, vk w=12
    }

    int s,f;
    cout << "Vnesi pocetno i krajno teme: ";
    cin >> s >> f;

    int result = fulkerson(s,f);
    cout << "\nMaksimalen protok:" << result << "\n";
}

// od cp-alg primerot
// 6 9
// 0 1 7
// 0 4 4
// 1 2 5
// 1 3 3
// 4 1 3
// 4 3 2
// 2 5 8
// 3 2 3
// 3 5 5
// 0 5 
//poc kraj

