#include "vector.hpp"
#include "ray.hpp"

class Camera
{
public:
    Vector position;
    Vector lower_left_corner;
    Vector horizontal;
    Vector vertical;
    unsigned YRES;
public:
    Camera(const Vector& init_position, unsigned X, unsigned Y) : 
        position {init_position}, 
        lower_left_corner {Vector{0, static_cast<double>(Y), 0} - position},
        horizontal {Vector{1, 0, 0}},
        vertical {Vector{0, -1, 0}},  
        YRES {Y}
        {}
    ~Camera() {}

    Ray get_ray(unsigned x, unsigned y) const
    {
        return Ray{position, -position + Vector{x, y}};
    }
};
