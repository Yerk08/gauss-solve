#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include "myint.h"
#include "matrix.cpp"
using namespace std;
using ll = long long;

const int MAXN = int(1e5) + 7;
const int INF = int(1e9) + 7;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	matrix<MyInt> mt(n, m);
	cin >> mt;
	mt.gauss_method();
}

