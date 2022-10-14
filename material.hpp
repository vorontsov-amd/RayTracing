#pragma once
#include "ray.hpp"
#include "sphere.hpp"

class material
{
private:
public:
    virtual ~material() {}
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector& attenuation, Ray& scaterred) const = 0;
};


Vector randInSphere()
{
    Vector p;
    do
    {
        p = 2 * Vector{drand48(), drand48(), drand48()} - Vector{1,1,1};
    } while (p.length() >= 1);
    return p;
} 



class lambertian : public material
{
private:
    Vector albedo;
public:
    lambertian(const Vector& a) : albedo(a) {}
    bool scatter(const Ray& r_in, const hit_record& rec, Vector& attenuation, Ray& scattered) const override
    {
        Vector target = rec.P + rec.normal + randInSphere();
        scattered = Ray{rec.P, target - rec.P};     
        attenuation = albedo;
        return true;
    }
};


Vector reflect(const Vector& v, const Vector n)
{
    return v - 2 * (v * n) * n;
}

class metal : public material
{
private:
    Vector albedo;
    double fuzz;
public: 
    metal(const Vector& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
    bool scatter(const Ray& r_in, const hit_record& rec, Vector& attenuation, Ray& scattered) const override
    {
        Vector reflected = reflect(r_in.direction().normalize(), rec.normal);
        scattered = Ray{rec.P, reflected + fuzz * randInSphere()};
        attenuation = albedo;
        return scattered.direction() * rec.normal > 0;
    }
};


