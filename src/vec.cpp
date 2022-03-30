#include "vec.h"

template class vec<2, float>;
template class vec<3, float>;
template class vec<3, unsigned int>;
template class vec<4, float>;

// ----- DIM 2 -----
template <typename T>
vec<2,T>::vec() : x{}, y{} {}

template <typename T>
vec<2,T>::vec(T x_in, T y_in) : x{x_in}, y{y_in} {}

// access data
template <typename T>
T& vec<2,T>::operator[](const size_t i){ 
    assert(i < 2); 
    return (i <= 0) ? x : y; 
}

template <typename T>
const T& vec<2,T>::operator[](const size_t i) const { 
    assert(i < 2); 
    return (i <= 0) ? x : y; 
}

// ----- DIM 3 -----
template <typename T>
vec<3,T>::vec() : x{}, y{}, z{} {}

template <typename T>
vec<3,T>::vec(T x_in, T y_in, T z_in) : x{x_in}, y{y_in}, z{z_in} {}

// access data
template <typename T>
T& vec<3,T>::operator[](const size_t i){ 
    assert(i < 3); 
    return (i <= 0) ? x : ((i == 1) ? y : z);
}

template <typename T>
const T& vec<3,T>::operator[](const size_t i) const { 
    assert(i < 3); 
    return (i <= 0) ? x : ((i == 1) ? y : z);
}

// get magnitude of vector
template <typename T>
float vec<3,T>::magnitude() { 
    return std::sqrt( x * x + y * y + z * z); 
}

// get normalized vector
template <typename T>
vec<3,T>& vec<3,T>::normalize(T m) { 
    if (magnitude() != 0){ *this = (*this)*(m/magnitude()); }
    return *this;
}

// ----- DIM 4 -----
template <typename T>
vec<4,T>::vec() : x{}, y{}, z{}, w{} {}

template <typename T>
vec<4,T>::vec(T x_in, T y_in, T z_in, T w_in) :x{x_in}, y{y_in}, z{z_in}, w{w_in} {}

// access data
template <typename T>
T& vec<4,T>::operator[](const size_t i){ 
    assert(i < 4); 
    return (i <= 0) ? x : ((i == 1) ? y : ((i == 2) ? z : w));
}

template <typename T>
const T& vec<4,T>::operator[](const size_t i) const { 
    assert(i < 4); 
    return (i <= 0) ? x : ((i == 1) ? y : ((i == 2) ? z : w));
}

