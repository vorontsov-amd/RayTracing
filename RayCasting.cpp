#include <iostream>
#include "vector.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"
#include <cstdlib>
#include "material.hpp"

// auto CreateSysCoord(unsigned x, unsigned y)
// {
//     Vector i = {1, 0, 0}, j = {0, -1, 0}, k = {0, 0, 1};
//     Vector O = {0, y, 0};
//     return SystemCoord(O, i, j, k);
// }

// void RenderCircle(sf::RenderWindow& window, const Vector& LigthSource, const SystemCoord& system)
// {
//     Sphere sphere(system.cstart_point, 300);

//     sf::RectangleShape pixel(sf::Vector2f(2, 2));

//     Vector radius_point = {};

//     Color  SourceColor(255, 250, 250);
//     Color  SphereColor(sphere.ccolor);

//     for (int y = 0, height = window.getSize().y; y < height; ++y)
//     {
//         for (int x = 0, weight = window.getSize().x; x < weight; ++x)
//         {
//             pixel.setPosition(x, y);


//             if (sphere.сontainsInside(Vector(x, y)))
//             {                
//                 double z = std::sqrt((Double(sphere.cradius) ^ 2) - 
//                                      (Double(x - sphere.ccenter.getX()) ^ 2) -
//                                      (Double(y - sphere.ccenter.getY()) ^ 2)) +
//                            sphere.ccenter.getZ();
                
//                 Vector L = LigthSource - Vector(x, y, z);
//                 Vector n = sphere.normal(Vector(x, y, z));

//                 double D = 0.95 * cos(L, n); 
//                 D = (D < 0) ? 0 : D;

//                 Vector V = Vector(0, 0, 1000, system) - Vector(x, y, z);
//                 Vector reflected = n * (2 * (n * L) / (n.length() * n.length())) - L;

//                 double S = Double(0.95) * Double(cos(V, reflected)) ^ 35;
            
//                 S = (S < 0) ? 0 : S;

//                 double A = 0.1;

//                 Color PointColor = static_cast<Vector> (SourceColor * SphereColor) * D +  
//                                    static_cast<Vector> (SourceColor * SphereColor) * A +
//                                    static_cast<Vector> (SourceColor) * S; 



//                 pixel.setFillColor(sf::Color(PointColor.getX(), PointColor.getY(), PointColor.getZ()));
//                 window.draw(pixel);
//             }
//             else
//             {
//                 pixel.setFillColor(sf::Color(100, 100, 100));
//                 window.draw(pixel);
//             }
//         }
//     }
// }


Color GetColor(const Ray& r, const Hitable* world, int depth)
{
    hit_record rec;
    if (world->hit(r, 1, MAXFLOAT, rec) && rec.t > 0)
    {
        Ray scattered;
        Color attenuation;
        
        if (depth < 50 and rec.mat_prt->scatter(r, rec, attenuation, scattered))
        {
            //std::cout << depth << '\t';
            //std::cout << scattered.direction() << "\t";
            //std::cout << attenuation << " " << GetColor(scattered, world, depth + 1) << attenuation * GetColor(scattered, world, depth + 1) << '\n';
            return attenuation * GetColor(scattered, world, depth + 1);
        }
        else 
        {
            //puts("SUCK");
            return Vector {0, 0, 0};
        }
    }
    else
    {
        double t = 0.5 * (r.direction().normalize().getY() + 1);
        //std::cout << t << std::endl;
        return (t) * Color{255, 255, 255} + (1-t) * Color{127, 178, 255};
    }
}


void RenderScene(sf::RenderWindow& window, const Camera& cam, const Hitable* world)
{
    sf::RectangleShape pixel(sf::Vector2f(1, 1));



    for (int y = 0, height = window.getSize().y; y < height; ++y)
    {
        std::cout << double(y) / height * 100 << "%" << "\n";
        for (int x = 0, weight = window.getSize().x; x < weight; ++x)
        {
            pixel.setPosition(x, y);
            Color color;
            int sn = 5;
            for (int s = 0; s < sn; ++s)
            {
                int u = x + 2 * drand48() - 1;
                int v = y + 2 * drand48() - 1;
                Ray ray = cam.get_ray(u, v);
                color += GetColor(ray, world, 1); 
            }
            color /= sn;
            pixel.setFillColor(sf::Color(color.getX(), color.getY(), color.getZ()));
            window.draw(pixel);
        }
    }
}


int main()
{   
    const int X = 800, Y = 800, Z = 400;

    sf::RenderWindow window(sf::VideoMode(X, Y), "RayCasting");
    Camera cam {Vector{X / 2, Y / 2, Z}, X, Y};
    //auto system = CreateSysCoord(X, Y); 
    Hitable* list[4];
    list[0] = new Sphere(Vector{X/2,       Y/2,         -200}, 200,     new lambertian{Vector{0.8*255, 0.3*255, 0.3*255}});
    list[1] = new Sphere(Vector{X/2,       Y/2 + 40200, -100}, 40000,   new lambertian{Vector{0.8*255, 0.8*255, 0*255}});
    list[2] = new Sphere(Vector{X/2 + 400, Y/2,         -200}, 200,     new metal{Vector{0.8*255, 0.6*255, 0.2*255}, 0.3});
    list[3] = new Sphere(Vector{X/2 - 400, Y/2,         -200}, 200,     new metal{Vector{0.8*255, 0.8*255, 0.8*255}, 1.0});
    auto* world = new Hittable_list{&list[0], 4};

    // std::cout << cam.lower_left_corner << '\n';
    // std::cout << cam.get_ray(0, Y).direction();


    while (window.isOpen())
    {
        //window.clear(sf::Color(120, 120, 120));
        srand48(0);

        sf::Event event;
        while (window.pollEvent(event))
        {            
            if (event.type == sf::Event::Closed)
                window.close();
        }

        RenderScene(window, cam, world);        
        window.display();
    }
}