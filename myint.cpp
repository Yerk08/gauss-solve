#include <iostream>
#include "myint.h"

int gcd(int a, int b) {
	while (b > 0) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

MyInt::MyInt() {}
MyInt::MyInt(int i) : n(i), m(1) {}
MyInt::MyInt(int i, int j) {
    if (j < 0) {
        i = -i;
        j = -j;
    } else if (j == 0) {
        throw std::runtime_error("Zero m part in n/m");
    }
    int c = gcd(abs(i), abs(j));
    n = i / c;
    m = j / c;
}
MyInt MyInt::operator+(const MyInt other) const {
    return MyInt(n * other.m + other.n * m, m * other.m);
}
MyInt MyInt::operator-() const {
    return MyInt(-n, m);
}
MyInt MyInt::operator-(const MyInt other) const {
    return MyInt(n * other.m - other.n * m, m * other.m);
}
MyInt MyInt::operator*(const MyInt other) const {
    return MyInt(n * other.n, m * other.m);
}
MyInt MyInt::operator/(const MyInt other) const {
    return MyInt(n * other.m, m * other.n);
}
bool MyInt::operator==(const MyInt other) const {
    return (n == other.n && m == other.m);
}
bool MyInt::operator==(const int other) const {
    return (n == other && m == 1);
}

std::istream& operator>>(std::istream& cin, MyInt& a) {
    a.m = 1;
    return cin >> a.n;
}

std::ostream& operator<<(std::ostream& cout, const MyInt a) {
    if (a.m == 1) {
        return cout << a.n;
    }
    return cout << a.n << "/" << a.m;
}
