#include <iostream>
#include <vector>

template <typename T>
class matrix {
private:
	std::vector <std::vector <T>> mt;
public:
	matrix() {}
	matrix(int n, int m) : mt(std::vector <std::vector <T>>(n, std::vector <T>(m, 0))) {}

	friend std::istream& operator>>(std::istream& cin, matrix<T>& a) {
		for (size_t i = 0; i < a.mt.size(); ++i) {
			for (size_t j = 0; j < a.mt[i].size(); ++j) {
				cin >> a.mt[i][j];
			}
		}
		return cin;
	}

	friend std::ostream& operator<<(std::ostream& cout, const matrix<T>& a) {
		for (size_t i = 0; i < a.mt.size(); ++i) {
			for (size_t j = 0; j < a.mt[i].size(); ++j) {
				cout << a.mt[i][j] << "\t";
			}
			cout << "\n";
		}
		return cout;
	}

	void first_operator(const size_t i, const size_t j, bool do_print = false) {
		swap(mt[i], mt[j]);
		std::cout << "-- swap (" << i + 1 << ") and (" << j + 1 << ") rows\n";
		if (do_print) std::cout << *this << "\n";
	}

	void second_operator(const size_t i, const T a, bool do_print = false) {
		for (int j = 0; j < mt[i].size(); ++j) {
			mt[i][j] = mt[i][j] * a;
		}
		std::cout << "-- multiply row (" << i + 1 << ") by " << a << "\n";
		if (do_print) std::cout << *this << "\n";
	}

	void third_operator(const size_t i, const size_t j, const T a, bool do_print = false) {
		if (i == j) throw std::runtime_error("Add two same rows");
		for (int k = 0; k < mt[i].size(); ++k) {
			mt[i][k] = mt[i][k] + mt[j][k] * a;
		}
		std::cout << "-- Add to row (" << i + 1 << ") row (" << j + 1 << ") mul. by " << a << "\n";
		if (do_print) std::cout << *this << "\n";
	}

	void gauss_method() {
		size_t cur_i = 0, cur_j = 0, cur_iterate = 0;
		while (cur_i < mt.size() && cur_j < mt.back().size()) {
			std::cout << "  <ITERATE " << (++cur_iterate) << ">  \n";
			if (mt[cur_i][cur_j] != 0) { // part 1
				for (size_t k = 0; k < mt.size(); ++k) {
					if (k != cur_i) {
						T a = -mt[k][cur_j] / mt[cur_i][cur_j];
						if (a != 0) third_operator(k, cur_i, a);
					}
				}
				T a = T(1) / mt[cur_i][cur_j];
				second_operator(cur_i, a, true);
				++cur_i;
				++cur_j;
			} else { // part 2
				bool found = false;
				for (size_t k = cur_i; k < mt.size(); ++k) {
					if (mt[k][cur_j] != 0) {
						found = true;
						first_operator(cur_i, k, true);
						break;
					}
				}
				if (!found) { // part 3
					++cur_j;
				}
			}
		}
		std::cout << "  <FINISHED>  \n";
	}
};
