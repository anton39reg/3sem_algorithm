#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;


typedef enum {
    WHITE = 1,
    GRAY = 2,
    BLACK = 3
} colors;

class Graph {
public:
    Graph(int mCountVertex, int mCountEdges): colorVertex(mCountVertex, WHITE),
        countVertex(mCountVertex),
        graph(mCountVertex, list<int>()),
        weight(mCountEdges) {}

    void readData(int M) {
        int tmpFirst, tmpSecond, w;
        for (int i = 0; i < M; ++i) {
            cin >> tmpFirst >> tmpSecond >> w;
            graph[tmpFirst - 1].push_back(tmpSecond - 1);
            graph[tmpSecond - 1].push_back(tmpFirst - 1);
            weight[i] = {w, {tmpFirst-1, tmpSecond -1}};
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
    
    vector<pair<int, pair<int, int>>> getWeight() const{
        return weight;
    }

private:
    vector<colors> colorVertex;
    int countVertex;
    vector<list<int>> graph;
    vector<pair<int, pair<int, int>>> weight;
};

int get(unordered_map<int, int> &p, int x) {
    if (p[x] != x) {
        p[x] = get(p, p[x]);
    }
    return p[x];
}

void unionComp(unordered_map<int, int> &p, unordered_map<int, int> &r, int x, int y) {
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

int comporate(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
    if (a.first < b.first) {
        return 1;
    }
    return 0;
}

void kruskal(Graph &g) {
    unordered_map<int, int> p;
    unordered_map<int, int> r;
    for (int i = 0; i < g.getCountVertex(); ++i) {
        p[i] = i;
        r[i] = 0;
    }
    
    vector<pair<int, pair<int, int>>> weight = g.getWeight();
    sort(weight.begin(), weight.end(), comporate);
    int res = 0;

    int v, u, w;
    for (int i = 0; i < weight.size(); ++i) {
        v = weight[i].second.first;
        u = weight[i].second.second;
        w = weight[i].first;
        if (get(p, u) != get(p, v)) {
            res += w;
            unionComp(p, r, u, v);
        }
    }
    cout << res << endl;
}

int main() {
    int N, M;
    cin >> N >> M;
    Graph g(N, M);
    g.readData(M);
    kruskal(g);
}
