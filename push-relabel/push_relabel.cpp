#include <bits/stdc++.h>
#include <ctime>
using namespace std;

const int inf = 1000000000;

int n_nodes;
vector<vector<int>> capacity, flow;
vector<int> height, excess, seen;
queue<int> excess_vertices;
vector<bool> active; // За да знаеме дали јазолот е веќе во опашката

void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);

    flow[u][v] += d;
    flow[v][u] -= d;

    excess[u] -= d;
    excess[v] += d;

    // Ако v има вишок, не е извор/sink и НЕ Е веќе во опашката
    if (d > 0 && excess[v] > 0 && !active[v]) {
        excess_vertices.push(v);
        active[v] = true;
    }
}

void relabel(int u) {
    int d = inf;
    for (int i = 0; i < n_nodes; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}

void discharge(int u) {
    while (excess[u] > 0) {
        if (seen[u] < n_nodes) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v]) {
                push(u, v);
            } else {
                seen[u]++;
            }
        } else {
            relabel(u);
            seen[u] = 0;
        }
    }
}

int max_flow(int s, int t) {
    // Иницијализација
    height.assign(n_nodes, 0);
    height[s] = n_nodes;

    flow.assign(n_nodes, vector<int>(n_nodes, 0));
    excess.assign(n_nodes, 0);
    seen.assign(n_nodes, 0);
    active.assign(n_nodes, false); // Ресетирај active

    // Изворот и понорот никогаш не ги ставаме во опашката за обработка
    active[s] = true;
    active[t] = true;

    excess[s] = inf;

    // Почетно туркање од изворот (Pre-flow)
    for (int i = 0; i < n_nodes; i++) {
        if (capacity[s][i] > 0)
            push(s, i);
    }


    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        active[u] = false; // Го вадиме од статус "активен" за да може пак да влезе ако треба
        discharge(u);
    }

    int total_flow = 0;
    for (int i = 0; i < n_nodes; i++)
        total_flow += flow[i][t]; // Колку влегло во t


    return total_flow;
}
void generate_random_graph(int max_nodes, int& s, int& t) {
    srand(time(0));
    n_nodes = (rand() % (max_nodes - 1)) + 2;
    capacity.assign(n_nodes, vector<int>(n_nodes, 0));

    s = 0;
    t = n_nodes - 1;

    int max_edges = n_nodes * (n_nodes - 1) / 2;
    int num_edges = (rand() % max_edges) + 1;

    for (int k = 0; k < num_edges; ++k) {
        int u, v;
        do {
            u = rand() % n_nodes;
            v = rand() % n_nodes;
        } while (u == v || capacity[u][v] > 0 || v == s); // Избегнува самостојни јамки и ребра кон s

        // Капацитет од 1 до 100
        capacity[u][v] = (rand() % 100) + 1;
    }

    cout << "\nGrafot e generiran so: " << n_nodes << " jazli\n";
    cout << " s: " << s << endl;
    cout << " t: " << t << endl;

    cout << "\n--- Rebra vo generiraniot graf ---\n";
    for (int u = 0; u < n_nodes; u++) {
        for (int v = 0; v < n_nodes; v++) {
            if (capacity[u][v] > 0) {
                cout << (u+1) << " -> " << (v+1)
                     << "   cap=" << capacity[u][v] << "\n";
            }
        }
    }
}
void input_custom_graph() {
    int m_edges;
    cout << "Vnesi n i m: ";
    cin >> n_nodes >> m_edges;

    if (cin.fail()) {
        return;
    }

    capacity.assign(n_nodes, vector<int>(n_nodes, 0));

    cout << "Vnesi rebra (u v capacity):\n";
    for (int i = 0; i < m_edges; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        capacity[u-1][v-1] = c; //0-ind
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    int s, t, opc;
    cout << "Vnesi opcija: 1.Input 2.Random generiran \n";
    cin >> opc;

    if(opc == 1) {
        input_custom_graph();
        s=0, t=n_nodes-1;
    }
    else {
        generate_random_graph(50, s, t);
    }

    if (n_nodes == 0) return 0;

    start = clock();
    int result = max_flow(s, t);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Maxflow: " << result << endl;

    cout << "\n\n";
    cout << "Vreme na izvrushuvanje: "
              << std::fixed << std::setprecision(10) << cpu_time_used
              << " sec" << std::endl;

    return 0;
}
