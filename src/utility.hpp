#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


template <typename T>
inline T clamp(T x, T min, T max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


// Common Headers

#include "ray.hpp"
#include "vector.hpp"
#include "random.hpp"

#endif