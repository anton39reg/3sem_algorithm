#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;

enum {MAX = 1 << 30};

inline void relax(vector<int> &minPath, set<pair<int, int>> &orderOfVisit, 
    int u, int v, int U, int D, int IJ, int f, int haveCommonLift,
        int haveLiftFromZeroFloor, 
        int haveLiftOnFinishFloor) {

        int w;
        if (v >= u) {
            w = U;
        }
        else {
            w = D;
        }
        int bestWay;
        if ((u != 0 || haveLiftFromZeroFloor) && 
            (v != f || haveLiftOnFinishFloor) && haveCommonLift) {
            bestWay = min(abs(u - v) * w, IJ);
        }
        else {
            bestWay = abs(u - v) * w;
        }
        if (minPath[v] > minPath[u] + bestWay) {
            orderOfVisit.erase({minPath[v], v});
            minPath[v] = minPath[u] + bestWay;
            orderOfVisit.insert({minPath[v], v});
        } 
    }

void dijkstra(vector<int> &minPath, vector<vector<int>> &vertex, 
    int s, int f, int U, int D, int IJ, int haveLiftFromZeroFloor,
    int haveLiftOnFinishFloor) {
    
    minPath[s] = 0;
    if (minPath[f] == MAX) {
        minPath[f] = f * U;
    }
    
    set<pair<int, int>> orderOfVisit;
    for (int i = 0; i < minPath.size(); ++i) {
        if (minPath[i] != MAX) {
            orderOfVisit.insert({minPath[i], i});
        }
    }
    
    pair<int, int> cur;
    while (!orderOfVisit.empty()) {
        cur = *orderOfVisit.begin();
        orderOfVisit.erase(orderOfVisit.begin());
        int haveCommonLift;
        for (int i = 0; i < vertex.size(); ++i) {
            if (find(vertex[i].begin(), vertex[i].end(), cur.second) != 
                vertex[i].end()) {
                haveCommonLift = 1;
            }
            else {
                haveCommonLift = 0;
            }
            for (auto v: vertex[i]) {
                relax(minPath, orderOfVisit, cur.second, v, U, D, IJ, f,
                    haveCommonLift, 
                    haveLiftFromZeroFloor, haveLiftOnFinishFloor);
            }
        }
        haveCommonLift = 0;
        relax(minPath, orderOfVisit, cur.second, f, U, D, IJ, f, haveCommonLift,
            haveLiftFromZeroFloor,
            haveLiftOnFinishFloor);
    }
    cout << minPath[f] << endl;

    //for (auto v: minPath) {
    //    cout << v.first + 1 << " --- " << v.second << endl;
    //}
}

int main() {
    int N, U, D, I, J, L;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> U >> D >> I >> J >> L;
    vector<int> minPath(1000000 + L, MAX);
    int count;
    vector<vector<int>> vertex(L);
    int haveLiftFromZeroFloor = 0;
    int haveLiftOnFinishFloor = 0;

    for (int i = 0; i < L; ++i) {
        cin >> count;
        vertex[i] = vector<int>(count);
        int floor;
        int tmp;
        for (int j = 0; j < count; ++j) {
            cin >> floor;
            --floor;
            if (floor == 0) {
                haveLiftFromZeroFloor = 1;
            }
            if (floor == N-1) {
                haveLiftOnFinishFloor = 1;
            }
            vertex[i][j] = floor;
            if (j == 0) {
                minPath[floor] = floor * U; 
                tmp = floor * U;
            }
            else {
                minPath[floor] = tmp + I + J;
            }
        }
    }
    dijkstra(minPath, vertex, 0, N - 1, U, D, I+J, haveLiftFromZeroFloor, haveLiftOnFinishFloor);
}
