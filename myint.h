#include <iostream>
#include "helpful.cpp"

class MyInt : public OpNot<MyInt> {
private:
	int n, m;
public:
	MyInt();
	MyInt(int i);
	MyInt(int i, int j);
	MyInt operator+(const MyInt other) const;
	MyInt operator-() const;
	MyInt operator-(const MyInt other) const;
	MyInt operator*(const MyInt other) const;
	MyInt operator/(const MyInt other) const;
	bool operator==(const MyInt other) const;
	bool operator==(const int other) const;

	friend std::istream& operator>>(std::istream& cin, MyInt& a);
	friend std::ostream& operator<<(std::ostream& cout, const MyInt a);
};
