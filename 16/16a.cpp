#include "../lib.hpp"

int main() {
    string s;
    getline(cin, s);
    int base[4] = { 0, 1, 0, -1 };

    for (int t = 0; t < 100; t++) {
        string next(s.size(), '0');
        for (int i = 0; i < s.size(); i++) {
            int res = 0;
            for (int j = 0; j < s.size(); j++)
                res += (s[j] - '0') * base[((j + 1) / (i + 1)) % 4];

            if (res < 0) res = -res;
            next[i] = '0' + (res % 10);
        }
        s = next;
    }
    cout << s.substr(0, 8) << endl;

    return 0;
}

