#Step 1 completed
12.14.2021 - Created README.md, Images.md, Images_src, rendered first image (Image_0), main.cpp added to the .main branch. 
See first image here:
[Image_0](https://github.com/majkong14/Raytracer/blob/main/Images/Image_0.jpeg) 

12.15.2021 - Geometry.h created, pushed to main - a header file featuring the polymorphic framework for N-vectors. 
Implemented using the structures, but not classes because there's no need to complicate the code as of now. At this stage, 
templates provide enough flexibility. Namely, just two lines introducing vec3 and vec4 via name mangling (typedef) allow 
not to rewrite same code twice for vec3 and vec4 respectively.

12.16.2021 - Main.cpp updated, broke the .ppm color code, rendering cycle outputs the rainbow-gradient in a row followed by
the striped gradient of gray for all the other rows (possible change in framebuffer filling order - column-major one instead 
of the row-major).
[Image_1](https://github.com/majkong14/Raytracer/blob/main/Images/Image_1.jpeg)

#Step 2 completed
12.18.2021 - main.cpp, and geometry.h updated - added new rendering cycle (paralellized using OMP), ray tracing function, can 
put objects into the scene, new onjects - sphere. 
See first raytraced sphere here:
[Image_2](https://github.com/majkong14/Raytracer/blob/main/Images/Image_2.jpeg)

#Step 5 completed
main.cpp updated - added materials, modified Sphere structure, scene_intersect() function added (iteratively check whether 
spheres from the array must be shaded or not), cast_ray() function updated, an array (stack) of spheres added.
See several spheres on the scene here:
[Image_3](https://github.com/majkong14/Raytracer/blob/main/Images/Image_3.jpeg)

12.19.2021 - added lights structure (diffuse_lighting), scene_intersect(), cast_ray() modified, an array (stack) of lights 
added. Now it is possible to position lights => simple shadows are present.

12.21.2021 - added phong reflections (added specular component to the diffuse lighting), updated Material struct, added 
reflect() function, updated scene_intersect() function. New changes in the rendering loop: added a color 3-vector "&c" to 
contain the clamped values of the color of a pixel ("clamp" prevents the pixel from being brighter than the maximum allowed
brightness). 
See the image featuring Phong reflections here:
[Image_4](https://github.com/majkong14/Raytracer/blob/main/Images/Image_4.jpeg)

added shadows - cast_ray() function updated.
See the image with shadows:
[Image_5](https://github.com/majkong14/Raytracer/blob/main/Images/Image_5.jpeg)

12.22.2021 - added reflections and reflective materials, updated reflect() and cast_ray() functions, Material strucutre also updated.
The image with reflections here:
[Image_6](https://github.com/majkong14/Raytracer/blob/main/Images/Image_6.jpeg)

Added refractions - updated cast_ray() and added the refract() function (Snellius law for light refraction), updated the Material.
Now the image with refractions:
[Image_7](https://github.com/majkong14/Raytracer/blob/main/Images/Image_7.jpeg)

Added a board with the checkered skin - updated scene_intersect() (code analogous to the one needed for the sphere) + added a condition
for drawing the checkered skin on the plane in the scene_intersect(). Board (a plane, in essence), is given by an explicit equation 
(namely y = -4), so no structure to define the plane is needed.
The image with the plane on it:
[Image_8](https://github.com/majkong14/Raytracer/blob/main/Images/Image_8.jpeg)
