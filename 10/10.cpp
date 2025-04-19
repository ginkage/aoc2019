#include "../lib.hpp"

vector<string> grid;
int m, n;

int main() {
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }
    m = grid.size();
    n = grid[0].size();

    vector<pair<int, int>> ast;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == '#')
                ast.emplace_back(i, j);

    int result = 0, ri = -1;
    for (int i = 0; i < ast.size(); i++) {
        set<pair<int, int>> dir;
        for (int j = 0; j < ast.size(); j++)
            if (i != j) {
                int di = ast[i].first - ast[j].first;
                int dj = ast[i].second - ast[j].second;
                int mm = max(abs(di), abs(dj));
                for (int k = 2; k <= mm; k++)
                    while (di % k == 0 && dj % k == 0) {
                        di /= k;
                        dj /= k;
                    }
                dir.emplace(di, dj);
            }
        if (result < dir.size()) {
            result = dir.size();
            ri = i;
        }
    }
    cout << result << endl;

    map<pair<double, double>, pair<int, int>> target;
    for (int j = 0; j < ast.size(); j++)
        if (j != ri) {
            int dx = ast[ri].first - ast[j].first;
            int dy = ast[j].second - ast[ri].second;
            double phi = atan2(dy, dx);
            double r = hypot(dy, dx);
            if (phi < 0) phi += 2 * M_PI;
            target[make_pair(phi, r)] = make_pair(ast[j].second, ast[j].first);
        }

    int i = 0;
    double prev = 10;
    map<pair<int, double>, pair<int, int>> sorted;
    for (auto &p : target) {
        if (p.first.first == prev)
            i++;
        else
            i = 0;
        sorted[make_pair(i, p.first.first)] = p.second;
        prev = p.first.first;
    }

    i = 0;
    for (auto &p : sorted) {
        i++;
        if (i == 200)
            cout << p.second.first * 100 + p.second.second << endl;
    }

    return 0;
}

