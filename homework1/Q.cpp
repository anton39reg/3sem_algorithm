#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <unordered_map>
#include <set>

using namespace std;


typedef enum {
    WHITE = 1,
    GRAY = 2,
    BLACK = 3
} colors;

class Graph {
public:
    Graph(int mCountVertex): colorVertex(mCountVertex, WHITE),
        countVertex(mCountVertex),
        graph(mCountVertex, list<int>()) {}

    void readData(int N) {
        int w;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> w;
                if (i == j) {
                    continue;
                }
                graph[i].push_back(j);
                weight.insert({w, {i, j}});
            }
        }
        for (int i = 0; i < N; ++i) {
            cin >> w;
            graph[N].push_back(i);
            graph[i].push_back(N);
            weight.insert({w, {N, i}});
            weight.insert({w, {i, N}});
        }
    }

    colors getColorVertex(int v) const {
        return colorVertex[v];
    }

    void setColorVertex(int v, colors c) {
        colorVertex[v] =  c;
    }

    list<int> getNeighbourhood(int v) const {
        return graph[v];
    }

    int getCountVertex() {
        return countVertex;
    }
    
    set<pair<int, pair<int, int>>> getWeight() const{
        return weight;
    }

private:
    vector<colors> colorVertex;
    int countVertex;
    vector<list<int>> graph;
    set<pair<int, pair<int, int>>> weight;
};

int get(vector<int> &p, int x) {
    if (p[x] != x) {
        p[x] = get(p, p[x]);
    }
    return p[x];
}

void unionComp(vector<int> &p, vector<int> &r, int x, int y) {
    x = get(p, x);
    y = get(p, y);
    if (x == y) {
        return;   
    }
    if (r[x] == r[y]) {
        ++r[x];
    }
    if (r[x] < r[y]) {
        p[x] = y;
    }
    else {
        p[y] = x;
    }
}


void kruskal(Graph &g) {
    vector<int> p(g.getCountVertex());
    vector<int> r(g.getCountVertex(), 0);
    for (int i = 0; i < g.getCountVertex(); ++i) {
        p[i] = i;
    }
    
    set<pair<int, pair<int, int>>> weight = g.getWeight();
    int res = 0;

    int v, u, w;
    for (auto edge: weight) {
        v = edge.second.first;
        u = edge.second.second;
        w = edge.first;
        if (get(p, u) != get(p, v)) {
            res += w;
            unionComp(p, r, u, v);
        }
    }
    cout << res << endl;
}

int main() {
    int N, M;
    cin >> N;
    Graph g(N + 1);
    g.readData(N);
    kruskal(g);
}
