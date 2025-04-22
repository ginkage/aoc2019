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
    for (int t = 0; t < 1000 && !st.halt; t++) { // while (!st.halt) {
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
            if (!st.input.empty()) {
                st.put(arg1, m1, st.input.front());
                st.input.pop();
            }
            else //break;
                st.put(arg1, m1, -1);
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

int main() {
    ifstream fin("input.txt");
    string s;
    getline(fin, s);
    auto program = split_l(s, ",");

    vector<state_t> computer(50);
    for (int i = 0; i < computer.size(); i++) {
        for (int t = 0; t < program.size(); t++)
            computer[i].program[t] = program[t];
        computer[i].input.push(i);
    }

    long last_y = -1;
    for (int q = 0; q < 10000; q++) {
        long nat_x = -1, nat_y = -1;
        for (int t = 0; t < 10; t++) {
            for (int i = 0; i < computer.size(); i++) {
                run(computer[i]);

                while (!computer[i].output.empty()) {
                    long addr = computer[i].output.front();
                    computer[i].output.pop();
                    long x = computer[i].output.front();
                    computer[i].output.pop();
                    long y = computer[i].output.front();
                    computer[i].output.pop();

                    if (addr != 255) {
                        computer[addr].input.push(x);
                        computer[addr].input.push(y);
                    }
                    else {
                        nat_x = x;
                        nat_y = y;
                    }
                }
            }
        }

        computer[0].input.push(nat_x);
        computer[0].input.push(nat_y);

        if (last_y == nat_y) {
            cout << nat_y << endl;
            break;
        }
        last_y = nat_y;
    }

    return 0;
}

