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
[Image_1]()

#Step 2 completed
12.18.2021 - main.cpp, and geometry.h updated - added new rendering cycle (paralellized using OMP), ray tracing function, can 
put objects into the scene, new onjects - sphere. 
See first raytraced sphere here:
[Image_2]()

#Step 5 completed
main.cpp updated - added materials, modified Sphere structure, scene_intersect() function added (iteratively check whether 
spheres from the array must be shaded or not), cast_ray() function updated, an array (stack) of spheres added.
See several spheres on the scene here:
[Image 3]()
