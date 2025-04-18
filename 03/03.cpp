#include "../lib.hpp"

vector<vec> parse() {
    string s;
    getline(cin, s);
    vector<vec> result;
    vec pos(0, 0);
    result.push_back(pos);
    for (auto dir : split_s(s, ",")) {
        int len = stoi(dir.substr(1));
        if (dir[0] == 'U')
            pos[1] -= len;
        else if (dir[0] == 'L')
            pos[0] -= len;
        else if (dir[0] == 'R')
            pos[0] += len;
        else if (dir[0] == 'D')
            pos[1] += len;
        result.push_back(pos);
    }
    return result;
}

int main() {
    vector<vec> first = parse();
    vector<vec> second = parse();
    int result1 = -1, result2 = -1;
    int steps1 = 0;
    for (int i = 1; i < first.size(); i++) {
        vec p1 = first[i-1], p2 = first[i];
        vec mn1(min(p1[0], p2[0]), min(p1[1], p2[1]));
        vec mx1(max(p1[0], p2[0]), max(p1[1], p2[1]));
        int s1 = mx1[0] - mn1[0] + mx1[1] - mn1[1];
        if (i > 1) {
            int steps2 = 0;
            for (int j = 1; j < second.size(); j++) {
                vec q1 = second[j-1], q2 = second[j];
                vec mn2(min(q1[0], q2[0]), min(q1[1], q2[1]));
                vec mx2(max(q1[0], q2[0]), max(q1[1], q2[1]));
                int s2 = mx2[0] - mn2[0] + mx2[1] - mn2[1];
                if (j > 1) {
                    if (mn1[0] == mx1[0] && mn2[1] == mx2[1]) {
                        int x = mn1[0], y = mn2[1];
                        if (x >= mn2[0] && x <= mx2[0] && y >= mn1[1] && y <= mx1[1]) {
                            int dist = abs(x) + abs(y);
                            if (result1 < 0 || result1 > dist)
                                result1 = dist;
                            int steps = steps1 + steps2 + abs(x - q1[0]) + abs(y - p1[1]);
                            if (result2 < 0 || result2 > steps)
                                result2 = steps;
                        }
                    }
                    else if (mn1[1] == mx1[1] && mn2[0] == mx2[0]) {
                        int x = mn2[0], y = mn1[1];
                        if (x >= mn1[0] && x <= mx1[0] && y >= mn2[1] && y <= mx2[1]) {
                            int dist = abs(x) + abs(y);
                            if (result1 < 0 || result1 > dist)
                                result1 = dist;
                            int steps = steps1 + steps2 + abs(x - p1[0]) + abs(y - q1[1]);
                            if (result2 < 0 || result2 > steps)
                                result2 = steps;
                        }
                    }
                }
                steps2 += s2;
            }
        }
        steps1 += s1;
    }
    cout << result1 << ' ' << result2 << endl;

    return 0;
}
