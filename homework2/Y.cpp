#include <iostream>
#include <vector> 
#include <string>
#include <list>

using namespace std;


vector<int> zFunc(const string &input) {
    vector<int> answer(input.length(), 0);
    answer[0] = input.length();
    int left = 0;
    int right = 0;
    int len = input.length();
    for (int i = 1; i < len; ++i) {
        answer[i] = max(0, min(right - i, answer[i - left]));
        while (i + answer[i] < len && 
            input[answer[i]] == input[i + answer[i]]) {
            ++answer[i];
        }
        if (i + answer[i] > right) {
            left = i;
            right = i + answer[i];
        }
    }
    return answer;
}

int main() {
    string wordOnFence, jackWord;
    cin >> wordOnFence >> jackWord;
    
    string forFindSubstr = wordOnFence + "#" + jackWord;
    vector<int> resZFunc(zFunc(forFindSubstr)); 
    
    size_t curPos = wordOnFence.length() + 1;
    size_t resLen = 0;
    list<string> answer;
    size_t lenNewStr = forFindSubstr.length();
    while (curPos < lenNewStr) {
        if (resZFunc[curPos] == 0) {
            break;
        }
        int tmp = resZFunc[curPos];
        string word = "";
        //cout << curPos - wordOnFence.length() - 1 << " " << resZFunc[curPos] << endl;
        do {
           word += forFindSubstr[curPos];
           ++curPos;
           ++resLen;
           --tmp;

        } while (tmp > 0 && tmp > resZFunc[curPos]);
        
        answer.push_back(word);
    }
    if (resLen == jackWord.length()) {
        cout << "No" << endl;
        for (auto str: answer) {
            cout << str << " ";
        }
    }
    else {
        cout << "Yes";
    }
}
