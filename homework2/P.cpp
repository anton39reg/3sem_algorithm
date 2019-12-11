#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> prefixFunc(string input) {
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

int main() {
    string input;
    cin >> input;

    vector<int> prefix(prefixFunc(input));
    
    for (int i = 0; i < prefix.size(); ++i) {
        cout << prefix[i] << " ";
    }
    cout << endl;
}
