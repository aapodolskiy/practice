#include <cstdio>
#include <iostream>
#include <fstream>

#include <string>
#include <cstring>

#include <vector>
#include <deque>
#include <queue>
#include <tuple>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <cmath>
#include <functional>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

#ifdef LOCAL_TEST_ENVIRONMENT
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

int lengthOfNumber(int x) {
    int l = 0;
    for (; x > 0; x /= 10) {
        l++;
    }
    return l;
}

int sumOfDigits(int x) {
    int s = 0;
    for (; x > 0; x /= 10) {
        s += x % 10;
    }
    return s;
}

int sumOfLastDigits(int x, int digits) {
    int s = 0;
    for (; digits > 0; x /= 10) {
        s += x % 10;
        digits--;
    }
    return s;
}

int sumOfFirstDigits(int x, int digits) {
    return sumOfDigits(x) - sumOfLastDigits(x, lengthOfNumber(x) - digits);
}

ull binomialCoef2(int x) {
    ull b = x;
    b *= (x-1);
    b /= 2;
    return b;
}

int main() {
    int n;
    cin >> n;

    ull result = 0;
    
    vector<vector<int>> s(6);

    int sums[6][46];
    for (int d = 0; d <= 5; d++) {
        for (int i = 0; i < 46; i++) {
            sums[d][i] = 0;
        }
    }

    int tmp = 0, length = 0, tmpSumOfDigits = 0;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        length = lengthOfNumber(tmp);
        s[length].push_back(tmp);
        sums[length][sumOfDigits(tmp)]++;
    }
    

    // self-pairs
    for (int d = 1; d <= 5; d++) {
        // cout << "sums for digit " << d << ":" << endl;
        for (int i = 0; i < 46; i++) {
            if (sums[d][i] == 0) {
                continue;
            }
            result += static_cast<ull>(sums[d][i]) * static_cast<ull>(sums[d][i]);//+ binomialCoef2(sums[d][i]);
            // cout << sums[d][i] << " with sum " << i << ", ";
        }
        // cout << endl << endl;
    }

    // presums and postsums
    for (int D = 3; D <= 5; D++) {
        for (int d = D-2; d >= 1; d -= 2) {
            int digitsToRemove = (D - d)/2;
            int presums[46];
            for (int i = 0; i < 46; i++) {
                presums[i] = 0;
            }
            int postsums[46];
            for (int i = 0; i < 46; i++) {
                postsums[i] = 0;
            }
            for (int num : s[D]) {
                int fullSum = sumOfDigits(num);
                int presum = sumOfFirstDigits(num, D - digitsToRemove)
                    - sumOfLastDigits(num, digitsToRemove);
                int postSum = sumOfLastDigits(num, D - digitsToRemove)
                    - sumOfFirstDigits(num, digitsToRemove);
                if (presum >= 0) {
                    presums[presum]++;
                }
                if (postSum >= 0) {
                    postsums[postSum]++;
                }
            }
            // cout << endl << "pre and post sums for digit " << D << " ("<<d<<"): " << endl;
            // for (int i = 0; i < 46; i++) {
            //     if (presums[i] > 0) {
            //         cout << "presum " << i << " " << presums[i] << " times, ";
            //     }
            //     if (postsums[i] > 0) {
            //         cout << "postsum " << i << " " << postsums[i] << " times, ";
            //     }
            // }
            // cout << endl;
            for (int i = 0; i < 46; i++) {
                result += static_cast<ull>(sums[d][i]) * static_cast<ull>(presums[i]);
                result += static_cast<ull>(sums[d][i]) * static_cast<ull>(postsums[i]);
            }
            // cout << "after "<<D<<"("<<d<<") result is " << result << endl;
        }
    }

    cout << result << endl;
 
    return 0;
}