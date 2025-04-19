#include "../lib.hpp"

int main() {
    unordered_map<int, int> parent;
    const regex linerex("(.*)\\)(.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            int id1 = remap(linematch[1].str());
            int id2 = remap(linematch[2].str());
            parent[id2] = id1;
        }
    }

    int result = 0;
    for (auto &p : parent) {
        int id2 = p.first;
        int id1 = p.second;
        result++;
        for (auto it = parent.find(id1); it != parent.end(); it = parent.find(it->second))
            result++;
    }
    cout << result << endl;

    unordered_map<int, int> dy;
    int dist = 0;
    for (auto it = parent.find(remap("YOU")); it != parent.end(); it = parent.find(it->second))
        dy[it->second] = dist++;

    dist = 0;
    for (auto it = parent.find(remap("SAN")); it != parent.end(); it = parent.find(it->second)) {
        auto jt = dy.find(it->second);
        if (jt != dy.end()) {
            cout << dist + jt->second << endl;
            break;
        }
        dist++;
    }

    return 0;
}

