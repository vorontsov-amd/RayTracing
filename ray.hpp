#pragma once
#include "vector.hpp"

class Ray
{
private:
    Vector centry;
    Vector cdirection;
public:
    Ray() {}
    Ray(const Vector& entry, const Vector& direction) : centry(entry), cdirection(direction) {}
    
    Vector origin() const { return centry; }
    Vector direction() const { return cdirection; }
    Vector pointAtParametr(double t) const { return centry + cdirection * t; }
};
