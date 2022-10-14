#pragma once
#include "ray.hpp"
#include "vector.hpp"
#include "sphere.hpp"


class Hittable_list : public Hitable
{
private:
    Hitable** clist;
    size_t clist_size;
public:
    Hittable_list() {}
    Hittable_list(Hitable** list, int list_size) : clist(list), clist_size(list_size) {}
    ~Hittable_list() {}
    virtual bool hit(const Ray& ray, double min, double max, hit_record& rec) const override;
};

inline bool Hittable_list::hit(const Ray& ray, double t_min, double t_max, hit_record& rec) const
{
    hit_record tmp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < clist_size; ++i)
    {
        if (clist[i]->hit(ray, t_min, closest_so_far, tmp_rec))
        {
            hit_anything = true;
            closest_so_far = tmp_rec.t;
            rec = tmp_rec;
        }
    }
    return hit_anything;
}

