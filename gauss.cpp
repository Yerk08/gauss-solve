#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXN = int(1e5) + 7;
const int INF = int(1e9) + 7;

template <typename T>
class OpNot {
public:
	bool operator!=(const T other) const {
		return !(static_cast<const T&>(*this) == other);
	}
	bool operator!=(const int other) const {
		return !(static_cast<const T&>(*this) == other);
	}
};

int gcd(int a, int b) {
	while (b > 0) {
		a %= b;
		swap(a, b);
	}
	return a;
}

class MyInt : public OpNot<MyInt> {
public:
	int n, m;
	MyInt() {}
	MyInt(int i) : n(i), m(1) {}
	MyInt(int i, int j) {
		if (j < 0) {
			i = -i;
			j = -j;
		} else if (j == 0) {
			throw runtime_error("Zero m part in n/m");
		}
		int c = gcd(abs(i), abs(j));
		n = i / c;
		m = j / c;
	}
	MyInt operator+(const MyInt other) const {
		return MyInt(n * other.m + other.n * m, m * other.m);
	}
	MyInt operator-() const {
		return MyInt(-n, m);
	}
	MyInt operator-(const MyInt other) const {
		return MyInt(n * other.m - other.n * m, m * other.m);
	}
	MyInt operator*(const MyInt other) const {
		return MyInt(n * other.n, m * other.m);
	}
	MyInt operator/(const MyInt other) const {
		return MyInt(n * other.m, m * other.n);
	}
	bool operator==(const MyInt other) const {
		return (n == other.n && m == other.m);
	}
	bool operator==(const int other) const {
		return (n == other && m == 1);
	}
};

istream& operator>>(istream& cin, MyInt& a) {
	a.m = 1;
	return cin >> a.n;
}

istream& operator>>(istream& cin, vector <vector <MyInt>>& a) {
	for (size_t i = 0; i < a.size(); ++i) {
		for (size_t j = 0; j < a[i].size(); ++j) {
			cin >> a[i][j];
		}
	}
	return cin;
}

ostream& operator<<(ostream& cout, MyInt a) {
	if (a.m == 1) {
		return cout << a.n;
	}
	return cout << a.n << "/" << a.m;
}

ostream& operator<<(ostream& cout, vector <vector <MyInt>>& a) {
	for (size_t i = 0; i < a.size(); ++i) {
		for (size_t j = 0; j < a[i].size(); ++j) {
			cout << a[i][j] << "\t";
		}
		cout << "\n";
	}
	return cout;
}

void first_operator(vector <vector <MyInt>>& mt, const size_t i, const size_t j) {
	swap(mt[i], mt[j]);
	cout << "-- swap (" << i + 1 << ") and (" << j + 1 << ") rows\n" << mt << "\n";
}

void second_operator(vector <vector <MyInt>>& mt, const size_t i, const MyInt a) {
	for (int j = 0; j < mt[i].size(); ++j) {
		mt[i][j] = mt[i][j] * a;
	}
	cout << "-- multiply row (" << i + 1 << ") by " << a << "\n" << mt << "\n";
}

void third_operator(vector <vector <MyInt>>& mt, const size_t i, const size_t j, const MyInt a) {
	if (i == j) throw runtime_error("Add two same rows");
	for (int k = 0; k < mt[i].size(); ++k) {
		mt[i][k] = mt[i][k] + mt[j][k] * a;
	}
	cout << "-- Add to row (" << i + 1 << ") row (" << j + 1 << ") mul. by " << a << "\n" << mt << "\n";
}

void gauss_method(vector <vector <MyInt>>& mt) {
	size_t cur_i = 0, cur_j = 0, cur_iterate = 0;
	while (cur_i < mt.size() && cur_j < mt.back().size()) {
		cout << "  <ITERATE " << (++cur_iterate) << ">  \n";
		if (mt[cur_i][cur_j] != 0) { // part 1
			for (size_t k = 0; k < mt.size(); ++k) {
				if (k != cur_i) {
					MyInt a = -mt[k][cur_j] / mt[cur_i][cur_j];
					if (a != 0) third_operator(mt, k, cur_i, a);
				}
			}
			MyInt a = MyInt(1) / mt[cur_i][cur_j];
			if (a != 1) second_operator(mt, cur_i, a);
			++cur_i;
			++cur_j;
		} else { // part 2
			bool found = false;
			for (size_t k = cur_i; k < mt.size(); ++k) {
				if (mt[k][cur_j] != 0) {
					found = true;
					first_operator(mt, cur_i, k);
					break;
				}
			}
			if (!found) { // part 3
				++cur_j;
			}
		}
	}
	cout << "  <FINISHED>  \n";
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	auto mt = vector <vector <MyInt>>(n, vector <MyInt>(m, 0));
	cin >> mt;
	gauss_method(mt);
}

