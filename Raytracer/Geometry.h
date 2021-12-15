#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

//General template for the N-vector
template <size_t DIM, typename T> struct vec {
    vec() { for (size_t i = DIM; i--; data_[i] = T()); }                            //Pay attention - iterating through coords in the bottom-to-top convention
    T& operator[](const size_t i) { assert(i < DIM); return data_[i]; }             //Overloaded indexation operator []
    const T& operator[](const size_t i) const { assert(i < DIM); return data_[i]; } //Same overloaded operator, but const
private:
    T data_[DIM];          //the coord's array itself
};

//Name-mangling - defining special cases for the float/int 3- and 4- vectors
typedef vec<2, float> Vec2f;
typedef vec<3, float> Vec3f;
typedef vec<3, int  > Vec3i;
typedef vec<4, float> Vec4f;

//Template for the 2-vector
template <typename T> struct vec<2, T> {
    vec() : x(T()), y(T()) {}
    vec(T X, T Y) : x(X), y(Y) {}
    template <class U> vec<2, T>(const vec<2, U>& v);
    T& operator[](const size_t i) { assert(i < 2); return i <= 0 ? x : y; }
    const T& operator[](const size_t i) const { assert(i < 2); return i <= 0 ? x : y; }
    T x, y;
};

//Template for the 3-vector
template <typename T> struct vec<3, T> {
    vec() : x(T()), y(T()), z(T()) {}
    vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
    T& operator[](const size_t i) { assert(i < 3); return i <= 0 ? x : (1 == i ? y : z); }
    const T& operator[](const size_t i) const { assert(i < 3); return i <= 0 ? x : (1 == i ? y : z); }
    float norm() { return std::sqrt(x * x + y * y + z * z); }                                           //defining the norm of a vector
    vec<3, T>& normalize(T l = 1) { *this = (*this) * (l / norm()); return *this; }                     //vector normalization
    T x, y, z;
};

//Template for the 4-vector
template <typename T> struct vec<4, T> {
    vec() : x(T()), y(T()), z(T()), w(T()) {}
    vec(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}
    T& operator[](const size_t i) { assert(i < 4); return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w)); }
    const T& operator[](const size_t i) const { assert(i < 4); return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w)); }
    T x, y, z, w;
};

//vector dot product
template<size_t DIM, typename T> T operator*(const vec<DIM, T>& lhs, const vec<DIM, T>& rhs) {
    T ret = T();
    for (size_t i = DIM; i--; ret += lhs[i] * rhs[i]);
    return ret;
}

//vector-vector addition
template<size_t DIM, typename T>vec<DIM, T> operator+(vec<DIM, T> lhs, const vec<DIM, T>& rhs) {
    for (size_t i = DIM; i--; lhs[i] += rhs[i]);
    return lhs;
}

//vector-vector substraction
template<size_t DIM, typename T>vec<DIM, T> operator-(vec<DIM, T> lhs, const vec<DIM, T>& rhs) {
    for (size_t i = DIM; i--; lhs[i] -= rhs[i]);
    return lhs;
}

//vector scaling (multiplication by a constant)
template<size_t DIM, typename T, typename U> vec<DIM, T> operator*(const vec<DIM, T>& lhs, const U& rhs) {
    vec<DIM, T> ret;
    for (size_t i = DIM; i--; ret[i] = lhs[i] * rhs);
    return ret;
}

//vector-scalar substraction
template<size_t DIM, typename T> vec<DIM, T> operator-(const vec<DIM, T>& lhs) {
    return lhs * T(-1);
}

//vector cross product
template <typename T> vec<3, T> cross(vec<3, T> v1, vec<3, T> v2) {
    return vec<3, T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

//vector output 
template <size_t DIM, typename T> std::ostream& operator<<(std::ostream& out, const vec<DIM, T>& v) {
    for (unsigned int i = 0; i < DIM; i++) {
        out << v[i] << " ";
    }
    return out;
}
#endif //__GEOMETRY_H__