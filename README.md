# Ray Tracing

This project implements a basic ray tracing algorithm that can generate realistic 2D images in PPM format by simulating the behavior of light in a 3D scene. The program generates incident, refraction and reflection rays and, depending on the material properties (such as the type of material - lambertian, metal, dielectric and the corresponding indicators for these), generates a realistic picture in PPM format.

## Requirements

To use the Ray Tracer in this repository, you need to have the following:

- C++ Compiler (GCC, Clang, or MSVC)
- SFML Library

## Installation

You can clone the repository and compile the program by running the following commands in your terminal:

```
git clone https://github.com/vorontsov-amd/RayTracing.git
cd RayTracing/raytracer
make
```

This will generate an executable named `raytracer`.

## Example 

If you do not change the program code, by default it generates this image, saves it to the device and displays it on the screen 

![](https://sun9-7.userapi.com/impg/3_5Dmsv-lKFRoZHoVGRfqKsAY3BkkZE_W5DLwQ/fcZvDZfCqro.jpg?size=1200x800&quality=96&sign=728d9a9ffaff8b4976e989a4e569c16a&type=album)

## Future Development

We are currently in the process of developing a GUI for easy object layout and material property selection. The GUI will allow users to create and edit scenes using a simple drag-and-drop interface and will provide real-time previews of the generated images.

![](https://sun9-17.userapi.com/impg/7AbvEjcii8_0jvm_4B-uircreuDBkpGZdjF_8Q/Hx97n4h2CDg.jpg?size=2560x1817&quality=96&sign=bc4a4b61d010e84a233423493c7c99ba&type=album)

## Useful Materials 

[Ray Tracing in One Weekend](https://raytracing.github.io/)