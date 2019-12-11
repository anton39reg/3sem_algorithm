#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


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
        graph(mCountVertex, vector<int>()) {}

    void readData(int M) {
        int tmpFirst, tmpSecond;
        for (int i = 0; i < M; ++i) {
            cin >> tmpFirst >> tmpSecond;
            graph[tmpFirst - 1].push_back(tmpSecond - 1);
            graph[tmpSecond - 1].push_back(tmpFirst - 1);
        }
    }

    colors getColorVertex(int v) const {
        return colorVertex[v];
    }

    void setColorVertex(int v, colors c) {
        colorVertex[v] =  c;
    }

    vector<int> getNeighbourhood(int v) const {
        return graph[v];
    }

    int getCountVertex() {
        return countVertex;
    }


private:
    vector<colors> colorVertex;
    int countVertex;
    vector<vector<int>> graph;
};


void visit(Graph &g, int v, int p, int &time, vector<int> &tIn,
    vector<int> &up, set<int> &result) {
    time += 1;
    up[v] = time;
    tIn[v] = time;
    g.setColorVertex(v, GRAY);
    int countChildren = 0;
    for (auto u: g.getNeighbourhood(v)) {
        if (u == p) {
            continue;
        }
        if (g.getColorVertex(u) == WHITE) {
            visit(g, u, v, time, tIn, up, result);
            countChildren += 1;
            up[v] = min(up[v], up[u]);
            if (p != -1 && up[u] >= tIn[v]) {
                result.insert(v);
            }
        }
        else {
            up[v] = min(up[v], tIn[u]);
        }
    }
    if (p == -1 && countChildren >= 2) {
        result.insert(v);
    }
    g.setColorVertex(v, BLACK);
}

void dfs(Graph &g) {
    int time = 0;
    vector<int> timeIn(g.getCountVertex(), 0);
    vector<int> up(g.getCountVertex(), 0);
    set<int> result;
    for (int v = 0; v < g.getCountVertex(); ++v) {
        if (g.getColorVertex(v) == WHITE) {
            visit(g, v, -1, time, timeIn, up, result);
        }
    }
    cout << result.size() << endl;
    for (auto v: result) {
        cout << v + 1 << endl;
    }
}


int main() {
    int N, M;
    cin >> N >> M;
    Graph g(N);
    g.readData(M);
    dfs(g);
}
