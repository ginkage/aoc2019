#include "../lib.hpp"

typedef Eigen::Vector3i v3;

int sign(int a) {
    return (a < 0 ? -1 : (a > 0 ? 1 : 0));
}

v3 sign(v3 v) {
    return v3(sign(v[0]), sign(v[1]), sign(v[2]));
}

int main() {
    vector<v3> pos, vel;
    const regex linerex("<x=(.*), y=(.*), z=(.*)>");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 4) {
            pos.emplace_back(stoi(linematch[1].str()), stoi(linematch[2].str()), stoi(linematch[3].str()));
            vel.emplace_back(0, 0, 0);
        }
    }

    for (int t = 0; t < 1000; t++) {
        for (int i = 0; i < pos.size(); i++)
            for (int j = 0; j < pos.size(); j++)
                if (i != j) {
                    v3 &pi = pos[i], &pj = pos[j];
                    vel[i] += sign(pj - pi);
                }

        for (int i = 0; i < pos.size(); i++)
            pos[i] += vel[i];
    }

    long result = 0;
    for (int i = 0; i < pos.size(); i++) {
        long pot = abs(pos[i][0]) + abs(pos[i][1]) + abs(pos[i][2]);
        long kin = abs(vel[i][0]) + abs(vel[i][1]) + abs(vel[i][2]);
        result += pot * kin;
        //cout << pos[i][0] << ' ' << pos[i][1] << ' ' << pos[i][2] << ' ' << vel[i][0] << ' ' << vel[i][1] << ' ' << vel[i][2] << endl;
    }
    cout << result << endl;

    return 0;
}

