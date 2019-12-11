#include <iostream>
#include <vector>
#include <list>

// by Anton Pilkevich

using namespace std;

enum {NOEDGE = 100000, INF = 1 << 30};


void relax(vector<int> &lenPath, int u, int v, int w, vector<int> &parent) {
    if (lenPath[v] > lenPath[u] + w) {
        lenPath[v] = lenPath[u] + w;
        parent[v] = u;
    }
}

void fordBellman(vector<int> &lenPath,
    list<pair<pair<int, int>, int>> &edges, 
    vector<int> &parent) {
    
    for (int i = 0; i < lenPath.size() - 1; ++i) {
        for (auto edge: edges) {
            relax(lenPath, edge.first.first, edge.first.second,
                edge.second, parent);
        }
    }
    
    int u, v;
    list<int> cycle;
    for (auto edge: edges) {
        u = edge.first.first;
        v = edge.first.second;
        if (lenPath[v] > lenPath[u] + edge.second) {
            parent[v] = u;
            for (int i = 0; i < lenPath.size(); ++i) {
                v = parent[v];
            }
            u = v;
            v = parent[v];
            if (v == -1) {
                cycle.push_front(u);
            }
            while (u != v) {
                cycle.push_front(v);
                v = parent[v];
            }
            cycle.push_front(v);
            cycle.push_back(v);
            break;
        }
    }i
    if (cycle.empty()) {
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
        cout << cycle.size() << endl;
        int k = 1;
        for (auto u: cycle) {
            if (k != cycle.size()) {
                cout << u + 1 << " ";
            }
            else {
                cout << u + 1;
            }
            ++k;
        }
        cout << endl;
    }
}

int main() {
    int N;
    cin >> N;

    vector<int> lenPath(N, INF);
    lenPath[0] = 0;
    list<pair<pair<int, int>, int>> edges;
    vector<int> parent(N, -1);

    int w;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> w;
            if (w != NOEDGE) {
                edges.push_back({{i, j}, w});
            }
        }
    }
    fordBellman(lenPath, edges, parent);
}
