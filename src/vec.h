#ifndef VEC_H
#define VEC_H

#include <cassert>
#include <cmath>
#include <iosfwd>

template <size_t DIM, typename T>
class vec {
    private:
        T _data[DIM];
    public:
        // constructors
        vec() { for(size_t i{}; i < DIM; ++i){ _data[i] = T(); }}
        vec(const vec& copy) { for(size_t i{}; i < DIM; ++i){ _data[i] = copy._data[i]; }}
        // access data
        T& operator[](const size_t i){ assert(i < DIM); return _data[i]; }
        const T& operator[](const size_t i) const { assert(i < DIM); return _data[i]; }
        vec& operator= (const vec& copy) {
            for(size_t i{}; i < DIM; ++i){ _data[i] = copy._data[i]; } return *this;
        }
};

typedef vec<3, unsigned int> color;
typedef vec<2, float> Vec2f;
typedef vec<3, float> Vec3f;
typedef vec<4, float> Vec4f;

template <typename T> 
class vec<2,T> {
    private:
        T x, y;
    public:
        // constructors
        vec();
        vec(T x_in, T y_in);
        vec(const vec<2,T>& copy);
        
        // access data
        T& operator[](const size_t i);
        const T& operator[](const size_t i) const;
        vec<2,T>& operator= (const vec<2,T>& copy);
};

template <typename T> 
class vec<3,T> {
    private:
        T x, y, z;
    public:
        // constructors
        vec();
        vec(T x_in, T y_in, T z_in);
        vec(const vec<3,T>& copy);

        // access data
        T& operator[](const size_t i);
        const T& operator[](const size_t i) const;
        vec<3,T>& operator= (const vec<3,T>& copy);

        // get magnitude of vector
        float magnitude();

        // get normalized vector
        vec<3,T>& normalize(T m = 1);
};

template <typename T> 
class vec<4,T> {
    private:
        T x, y, z, w;
    public:
        // constructors
        vec();
        vec(T x_in, T y_in, T z_in, T w_in);
        vec(const vec<4,T>& copy);

        // access data
        T& operator[](const size_t i);
        const T& operator[](const size_t i) const;
        vec<4,T>& operator= (const vec<4,T>& copy);
};

// ----- Overloaded Operators -----

// Cross product of two vectors w/ dimension 3
template <typename T>
vec<3, T> cross(const vec<3, T>& q, const vec<3, T>& r) {
    return vec<3, T>(q[1] * r[2] - q[2] * r[1], 
                     q[2] * r[0] - q[0] * r[2], 
                     q[0] * r[1] - q[1] * r[0]);
}

// Dot product of two vectors
template<size_t DIM, typename T> 
T operator*(const vec<DIM, T>& q, const vec<DIM, T>& r){
    T res{};
    for (size_t i{}; i < DIM; ++i) { res += q[i] * r[i]; }
    return res;
}

// Add two vectors element-wise, return a new vector
template<size_t DIM, typename T> 
vec<DIM, T> operator+(const vec<DIM, T>& q, const vec<DIM, T>& r){
    vec<DIM, T> res;
    for (size_t i{}; i < DIM; ++i) { res[i] = q[i] + r[i]; }
    return res;
}

// Subract 2nd vector from 1st vector element-wise, return a new vector
template<size_t DIM,typename T> 
vec<DIM, T> operator-(const vec<DIM, T>& q, const vec<DIM, T>& r){
    vec<DIM, T> res;
    for (size_t i{}; i < DIM; ++i) { res[i] = q[i] - r[i]; }
    return res;
}

// Multiply vector by a scalar
template<size_t DIM, typename T, typename U> 
vec<DIM, T> operator*(const vec<DIM, T>& q, const U& r){
    vec<DIM, T> res;
    for (size_t i{}; i < DIM; ++i) { res[i] = q[i] * r; }
    return res;
}

// Invert vector
template<size_t DIM,typename T> 
vec<DIM,T> operator-(const vec<DIM, T>& q){
    vec<DIM, T> res = q * T(-1);
    return res;
}

// Equals operator
template<size_t DIM,typename T> 
bool operator==(const vec<DIM, T>& l, const vec<DIM, T>& r){
    bool isEqual {true};
    for(size_t i{}; i < DIM; ++i){ if (l[i] != r[i]) { isEqual = false; break; }}
    return isEqual;
}

// Not equals operator
template<size_t DIM,typename T> 
bool operator!=(const vec<DIM, T>& l, const vec<DIM, T>& r){ return !(l == r); }

// Print contents
template<size_t DIM,typename T>
std::ostream& operator<< (std::ostream& out, const vec<DIM,T>& v) {
    for(size_t i{}; i<DIM; i++) { out << v[i] << ' '; }
    return out;
}

#endif