#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <list>

using namespace std;

enum {MAX = 2009000999};


void readGraph(vector<list<pair<int, int>>> &g, int M) {
    int u, v, w;
    for (int i = 0; i < M; ++i) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
}

void relax(vector<int> &minPath, set<pair<int, int>> &orderOfVisit, 
    int u, int v, int w) {
        if (minPath[v] > minPath[u] + w) {
            orderOfVisit.erase({minPath[v], v});
            minPath[v] = minPath[u] + w;
            orderOfVisit.insert({minPath[v], v});
        } 
    }

void dijkstra(vector<list<pair<int, int>>> &graph, int s) {
    vector<int> minPath(graph.size(), MAX);
    minPath[s] = 0;
    set<pair<int, int>> orderOfVisit;
    for (int i = 0; i < graph.size(); ++i) {
        orderOfVisit.insert({minPath[i], i});
    }
    
    pair<int, int> cur;
    while (!orderOfVisit.empty()) {
        cur = *orderOfVisit.begin();
        orderOfVisit.erase(orderOfVisit.begin());
        for (auto v: graph[cur.second]) {
            relax(minPath, orderOfVisit, cur.second, v.first, v.second);
        }
    }
    for (int i = 0; i < minPath.size(); ++i) {
        cout << minPath[i] << " ";
    }
    cout << endl;
}

int main() {
    int NUM, N, M, s;
    cin >> NUM;

    for (int i = 0; i < NUM; ++i) {
        cin >> N >> M;
        vector<int> minPath(N, MAX);
        vector<list<pair<int, int>>> graph(N);
        readGraph(graph, M);
        cin >> s;
        dijkstra(graph, s);
    }
}
