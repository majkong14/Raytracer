#define _USE_MATH_DEFINES
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

//Light source
struct Light {
    Light(const Vec3f& p, const float& i) : position(p), intensity(i) {}
    Vec3f position;
    float intensity;
};

//Materials
struct Material {
    Material(const Vec3f& color) : diffuse_color(color) {}
    Material() : diffuse_color() {}
    Vec3f diffuse_color;                //Basically emitted low-intensity light from the obj
};

//A sphere
struct Sphere {
    Vec3f center;
    float radius;
    Material material;

    Sphere(const Vec3f& c, const float& r, const Material& m) : center(c), radius(r), material(m) {}

    //Determine if the ray intersects the sphere
    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const {
        Vec3f L = center - orig;
        float tca = L * dir;
        float d2 = L * L - tca * tca;
        if (d2 > radius * radius) return false;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;                    //Discarding the backwards-facing intersection point
        if (t0 < 0) return false;
        return true;
    }
};

//Casting the ray into the scene
bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<Sphere> &spheres, Vec3f hit, Vec3f N, Material& material) {
    float spheres_dist = std::numeric_limits<float>::max();                                 //Setting a distance to the sphere to infinity as a default
    for (size_t i = 0; i < spheres.size(); i++) {
        float dist_i;
        if (spheres[i].ray_intersect(orig, dir, dist_i) && dist_i < spheres_dist) {          //If a ray hits a sphere NOT at infinity, we:
            spheres_dist = dist_i;                                                           //0. setting the distance to the sphere
            hit = orig + dir * dist_i;                                                       //1. determine the hit point
            N = (hit - spheres[i].center).normalize();                                       //2. find the normal (vec from the center of a sphere to the hit point (on the surface))
            material = spheres[i].material;                                                  //3. assign the material (diffuse color) of the sphere to the ray
        }
    }
    return spheres_dist < 1000;                         //We perform back-clipping - specifying the max distance after which the spheres won't be displayed
};

//A new cast_ray function
Vec3f cast_ray(const Vec3f& orig, const Vec3f dir, const std::vector<Sphere> &spheres, const std::vector<Light> &lights) {
    Vec3f point, N;
    Material material;

    if (!scene_intersect(orig, dir, spheres, point, N, material)) {
        return Vec3f(0.7, 0.8, 0.2);                    //Backgnd color if the ray hits nothing
    }
    
    float diffuse_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++) {                                        //Otherwise, we calculate the pixel's color relative according to the light sources nearby
        Vec3f light_dir = (lights[i].position - point).normalize();                     //Determine the ray from the light src to the point
        diffuse_light_intensity += lights[i].intensity * std::max(0.f, light_dir * N);  //Using dot product to calculate intensity
    }
    return material.diffuse_color * diffuse_light_intensity;
};

//the function that renders the scene
void render(const std::vector<Sphere>& spheres, const std::vector<Light> &lights) {
    const int width = 1024;                             //Image dimensions
    const int height = 768;
    const float fov = M_PI / 3;
    std::vector<Vec3f> framebuffer(width * height);     //Creating a framebuffer using std::vector from STL

#pragma omp parallel for                                //Cycle vectorization => faster rendering
    for (size_t j = 0; j < height; j++) {
        std::cerr << "\r Scanlines ready: " << j << std::flush;             //Progress indicator
        for (size_t i = 0; i < width; i++) {
            float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i + j * width] = cast_ray(Vec3f(0, 0, 0), dir, spheres, lights);
        }
    }

    std::cerr << "\nSaving...\n";

    std::ofstream ofs; // Save the framebuffer to file
    ofs.open("./output.ppm");
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height * width; ++i) {                                     //Here "i" is a joint index to traverse the image buffer like 2D array
        for (size_t j = 0; j < 3; j++) {                                              // "j" is a counter that separates the 3-vector triplets
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));     // Writing image to the file
        }
    }
    ofs.close();

    std::cerr << "Done.";
}

int main() {
    Material mat1(Vec3f(0.4, 0.3, 0.4));
    Material mat2(Vec3f(0.1, 0.1, 0.3));

    std::vector<Sphere>spheres;
    spheres.push_back(Sphere(Vec3f(1.5, -0.5, -18), 3, mat1));
    spheres.push_back(Sphere(Vec3f(7, 5, -18), 4, mat2));

    std::vector<Light>  lights;
    lights.push_back(Light(Vec3f(-20, 20, 20), 1.5));

    render(spheres, lights);

    return 0;
}