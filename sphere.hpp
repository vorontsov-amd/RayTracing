#pragma once
#include <iostream>
#include <cmath>
#include "vector.hpp"
#include "double.hpp"
#include "ray.hpp"

class material;

struct hit_record
{
    double t;
    Vector P;
    Vector normal;
    material* mat_prt;
};


class Hitable
{
public:
    virtual bool hit(const Ray& ray, double min, double max, hit_record& rec) const = 0;
};


class Sphere : public Hitable
{
public:
    double cradius;
    Vector ccenter;
    Vector ccolor;
    material* mat_ptr;
public:
    Sphere(const Vector& center, double radius, material* mat, const Vector& color = Vector(0, 200, 100)) :
        ccenter(center),
        cradius(radius),
        ccolor(color),
        mat_ptr(mat)
        {} 

    bool hit(const Ray& ray, double min, double max, hit_record& rec) const override;

    bool сontains(const Vector& point) const; 
    bool сontainsInside(const Vector& point) const; 
    Vector normal(const Vector& point) const;  
    Vector normal(const Vector&& point) const;  
};


inline bool Sphere::hit(const Ray& ray, double t_min, double t_max, hit_record& rec) const
{
    Vector oc = ray.origin() - ccenter;

    double a = ray.direction() * ray.direction();
    double b = oc * ray.direction();
    double c = oc * oc - cradius * cradius;
    double D = b * b - a * c;
    rec.mat_prt = mat_ptr;

    if (D > 0)
    {
        double temp = (-b - std::sqrt(D)) / a;
        if (temp < t_max and temp > t_min)
        {
            rec.t = temp;
            rec.P = ray.pointAtParametr(rec.t);
            rec.normal = (rec.P - ccenter) / cradius;
            return true;
        }
        temp = (-b + std::sqrt(D)) / a;
        if (temp < t_max and temp > t_min)
        {
            rec.t = temp;
            rec.P = ray.pointAtParametr(rec.t);
            rec.normal = (rec.P - ccenter) / cradius;
            return true;
        }
    }
    return false;
}


inline bool Sphere::сontains(const Vector& point) const
{    
    Double x  =   point.getX(), y  =   point.getY(),  z =   point.getZ(), radius = cradius,
           x0 = ccenter.getX(), y0 = ccenter.getY(), z0 = ccenter.getZ();

    return (x - x0 ^ 2) + (y - y0 ^ 2) + (z - z0 ^ 2) == (radius ^ 2);  
}

inline bool Sphere::сontainsInside(const Vector& point) const
{    
    Double x  =   point.getX(), y  =   point.getY(),  z =   point.getZ(), radius = cradius,
           x0 = ccenter.getX(), y0 = ccenter.getY(), z0 = ccenter.getZ();

    return (x - x0 ^ 2) + (y - y0 ^ 2) + (z - z0 ^ 2) <= (radius ^ 2);  
}

inline Vector Sphere::normal(const Vector& point) const
{
    if (!сontains(point))
    {
        return Vector(0, 0, 0);
    }

    return point - ccenter;
}

inline Vector Sphere::normal(const Vector&& point) const
{
    if (!сontains(point))
    {
        return Vector(0, 0, 0);
    }

    return point - ccenter;
}
