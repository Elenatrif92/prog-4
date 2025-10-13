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
    cin >> n >> m; //n-teminja m-edges

    capacity.assign(n, vector<int>(n, 0));
    adj.assign(n, vector<int>());

    cout << "Vnesi rabovi vo format: u v w (od, do, kapacitet)\n";
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] = w; // 0->1 w=5 0->1 w=7, vk w=12
    }

    int s,f;
    cout << "Vnesi pocetno i krajno teme: ";
    cin >> s >> f;

    int result = fulkerson(s,f);
    cout << "\nMaksimalen protok:" << result << "\n";

    vector<vector<int>> originalAdj=adj;
    vector<vector<int>> originalCap=capacity;
    
    vector<pair<int,int>> allEdges;
    for (int u=0; u<n; u++) {
        for (int v : adj[u]) {
            if (originalCap[u][v] > 0) {
                allEdges.push_back({u,v});
            }
        }
    }
    
    
    int minFlow=result;
    pair<int,int> edgeToRemove={-1,-1};
    
    //brute force za sekoj edge
    for (auto edge : allEdges) {
        int a=edge.first;
        int b=edge.second;
    
        vector<vector<int>> dupAdj=originalAdj;
        vector<vector<int>> dupCap=originalCap;
    
        // nema edge(flow) sega, cpacity na flow=0 od a do b
        dupCap[a][b]=0;
        
        //sega skroz go nema egdot, i od adjlist i na a i na b
        auto it=find(dupAdj[a].begin(), dupAdj[a].end(), b);
        if (it!=dupAdj[a].end()) 
            dupAdj[a].erase(it);
            
        it=find(dupAdj[b].begin(), dupAdj[b].end(), a);
        if (it!=dupAdj[b].end())
            dupAdj[b].erase(it);
    
        // povikaj fordfulk
        adj=dupAdj;
        capacity=dupCap;
        int newFlow=fulkerson(s, f);
    
        if (newFlow<minFlow) {
            minFlow=newFlow;
            edgeToRemove={a, b};
        }
    }
    
    // Restore the original graph
    adj=originalAdj;
    capacity=originalCap;
    
    // Print results
    cout << "\n Rab: " <<edgeToRemove.first<<" "<< edgeToRemove.second<< "\n";
    cout << "Nov maksimalen protok po brisenje: "<< minFlow<< "\n";
}


