#include "../lib.hpp"

vector<long> original;

long run(vector<long> input) {
    int in = 0;
    vector<long> program = original;
    for (int i = 0; i < program.size();) {
        long op = program[i++];
        int m1 = (op / 100) % 10;
        int m2 = (op / 1000) % 10;
        op %= 100;

        if (op == 1) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            program[arg3] = (m1 ? arg1 : program[arg1]) + (m2 ? arg2 : program[arg2]);
        }
        else if (op == 2) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            program[arg3] = (m1 ? arg1 : program[arg1]) * (m2 ? arg2 : program[arg2]);
        }
        else if (op == 3) {
            long arg = program[i++];
            program[arg] = input[in++];
        }
        else if (op == 4) {
            long arg = program[i++];
            return program[arg];
        }
        else if (op == 5) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            if (m1 ? arg1 : program[arg1])
                i = (m2 ? arg2 : program[arg2]);
        }
        else if (op == 6) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            if (!(m1 ? arg1 : program[arg1]))
                i = (m2 ? arg2 : program[arg2]);
        }
        else if (op == 7) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            program[arg3] = (m1 ? arg1 : program[arg1]) < (m2 ? arg2 : program[arg2]);
        }
        else if (op == 8) {
            long arg1 = program[i++];
            long arg2 = program[i++];
            long arg3 = program[i++];
            program[arg3] = (m1 ? arg1 : program[arg1]) == (m2 ? arg2 : program[arg2]);
        }
        else break;
    }
    return -1;
}

int main() {
    string s;
    getline(cin, s);
    original = split_l(s, ",");
    vector<long> ins(2);
    vector<long> set = { 0, 1, 2, 3, 4 };
    long result = 0;
    do {
        long out = 0;
        for (int j = 0; j < 5; j++) {
            ins[0] = set[j];
            ins[1] = out;
            out = run(ins);
        }

        if (result < out)
            result = out;
    }
    while (next_permutation(set.begin(), set.end()));
    cout << result << endl;
    return 0;
}
