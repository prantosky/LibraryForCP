#ifndef FAST_MEDIAN
#define FAST_MEDIAN 1

#include <set>

template <typename T>
class FastMedian {
 private:
	std::multiset<T> s1, s2;
	void balance_sets();

 public:
	FastMedian<T>() = default;
	~FastMedian<T>() = default;
	void insert_element(const T element);
	bool delete_element(const T& element);
	T get_median();
};

template <typename T>
void FastMedian<T>::balance_sets() {
	if (s2.size() > s1.size()) {
		s1.insert(*s2.begin());
		s2.erase(s2.begin());
	} else if (s1.size() > s2.size() + 1) {
		s2.insert(*s1.rbegin());
		s1.erase(--s1.end());
	}
}

template <typename T>
void FastMedian<T>::insert_element(const T element) {
	if (s1.empty()) {
		s1.insert(std::move(element));
	} else if (element > *s1.rbegin()) {
		s2.insert(std::move(element));
	} else {
		s1.insert(std::move(element));
	}
	balance_sets();
}

template <typename T>
bool FastMedian<T>::delete_element(const T& element) {
	auto it = s1.find(element);
	bool retVal = false;
	if (it != s1.end()) {
		s1.erase(it);
		retVal = true;
	} else {
		it = s2.find(element);
		if (it != s2.end()) {
			s2.erase(it);
			retVal = true;
		}
	}
	if (s1.size() + s2.size() == 0) return false;
	balance_sets();
	return retVal;
}

template <typename T>
T FastMedian<T>::get_median() {
	std::size_t size = s1.size() + s2.size();
	if (size == 0)
		throw "FastMedian:: Median cannot be found for zero elements";

	if ((size & 1) == 0) {
		return (*s1.rbegin() + *s2.begin()) / 2;
	}
	return *s1.rbegin();
}

#endif