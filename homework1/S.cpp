#include <iostream>
#include <vector>
#include <list>

using namespace std;

enum {MAX = 30000};


void relax(vector<int> &lenPath, int u, int v, int w) {
    if (lenPath[u] != MAX && (lenPath[v] > lenPath[u] + w)) {
        lenPath[v] = lenPath[u] + w;
    }
}

void fordBellman(vector<int> &lenPath,
    vector<pair<pair<int, int>, int>> &edges) {
    for (int i = 0; i < lenPath.size() - 1; ++i) {
        for (auto edge: edges) {
            relax(lenPath, edge.first.first, edge.first.second, edge.second);
        }
    }

    for (int i = 0; i < lenPath.size(); ++i) {
        cout << lenPath[i] << " ";
    }
    cout << endl;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> lenPath(N, MAX);
    lenPath[0] = 0;
    vector<pair<pair<int, int>, int>> edges(M);

    int u, v, w;
    for (int i = 0; i < M; ++i) {
        cin >> u >> v >> w;
        edges[i] = {{u - 1, v - 1}, w};
    }
    
    fordBellman(lenPath, edges);
}
