#ifndef ARES_MATHTOOLS_H
#define ARES_MATHTOOLS_H

#include <common/ares_mathTypes.h>
#include <stdio.h>
 
template <typename T>
inline T saturation(const T value, Vec2 limits){
    /*remind that left is smaller than other right one
    limits: vec2, Vec2(-lower,upper)
    return value inside limits*/
    T min = limits(0);
    T max = limits(1);
    if(value < min){
        return min;
    }
    if(value > max){
        return max;
    }
    return value;
}
inline Vec3 rotMatToRPY(const Mat3& R) {
    Vec3 rpy;
    rpy(0) = atan2(R(2,1),R(2,2));
    rpy(1) = asin(-R(2,0));
    rpy(2) = atan2(R(1,0),R(0,0));
    return rpy;
}
inline RotMat quatToRotMat(const Quat& q) {
    double e0 = q(0);
    double e1 = q(1);
    double e2 = q(2);
    double e3 = q(3);

    RotMat R;
    R << 1 - 2 * (e2 * e2 + e3 * e3), 2 * (e1 * e2 - e0 * e3),
            2 * (e1 * e3 + e0 * e2), 2 * (e1 * e2 + e0 * e3),
            1 - 2 * (e1 * e1 + e3 * e3), 2 * (e2 * e3 - e0 * e1),
            2 * (e1 * e3 - e0 * e2), 2 * (e2 * e3 + e0 * e1),
            1 - 2 * (e1 * e1 + e2 * e2);
    return R;
}