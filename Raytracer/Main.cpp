#define _USE_MATH_DEFINES
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

struct Sphere {
    Vec3f center;
    float radius;

    Sphere(const Vec3f& c, const float& r) : center(c), radius(r) {}

    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const {
        Vec3f L = center - orig;
        float tca = L * dir;
        float d2 = L * L - tca * tca;
        if (d2 > radius * radius) return false;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        return true;
    }
};

Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const Sphere& sphere) {
    float sphere_dist = std::numeric_limits<float>::max();
    if (!sphere.ray_intersect(orig, dir, sphere_dist)) {
        return Vec3f(0.2, 0.7, 0.8); // Background color
    }

    return Vec3f(0.4, 0.4, 0.3);
}

//the function that renders the scene
void render(const Sphere& sphere) {
    const int width = 1024;                             //Image dimensions
    const int height = 768;
    const int fov = M_PI / 2.;
    std::vector<Vec3f> framebuffer(width * height);     //Creating a framebuffer using std::vector from STL

#pragma omp parallel for                                //Cycle vectorization => faster rendering
    for (size_t j = 0; j < height; j++) {
        std::cerr << "\r Scanlines ready: " << j << std::flush;             //Progress indicator
        for (size_t i = 0; i < width; i++) {
            float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i + j * width] = cast_ray(Vec3f(0, 0, 0), dir, sphere);
        }
    }

    std::cerr << "\nSaving...\n";

    std::ofstream ofs; // Save the framebuffer to file
    ofs.open("./out.ppm");
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
    Sphere sphere(Vec3f(-3, 0, -16), 2); //Putting the sphere on the scene
    render(sphere);

    return 0;
}