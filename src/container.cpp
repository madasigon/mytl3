
#include "base.cpp"

#ifndef CONTAINER_CPP
#define CONTAINER_CPP

//STARTCOPY
namespace mytl{

template<typename T>
struct LazyVector : vector<T> {
	inline vector<T>::reference operator[](need_int i) {
		if (i >= vector<T>::size()) vector<T>::resize(i + 1);
		return vector<T>::operator[](i);
	}
};


template<typename T>
struct optional {
	T *ptr = nullptr;

	inline optional() {}
	inline optional(T val) {
		*ptr = val;
	}

	~optional() {
		if (ptr != nullptr) delete ptr;
	}
	inline T value() {
		return *ptr;
	}
	inline bool has_value() {
		return ptr != nullptr;
	}

	inline void set(T val) {
		ptr = new T;
		*ptr = val;
	}

};

}
//ENDCOPY

#endif