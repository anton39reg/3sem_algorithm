#include <iostream>
#include <vector>
#include <string>
#include <list>

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

bool findEntry(string input, string substr) {
    string tmpStr = substr + "*" + input;
    vector<int> prefix(prefixFunc(tmpStr));
    list<int> position;
    for (int i = 0; i < prefix.size(); ++i) {
        if (prefix[i] == substr.size()) {
            position.push_back(i - 2 * substr.size());    
        }
    } 
    return position.size();
}

int main() {
    int n;
    cin >> n;

    string firstCondition, secondCondition;
    cin >> firstCondition >> secondCondition;

    string secondConditionOne = secondCondition + "1";
    string secondConditionZero = secondCondition + "0";
    
    secondConditionOne += secondConditionOne;
    secondConditionZero += secondConditionZero;

    bool resZero = findEntry(secondConditionZero, firstCondition);
    bool resOne = findEntry(secondConditionOne, firstCondition);
    
    if (resZero && resOne) {
        cout << "Random" << endl;
    }
    else if (resOne) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}
