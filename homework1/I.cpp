#include <iostream>
#include <queue>
#include <map>

using namespace std;

int addFirst(int a) {
    if (a / 1000 != 9) {
        return a + 1000;
    }
    return a;
}

int subLast(int a) {
    if (a % 10 != 1) {
        return a - 1;
    }
    return a;
}

int shiftLeft(int a) {
    return (a % 1000) * 10 + (a / 1000);
}

int shiftRight(int a) {
    return (a % 10) * 1000 + (a / 10);
}


void printPath(int f, map<int, int> prev) {
    if (f != -1) {
        printPath(prev[f], prev);
        cout << f << endl;
    }
}

void bfs(int s, int f) {
    queue<int> orderOfVisit;
    map<int, bool> visited;
    map<int, int> prev;

    orderOfVisit.push(s);
    visited[s] = true;
    prev[s] = -1;

    int now;

    while (!orderOfVisit.empty()) {
        now = orderOfVisit.front();
        orderOfVisit.pop();
        int next[4] = { addFirst(now), subLast(now),
            shiftLeft(now), shiftRight(now) };
        for (int i = 0; i < 4; ++i) {
            if (visited[next[i]] == false) {
                orderOfVisit.push(next[i]);
                visited[next[i]] = true;
                prev[next[i]] = now;
            }
        }
        if (visited[f] == true) {
            break;
        }
    }
    printPath(f, prev);
}


int main() {
    int s, f;
    cin >> s >> f;

    bfs(s, f);
}
