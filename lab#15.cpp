#include <iostream>
#include <vector>
#include <queue>
#include <utility>  
#include <limits>   
using namespace std;

int dijkstra_unit_weight(int start, int finish,
    const vector<vector<int>>& adj) {
    const int INF = 1e9;
    int n = adj.size();
    vector<int> dist(n, INF);
    dist[start] = 0;

    priority_queue<pair<int, int>,
        vector<pair<int, int>>,
        greater<>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        auto top = pq.top();    
        int d = top.first;
        int u = top.second;
        pq.pop();
        if (d > dist[u]) continue;
        if (u == finish) break;

        for (int v : adj[u]) {
            int nd = d + 1;    
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({ nd, v });
            }
        }
    }

    return dist[finish] == INF ? -1 : dist[finish];
}

int main() {
    vector<vector<int>> adj(6);
    adj[1] = { 2,5 };
    adj[2] = { 4 };
    adj[4] = { 3 };
    adj[3] = { 5 };

    cout << dijkstra_unit_weight(1, 2, adj) << "\n"; // 1
    cout << dijkstra_unit_weight(1, 5, adj) << "\n"; // 1
    cout << dijkstra_unit_weight(2, 5, adj) << "\n"; // 3
    cout << dijkstra_unit_weight(5, 1, adj) << "\n"; // -1
    cout << dijkstra_unit_weight(2, 1, adj) << "\n"; // -1

    return 0;
}
