#include "../lib.hpp"

long modpow(__int128 base, long exp, long mod) {
    base %= mod;
    long result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    long n = 119315717514047l;
    long t = 101741582076661l;

    const regex cutrex("cut (.*)");
    const regex dealrex("deal with increment (.*)");
    const string deal = "deal into new stack";

    __int128 c = 1, d = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, cutrex) && linematch.size() == 2) {
            long cut = stol(linematch[1].str());
            if (cut < 0) cut += n;
            d = (d + n - cut) % n;
        }
        else if (regex_match(s, linematch, dealrex) && linematch.size() == 2) {
            long inc = stol(linematch[1].str());
            c = (c * inc) % n;
            d = (d * inc) % n;
        }
        else if (s == deal) {
            c *= -1;
            d = n - 1 - d;
        }
    }

    __int128 a = modpow(c, n - 2, n);
    __int128 b = ((n - d) * modpow(c, n - 2, n)) % n;
    __int128 p1 = modpow(a, t, n);
    __int128 p2 = ((p1 - 1) * modpow(a - 1, n - 2, n)) % n;
    long target = ((p1 * 2020) + (b * p2)) % n;
    cout << target << endl;

    return 0;
}

