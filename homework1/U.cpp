#include <iostream>
#include <vector>
#include <list>
using namespace std;

enum {MAX = 1 << 30};

struct edge {
    int u;
    int v;
    int w;
};

void relax(vector<pair<int, int>> &lenPath, int u, int v, int w, int K, int f) {
    if (lenPath[v].first > lenPath[u].first + w) {
        if (lenPath[u].second < K - 1 || (lenPath[u].second == K - 1 &&  v == f)) {
            lenPath[v].first = lenPath[u].first + w;
            lenPath[v].second = lenPath[u].second + 1 ;
        }
    }
    else if (lenPath[v].first == lenPath[u].first + w &&
        lenPath[u].second + 1 < lenPath[v].second) {
        if (lenPath[u].second < K - 1 || (lenPath[u].second == K - 1 &&  v == f)) {
            lenPath[v].first = lenPath[u].first + w;
            lenPath[v].second = lenPath[u].second + 1 ;
        }
    }
}

void fordBellman(vector<pair<int, int>> &lenPath, vector<edge> &edges,
    int K, int s, int f) {

    for (int i = 0; i < K; ++i) {
        for (auto e: edges) {
            relax(lenPath, e.u, e.v, e.w, K, f);
        }
    }

    if (lenPath[f].first == MAX) {
        cout << -1 << endl;
    }
    else {
        cout << lenPath[f].first << endl;
    }
}

int main() {
    int N, M, K, s, f;
    cin >> N >> M >> K >> s >> f;

    vector<pair<int, int>> lenPath(N, {MAX, MAX});
    lenPath[s - 1] = {0, 0};
    vector<edge> edges(M);

    edge e; 
    for (int i = 0; i < M; ++i) {
        cin >> e.u >> e.v >> e.w;
        --e.u;
        --e.v;
        edges[i] = e;
    }

    fordBellman(lenPath, edges, K, s - 1, f - 1);
}
