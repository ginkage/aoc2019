#include "../lib.hpp"

int main() {
    string s;
    getline(cin, s);

    long offset = stol(s.substr(0, 7));
    long len = s.size() * 10000 - offset;
    string res = s.substr(offset % s.size());
    while (res.size() + s.size() < len)
        res += s;
    res += s.substr(0, len - res.size());

    for (int t = 0; t < 100; t++) {
        int total = 0;
        for (int i = res.size() - 1; i >= 0; i--) {
            total = (total + (res[i] - '0')) % 10;
            res[i] = total + '0';
        }
    }

    cout << res.substr(0, 8) << endl;

    return 0;
}

