#include <iostream>
#include <vector>
#include <list>


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

    void readData(int M) {
        int tmpFirst;
        for (int i = 0; i < M; ++i) {
            cin >> tmpFirst;
            graph[tmpFirst - 1].push_back(i);
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

    void clear() {
        for (int i = 0; i < countVertex; ++i) {
            colorVertex[i] = WHITE;
        }
    }


private:
    vector<colors> colorVertex;
    int countVertex;
    vector<list<int>> graph;
};

void printCycle(Graph &g, int v) {
    cout << v + 1 << " ";
    for (auto u: g.getNeighbourhood(v)) {
        if (g.getColorVertex(u) == GRAY) {
            g.setColorVertex(v, BLACK);
            printCycle(g, u);
            break;
        }
    }
}

void visit(Graph &g, int v, list<int> &resTopSort) {
    g.setColorVertex(v, GRAY);
    for (auto u: g.getNeighbourhood(v)) {
        if (g.getColorVertex(u) == WHITE) {
            visit(g, u, resTopSort);
        }
    }
    resTopSort.push_front(v);
    g.setColorVertex(v, BLACK);
}

void dfs(Graph &g) {
    list<int> resultTopSort;
    for (int v = 0; v < g.getCountVertex(); ++v) {
        if (g.getColorVertex(v) == WHITE) {
            visit(g, v, resultTopSort);
        }
    }
    
    
    g.clear();

    int countPigs = 0;
    list<int> tmp;
    for (auto v: resultTopSort) {
        if (g.getColorVertex(v) == WHITE) {
            visit(g, v, tmp);
            ++countPigs;
        }
    }
    cout << countPigs << endl;
}


int main() {
    int N;
    cin >> N;
    Graph g(N);
    g.readData(N);
    dfs(g);
}
