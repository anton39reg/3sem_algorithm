#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<char> constructionString(const vector<int> &prefix) {
    char curChar = 'a';
    vector<char> answer(prefix.size());
    if (!prefix.size()) {
        return answer;
    }
    answer[0] = 'a';
    for (int i = 1; i < prefix.size(); ++i) {
        if (prefix[i] == 0) {
            vector<bool> used(26, false);
            int k = prefix[i-1];
            while (k > 0) {
                used[answer[k]-'a'] = true;
                k = prefix[k-1];
            }
            char c = 'b';
            while (used[c - 'a']) {
                ++c;
            }
            answer[i] = c;
        }
        else {
            answer[i] = answer[prefix[i] - 1];
        }
    }
    return answer;
}

int main() {
    int n;
    cin >> n;

    vector<int> prefix(n);
    for (int i = 0; i < n; ++i) {
        cin >> prefix[i];
    }

    vector<char> answer(constructionString(prefix));

    for (auto c: answer) {
        cout << c;
    }
    cout << endl;
}
