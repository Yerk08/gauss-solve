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
