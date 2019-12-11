#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<int> prefixFunc(const string &input) {
    vector<int> prefix(input.size(), 0);
    int k;
    for (int i = 1; i < input.size(); ++i) {
        k = prefix[i - 1];
        while (k > 0 && input[i] != input[k]) {
            k = prefix[k - 1];
        }
        if (input[i] == input[k]) {
            ++k;
        }
        prefix[i] = k;
    }
    return prefix;
}

inline void merge(string &left, const string &right) {
    string tmp = left.substr(
        max(0, static_cast<int> (left.size() - right.size())));
    vector<int> prefix(prefixFunc(right + "*" + tmp));
    left += right.substr(prefix.back());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    string answer, nextWord;
    cin >> answer;

    for (int i = 1; i < n; ++i) {
        cin >> nextWord;
        merge(answer, nextWord);
    }
    cout << answer << endl;
}
