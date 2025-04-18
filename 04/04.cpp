#include "../lib.hpp"

int main() {
    int start = 284639, end = 748759, result1 = 0, result2 = 0;
    for (int i = start; i <= end; i++) {
        bool inc = true, dbl = false, tpl = false;
        int mod = 100000, prev = -1, pprev = -1, ppprev = -1, num = i;
        for (int j = 0; j < 6; j++) {
            int dig = num / mod;
            if (dig < prev)
                inc = false;
            if (dig == prev)
                dbl = true;
            else if (prev != -1 && prev == pprev && pprev != ppprev)
                tpl = true;
            num -= dig * mod;
            mod /= 10;
            ppprev = pprev;
            pprev = prev;
            prev = dig;
        }
        if (prev == pprev && pprev != ppprev)
            tpl = true;
        if (inc && dbl)
            result1++;
        if (inc && tpl)
            result2++;
    }
    cout << result1 << ' ' << result2 << endl;
    return 0;
}
