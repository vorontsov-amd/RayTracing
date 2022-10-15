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


bool refract(const Vector& v, const Vector& n, double ni_over_nt, Vector& refracted)
{
    Vector uv = const_cast<Vector&>(v).normalize();
    double dt = uv * n;
    double discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
        return true;
    }
    return false;
}

double schlick(double cosine, double ref_idx)
{
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 *= r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

class dielectric : public material
{
private:
    double ref_idx;
public:
    dielectric(double ri) : ref_idx(ri) {}
    bool scatter(const Ray& r_in, const hit_record& rec, Vector& attenuation, Ray& scattered) const override
    {
        Vector outward_normal;
        Vector reflected = reflect(r_in.direction(), rec.normal);
        double ni_over_nt = 0;
        attenuation = Vector{255, 255, 255};
        Vector refracted;
        double reflect_prob = 0;
        double cosine = 0;
        if (r_in.direction() * rec.normal > 0)
        {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * (r_in.direction() * rec.normal) / r_in.direction().length();
        }
        else
        {
            outward_normal = rec.normal;
            ni_over_nt = 1 / ref_idx;
            cosine = -(r_in.direction() * rec.normal) / r_in.direction().length();
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
        {
            reflect_prob = schlick(cosine, ref_idx);            
        }
        else
        {
            scattered = Ray{rec.P, reflected};
            reflect_prob = 1;
        }
        if (drand48() < reflect_prob)
        {
            scattered = Ray{rec.P, reflected};
        }
        else
        {
            scattered = Ray{rec.P, refracted};
        }
        return true;
    }
};


