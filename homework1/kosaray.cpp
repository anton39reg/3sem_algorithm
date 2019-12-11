#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <utility>


using namespace std;


enum {WHITE = 1, GRAY = 2, BLACK = 3};


class Node{
public:
    Node(int mColor = WHITE): color(mColor){}

    void setColor(int mColor) {
        color = mColor;
    }

    int getColor(){
        return color;
    }

private:
    int color;
};


class Graph{
public:
    Graph(int mCountVertex): vertex(mCountVertex), countVertex(mCountVertex),
                           graph(mCountVertex, list<int>()) {}
    
    Graph(vector<list<int>> mGraph): vertex(mGraph.size()), 
        countVertex(mGraph.size()), graph(mGraph) {};

    void readData(int N){
        int tmpFirst = 0;
        int tmpSecond = 0;	
        for (int i = 0; i < N; ++i){
            cin >> tmpFirst >> tmpSecond;
            graph[tmpFirst - 1].push_back(tmpSecond - 1);
        }
    }
    
    int getCountVertex() const {
        return countVertex;
    }

    Node& getVertex(int v){
        return vertex[v];
    }

    list<int> operator[](int i){
        return graph[i];
    }

    void addTimeVertex(int time, int v) {
        timeVertex[time] = v;    
    }
    
    map<int, int> getTimeVertex() const {
        return timeVertex;
    }

    vector<list<int>> getReverseGraph() {
        vector<list<int>> result(countVertex);
        for (int i = 0; i < countVertex; ++i) {
            for (auto v: graph[i]) {
                result[v].push_back(i);
            }
        }
        return result;
    }

private:
    vector<Node> vertex;
    vector<list<int>> graph;
    int countVertex;
    map<int, int> timeVertex;
};


void visitSort(Graph &g, int v, int  &time){
    g.getVertex(v).setColor(GRAY);
    ++time;
    for (auto num: g[v]){
        if (g.getVertex(num).getColor() == WHITE){
            visitSort(g, num, time);
        }
    }
    ++time;
    g.addTimeVertex(time, v);
    g.getVertex(v).setColor(BLACK);
}


map<int, int> dfsSort(Graph &g){
    int time = 0; 
    for (int i = 0; i < g.getCountVertex(); ++i){
        if (g.getVertex(i).getColor() == WHITE){
            visitSort(g, i, time);
	    }
    }
    return g.getTimeVertex();
}


void visitStrongComponents(Graph &g, int v, vector<list<int>> &strongComponents) {
    g.getVertex(v).setColor(GRAY);
    int lastComponent = strongComponents.size() - 1;
    strongComponents[lastComponent].push_back(v);
    for (auto neighbor: g[v]) {
        if (g.getVertex(neighbor).getColor() == WHITE) {
            visitStrongComponents(g, neighbor, strongComponents);
        }
    }
    g.getVertex(v).setColor(BLACK);
}

vector<list<int>> dfsStrongComponents(Graph rG,
    map<int, int> orderOfVisit) {
    vector<list<int>> strongComponents;
    for (auto elem = orderOfVisit.rbegin(); elem != orderOfVisit.rend(); ++elem) {
        if (rG.getVertex(elem->second).getColor() == WHITE) {
            strongComponents.push_back(list<int>());
            visitStrongComponents(rG, elem->second, strongComponents);
        }
    }
    return strongComponents;
}

int main(){
    int N, M;
    cin >> N >> M;
    Graph graph(N);
    graph.readData(M);

    Graph reverseGraph(graph.getReverseGraph());
    map<int, int> orderOfVisit(dfsSort(graph));
    
    vector<list<int>> strongComponents(dfsStrongComponents(reverseGraph, 
        orderOfVisit));
    for (int i = 0; i < strongComponents.size(); ++i) {
        cout << i + 1 << " - "; 
        for (auto v: strongComponents[i]) {
            cout << v + 1 << " "; 
        }
        cout << endl;
    }
}
