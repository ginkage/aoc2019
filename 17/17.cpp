#include "../lib.hpp"

struct state_t {
    unordered_map<long, long> program;
    queue<long> input;
    queue<long> output;
    long ip { 0 };
    long base { 0 };
    bool halt { false };

    long get(long arg, int mode) {
        if (mode == 1)
            return arg;
        return program[(mode == 0) ? arg : (base + arg)];
    }

    void put(long arg, int mode, long value) {
        program[(mode == 0) ? arg : (base + arg)] = value;
    }
};

void run(state_t &st) {
    unordered_map<long, long> &program = st.program;
    int i = st.ip;
    while (!st.halt) {
        long op = program[i++];
        int m1 = (op / 100) % 10;
        int m2 = (op / 1000) % 10;
        int m3 = (op / 10000) % 10;
        op %= 100;

        if (op == 1) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            st.put(arg3, m3, st.get(arg1, m1) + st.get(arg2, m2));
        }
        else if (op == 2) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            st.put(arg3, m3, st.get(arg1, m1) * st.get(arg2, m2));
        }
        else if (op == 3) {
            long arg1 = program[i++];
            if (st.input.empty()) break;
            st.put(arg1, m1, st.input.front());
            st.input.pop();
        }
        else if (op == 4) {
            long arg1 = program[i++];
            st.output.push(st.get(arg1, m1));
        }
        else if (op == 5) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            if (st.get(arg1, m1))
                i = st.get(arg2, m2);
        }
        else if (op == 6) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            if (!st.get(arg1, m1))
                i = st.get(arg2, m2);
        }
        else if (op == 7) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            st.put(arg3, m3, st.get(arg1, m1) < st.get(arg2, m2));
        }
        else if (op == 8) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            st.put(arg3, m3, st.get(arg1, m1) == st.get(arg2, m2));
        }
        else if (op == 9) {
            long arg1 = program[i++];
            st.base += st.get(arg1, m1);
        }
        else {
            st.halt = true;
            break;
        }
        st.ip = i;
    }
}

unordered_map<int, vec> delta = {
    { 1, { -1, 0 } },
    { 2, { 1, 0 } },
    { 3, { 0, -1 } },
    { 4, { 0, 1 } }
};

int left(int dir) {
    switch (dir) {
        case 1: dir = 3; break;
        case 2: dir = 4; break;
        case 3: dir = 2; break;
        case 4: dir = 1; break;
    }
    return dir;
}

int right(int dir) {
    switch (dir) {
        case 1: dir = 4; break;
        case 2: dir = 3; break;
        case 3: dir = 1; break;
        case 4: dir = 2; break;
    }
    return dir;
}

int main() {
    string s;
    getline(cin, s);
    state_t state;
    auto program = split_l(s, ",");

    for (int i = 0; i < program.size(); i++)
        state.program[i] = program[i];

    vector<string> grid;
    string cur;

    while (!state.halt) {
        run(state);

        while (!state.output.empty()) {
            int out = state.output.front();
            state.output.pop();
            if (out == 10 && cur.size() > 0) {
                grid.push_back(cur);
                cur = "";
            }
            else
                cur += char(out);
        }
    }

    unordered_map<vec, int, VHash> space;
    vec pos;
    int m = grid.size(), n = grid[0].size();
    long result = 0;
    for (int i = 1; i < m-1; i++)
        for (int j = 1; j < n-1; j++)
            if (grid[i][j] == '#' && grid[i-1][j] == '#' && grid[i+1][j] == '#'
                    && grid[i][j-1] == '#' && grid[i][j+1] == '#')
                result += i * j;
    cout << result << endl;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == '#')
                space[vec(i, j)] = 1;
            else if (grid[i][j] == '^')
                pos = vec(i, j);

    int dir = 1;
    while (true) {
        vec l = pos + delta[left(dir)];
        vec r = pos + delta[right(dir)];
        if (space[l] && !space[r]) {
            cout << "L,";
            dir = left(dir);
        }
        else if (space[r] && !space[l]) {
            cout << "R,";
            dir = right(dir);
        }
        else break;

        int dist = 0;
        vec d = delta[dir];
        while (space[pos + d]) {
            dist++;
            pos += d;
        }
        cout << dist << ",";
    }
    cout << endl;

    // R,12,L,10,R,12,
    // L,8,R,10,R,6,
    // R,12,L,10,R,12,
    // R,12,L,10,R,10,L,8,
    // L,8,R,10,R,6,
    // R,12,L,10,R,10,L,8,
    // L,8,R,10,R,6,
    // R,12,L,10,R,10,L,8,
    // R,12,L,10,R,12,
    // R,12,L,10,R,10,L,8
    string a = "R,12,L,10,R,12\n";
    string b = "L,8,R,10,R,6\n";
    string c = "R,12,L,10,R,10,L,8\n";
    string route = "A,B,A,C,B,C,B,C,A,C\n";

    state = state_t();
    for (int i = 0; i < program.size(); i++)
        state.program[i] = program[i];
    state.program[0] = 2;

    string input = route + a + b + c + "n\n";
    for (char c : input)
        state.input.push(c);

    while (!state.halt) {
        run(state);

        while (!state.output.empty()) {
            int out = state.output.front();
            state.output.pop();
            if (out < 128)
                cout << char(out);
            else
                cout << out << endl;
        }
    }

    return 0;
}

