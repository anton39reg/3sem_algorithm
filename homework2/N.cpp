#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;

enum {INF = 1 << 30};

int dfsVisit(vector<unordered_map<int, int>> &graph, vector<bool> &visited, 
    int s, int d, int curFlow) {
        if (s == d) {
            return curFlow;
        }
        visited[s] = true;
        int res;
        for (auto tmp: graph[s]) {
            int v = tmp.first;
            int w = tmp.second;
            if (visited[v] == false && w != 0) {
                res = dfsVisit(graph, visited, v, d, min(w, curFlow));
                //cout << s << " ---> " << v << "  " << res << endl;
                if (res > 0) {
                    graph[s][v] -= res;
                    graph[v][s] += res;
                    return res;
                }
            }
        }
        return 0;
    }

int dfs(vector<unordered_map<int,int>> &graph, int s, int d) {
    vector<bool> visited(graph.size(), 0);
    return dfsVisit(graph, visited, s, d, INF);
}


int bfs(vector<unordered_map<int, int>> graph, int s, int d, int &countBfs, 
    vector<int> &col, vector<int> &parent) {
    queue<int> order;
    order.push(s);

    bool found = false;
    
    while (!order.empty()) {
        int u = order.front();
        order.pop();
        for (auto [v, w]: graph[u]) {
            if (w && col[v] != countBfs) {
                col[v] = countBfs;
                parent[v] = u;
                if (v == d) {
                    found = true;
                    break;
                }
                order.push(v);
            }
        }
        col[u] = countBfs;
    }

    if (found) {
        int stream = graph[parent[d]][d];
        int cur = d;
        while (cur != s) {
            if (graph[parent[cur]][cur] < stream) {
                stream = graph[parent[cur]][cur];
            }
            cur = parent[cur];
        }
        cur = d;
        while (cur != s) {
            graph[parent[cur]][cur] -= stream;
            graph[cur][parent[cur]] += stream;
            cur = parent[cur];
        }
        return stream;
    }
    return 0;
} 


int edmondsCarp(vector<unordered_map<int,int>> graph, int s, int d) {
    int res = 0;
    int flow = INF;
    int countBfs = 1;
    
    vector<int> col(graph.size(), 0);
    vector<int> parent(graph.size(), -1);

    while (flow != 0) {
       // cout << flow << endl;
        flow = bfs(graph, s, d, countBfs, col, parent);
        res += flow;
        ++countBfs;
    }
    return res;
}

int main() {
    int s, d, w;
    int N, M;
    cin >> N >> M;
    vector<unordered_map<int, int>> graph(N);
    for (int i = 0; i < M; ++i) {
        cin >> s >> d >> w;
        --s;
        --d;
        graph[s][d] = w;
    }
    s = 0;
    d = N - 1;
    cout << edmondsCarp(graph, s, d) << endl;
}
