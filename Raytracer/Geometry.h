#ifndef _GEOMETRY_H_
#define _GEOMETRY_H

#include<cmath>
#include<iostream>
#include<cassert>

//template for the structure of an N-dimensional vector
template <size_t DIM> struct vec {
	float data[DIM] = {};																//an array of coordinates
	
	float& operator[] (const size_t i) { assert(i < DIM); return data[i]; }			//overloaded indexation operator
	const float& operator[] (const size_t i) { assert(i < DIM); return data[i]; }	//same operator, but const
};

//template for the vector scaling
template <size_t DIM> vec<DIM> operator*(const vec<DIM>& left, const float right) {
	vec <DIM> result;
	for (size_t i = 0; i < DIM; ++i) { result[i] = left[i] * right; };			//multiplying coords by a scalar
	return result;
}

//template for vector dot product
template <size_t DIM> vec<DIM> operator*(const vec<DIM>& left, const vec<DIM>& right) {
	vec <DIM> result;
	for (size_t i = 0; i < DIM; ++i) { result[i] += left[i] * right[i]; };		//multiplying correspondent coordinates 
	return result;
}

//template for vector addition
template <size_t DIM> vec<DIM> operator+(vec <DIM> left, const vec<DIM>& right) {
	for (size_t i = 0; i < DIM; ++i) { left[i] += right[i]; };
	return left;
}

//template for vector substraction
template <size_t DIM> vec<DIM> operator-(vec <DIM> left, const vec<DIM>& right) {
	for (size_t i = 0; i < DIM; ++i) { left[i] -= right[i]; };
}

//template for obtaining the additive inverse of the vector (with the opposite sign)
template <size_t DIM> vec<DIM> operator-(vec <DIM>& left) {
	return left * (-1.f);
}

//a separate optimized template for the 3-vector
template <> struct vec<3> {
	float x = 0, y = 0, z = 0;
	float& operator[](const size_t i) { assert(i < 3); return i == 0 ? x : (1 == i ? y : z); }
	const float& operator[](const size_t i) const { assert(i < 3); return i == 0 ? x : (1 == i ? y : z); }

	float norm() { return std::sqrt(x * x + y * y + z * z); }	//defining a norm of a 3-vector

	vec<3>& normalize(float one = 1.f) {						//vector normalization
		*this = (*this) * (one / norm());
		return *this;
	}
};

//name mangling - naming our 3- and 4-vectors
typedef vec<3> vec3;
typedef vec<4> vec4;

//defining the cross product
vec3 cross(vec3 v1, vec3 v2) {
	return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

//template for the overloaded output operator
template <size_t DIM> std::ostream& operator<<(std::ostream& out, const vec <DIM>& v) {
	for (size_t i = 0; i < DIM; ++i) 
		out << v[i] << ' ';
	return out;
}

#endif