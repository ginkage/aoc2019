#include "../lib.hpp"

int main() {
    int result1 = 0, result2 = 0;
    while (true) {
        int mod;
        cin >> mod;
        if (!cin) break;
        mod = mod / 3 - 2;
        result1 += mod;
        do {
            result2 += mod;
            mod = mod / 3 - 2;
        } while (mod > 0);
    }
    cout << result1 << ' ' << result2 << endl;
    return 0;
}

