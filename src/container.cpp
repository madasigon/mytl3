
#include "base.cpp"

#ifndef CONTAINER_CPP
#define CONTAINER_CPP

//STARTCOPY
namespace mytl{

template<typename T>
struct LazyVector : vector<T> {
	inline typename vector<T>::reference operator[](need_int i) {

		if (i >= vector<T>::size()) vector<T>::resize(i + 1);
		return vector<T>::operator[](i);
	}
};

template<typename T>
struct TwoWayLazyVector {
	LazyVector<T> negative, positive;
	inline typename vector<T>::reference operator[](need_int i) {
		if(i >= 0){
			return positive[i];
		}
		else {
			return negative[-i];
		}
	}
};


template<typename T>
struct optional {
	T *ptr = nullptr;

	inline void set(const T& val) {
		ptr = new T(val);
	}

	inline optional() {}
	inline optional(const T& val) {
		set(val);
	}

	optional& operator=(const T& val){
		set(val);
		return *this;
	}

	~optional() {
		delete ptr;
	}
	inline T value() const {
		return *ptr;
	}
	inline bool has_value() const {
		return ptr != nullptr;
	}

	

	optional& operator=(const optional& other) {
		if (other.has_value()) {
			set(other.value());
		}
		else {
			ptr = nullptr;
		}
		return *this;
	}
	optional(const optional& other) {
		operator=(other);
	}

	optional(optional&& other) {
		ptr = other.ptr;
		other.ptr = nullptr;
	}

	optional& operator=(optional&& other) {
		if (this != &other) {
			delete ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
			return *this;
		}
	}

};

}
//ENDCOPY

#endif