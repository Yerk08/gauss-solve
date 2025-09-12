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
private:
	int n, m;
public:
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

	friend istream& operator>>(istream& cin, MyInt& a) {
		a.m = 1;
		return cin >> a.n;
	}

	friend ostream& operator<<(ostream& cout, const MyInt a) {
		if (a.m == 1) {
			return cout << a.n;
		}
		return cout << a.n << "/" << a.m;
	}
};


template <typename T>
class matrix {
private:
	vector <vector <T>> mt;
public:
	matrix() {}
	matrix(int n, int m) : mt(vector <vector <T>>(n, vector <T>(m, 0))) {}
	
	friend istream& operator>>(istream& cin, matrix<T>& a) {
		for (size_t i = 0; i < a.mt.size(); ++i) {
			for (size_t j = 0; j < a.mt[i].size(); ++j) {
				cin >> a.mt[i][j];
			}
		}
		return cin;
	}
	
	friend ostream& operator<<(ostream& cout, const matrix<T>& a) {
		for (size_t i = 0; i < a.mt.size(); ++i) {
			for (size_t j = 0; j < a.mt[i].size(); ++j) {
				cout << a.mt[i][j] << "\t";
			}
			cout << "\n";
		}
		return cout;
	}

	void first_operator(const size_t i, const size_t j) {
		swap(mt[i], mt[j]);
		cout << "-- swap (" << i + 1 << ") and (" << j + 1 << ") rows\n" << *this << "\n";
	}

	void second_operator(const size_t i, const T a) {
		for (int j = 0; j < mt[i].size(); ++j) {
			mt[i][j] = mt[i][j] * a;
		}
		cout << "-- multiply row (" << i + 1 << ") by " << a << "\n" << *this << "\n";
	}

	void third_operator(const size_t i, const size_t j, const T a) {
		if (i == j) throw runtime_error("Add two same rows");
		for (int k = 0; k < mt[i].size(); ++k) {
			mt[i][k] = mt[i][k] + mt[j][k] * a;
		}
		cout << "-- Add to row (" << i + 1 << ") row (" << j + 1 << ") mul. by " << a << "\n" << *this << "\n";
	}

	void gauss_method() {
		size_t cur_i = 0, cur_j = 0, cur_iterate = 0;
		while (cur_i < mt.size() && cur_j < mt.back().size()) {
			cout << "  <ITERATE " << (++cur_iterate) << ">  \n";
			if (mt[cur_i][cur_j] != 0) { // part 1
				for (size_t k = 0; k < mt.size(); ++k) {
					if (k != cur_i) {
						T a = -mt[k][cur_j] / mt[cur_i][cur_j];
						if (a != 0) third_operator(k, cur_i, a);
					}
				}
				T a = T(1) / mt[cur_i][cur_j];
				if (a != 1) second_operator(cur_i, a);
				++cur_i;
				++cur_j;
			} else { // part 2
				bool found = false;
				for (size_t k = cur_i; k < mt.size(); ++k) {
					if (mt[k][cur_j] != 0) {
						found = true;
						first_operator(cur_i, k);
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
};

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

