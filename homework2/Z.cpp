#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

string strByZFunc(const vector<int> &resZFunc) {
    if (resZFunc.size() == 0) {
        return "";
    }
    string answer = "a";
    list<int> posBadChar;
    bool appendAfterBlock = true;

    int curPos = 1;
    while (curPos < resZFunc.size()) {
        if (resZFunc[curPos] != 0) {
            posBadChar.clear();
            int prefixPos = 0;
            int remainingBlockLen = resZFunc[curPos];
            while (remainingBlockLen > 0) {
                if (resZFunc[curPos] > remainingBlockLen) {
                    remainingBlockLen = resZFunc[curPos];
                    posBadChar.push_back(resZFunc[curPos]);
                    prefixPos = 0;
                }
                else if (resZFunc[curPos] == remainingBlockLen) {
                   posBadChar.push_back(resZFunc[curPos]); 
                }

                answer += answer[prefixPos];

                ++prefixPos;
                ++curPos;
                --remainingBlockLen;
            }
            appendAfterBlock = true;
        }
        else {
            if (appendAfterBlock) {
                vector<bool> usedChar(26, false);
                for (auto pos: posBadChar) {
                    usedChar[answer[pos] - 'a'] = true;
                }

                char newChar = 'b';
                while (usedChar[newChar - 'a']) {
                    ++newChar;
                }
                answer += newChar;

                appendAfterBlock = false;
            }
            else {
                answer += "b";
            }

            ++curPos;
        }
    }
    return answer;
}

int main() {
    int n;
    cin >> n;

    vector<int> zFunc(n);
    for (int i = 0; i < n; ++i) {
        cin >> zFunc[i];
    }

    string answer(strByZFunc(zFunc));
    cout << answer;
}
