#include <bits/stdc++.h>
using namespace std;

int teminja = 0, rabovi = 0;

vector<int> bellman(int start, vector<vector<int>>& graf) {
    vector<int> dist(teminja, 1e8);
    dist[start] = 0;

    for (int i = 0; i < teminja; i++) {
        bool updated = false;

        for (auto &next : graf) {
            int u = next[0], v = next[1], w = next[2];
            if (dist[u] != 1e8 && dist[u] + w < dist[v]) {
                
                // posle vth iteracija ima neg ciklus
                if (i == teminja - 1) 
                    return {-1};
                
                dist[v] = dist[u] + w;
                updated = true;
            }
        }

        
    }

    return dist;
}

int main() {
    cin >> teminja >> rabovi;
    vector<vector<int>> graf;
    int a = 0, b = 0, w = 0;
    string op;

    cout << "choose option: random : self\n";
    cin >> op;

    if (op == "self") {
        for (int i = 0; i < rabovi; i++) {
            cin >> a >> b >> w;
            graf.push_back({a, b, w});
        }
    } else if (op == "random") {
        srand(time(0)); 
        for (int i = 0; i < rabovi; i++) {
            int u = rand() % teminja;
            int v = rand() % teminja;
            while (v == u) v = rand() % teminja; // avoid self-loop
            int w = (rand() % 21) - 3;          // weights in [-3, 17]
            graf.push_back({u, v, w});
        }
    }

    vector<int> dist = bellman(0, graf);

    ofstream fout("output.txt");
    if (dist.size() == 1 && dist[0] == -1) {
        fout << "Negative cycle detected\n";
    } else {
        for (auto d : dist) {
            if (d == 1e8) fout << "INF ";
            else fout << d << " ";
        }
    }
    fout.close();

    return 0;
}
