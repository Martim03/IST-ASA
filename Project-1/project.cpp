#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

map<vector<unsigned long long>, unsigned long long> memoization;
unsigned long long n, m, input;

unsigned long long calculate_high_square(unsigned long long row, vector<unsigned long long> stairs) {
    unsigned long long height = 0;
    for (unsigned long long i = row; i >= 0; i--) {
        if (stairs[i] == stairs[row]) {
            height++;
        } else {
            break;
        }
    }
    return min(stairs[row], height);
}

unsigned long long find_biggest_row(vector<unsigned long long> stairs) {
    unsigned long long biggestRow = 0;
    for (unsigned long long  i = 0; i < n; i++) {
        if (stairs[i] >= stairs[biggestRow]) {
            biggestRow = i;
        }
    }
    return biggestRow;
}

unsigned long long biggest_row_value(vector<unsigned long long> stairs) {
    unsigned long long biggestVal = 0;
    for (unsigned long long  i = 0; i < n; i++) {
        if (stairs[i] > biggestVal) {
            biggestVal = stairs[i];
        }
    }
    return biggestVal;
}

unsigned long long  zerovector(vector<unsigned long long> stairs) {
    for (unsigned long long  i = 0; i < n; i++) {
        if (stairs[i] != 0) {
            return 0;
        }
    }
    return 1;
}
unsigned long long terminalstairs(vector<unsigned long long> stairs) {
    if (biggest_row_value(stairs) <= 1) {
        return 1;
    }
    return 0;

}

unsigned long long recursive_algorithm(vector<unsigned long long> stairs) {
    if (memoization.find(stairs) != memoization.end()) {
        return memoization[stairs];
    }
    if (terminalstairs(stairs)) {
        memoization[stairs] = 1;
        return 1;
    }
    unsigned long long row = find_biggest_row(stairs);
    unsigned long long side = calculate_high_square(row, stairs);
    // for each square size
    for (unsigned long long i = side; i > 0; i--) {
        vector<unsigned long long> smallerStairs = stairs;
        // remove the square
        for (unsigned long long j = row; row - j < i; j--) {
            smallerStairs[j] -= i;
        }
        memoization[stairs] += recursive_algorithm(smallerStairs);
    }
    return memoization[stairs];
}

int main() {
	vector<unsigned long long> stairs;
	cin >> n >> m;
	for (unsigned long long i = 0; i < n; i++) {
		cin >> input;
		stairs.push_back(input);
	}
    if (n == 0 || m == 0 || zerovector(stairs)) {
        cout << 0 << endl;
        return 0;
    }
    cout << recursive_algorithm(stairs) << endl;
    return 0;
}

/////////////////////////////
/*
void truncatestairs(unsigned long long &n, unsigned long long &m, vector<unsigned long long> &stairs) {
    stairs.erase(remove(stairs.begin(), stairs.end(), 0), stairs.end());
    n = stairs.size();
}
*/