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

bool check(vector<long> &program, long i, long j) {
    state_t state;
    for (int t = 0; t < program.size(); t++)
        state.program[t] = program[t];
    state.input.push(j);
    state.input.push(i);
    run(state);
    return state.output.front();
}

int main() {
    string s;
    getline(cin, s);
    auto program = split_l(s, ",");
    int lower = 0, upper = 10000, best = upper;
    while (lower <= upper) {
        int mid = (lower + upper) / 2;
        bool good = false;
        for (int i = 0; i <= mid && !good; i++) {
            int j = mid - i;
            if (check(program, i, j) && check(program, i + 99, j) && check(program, i, j + 99)) {
                good = true;
                best = min(best, mid);
            }
        }

        if (good)
            upper = mid - 1;
        else
            lower = mid + 1;
    }

    for (int mid = best; mid >= best - 10; mid--) {
        bool good = false;
        for (int i = 0; i <= mid && !good; i++) {
            int j = mid - i;
            if (check(program, i, j) && check(program, i + 99, j) && check(program, i, j + 99)) {
                good = true;
                cout << mid << ' ' << (j * 10000 + i) << endl;
            }
        }
    }

    return 0;
}

