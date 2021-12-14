# Raytracer
Trying to make a simple raytracer from the ground-up. Inspired by the Ray Tracing in One Weekend by Peter Shirley
The initial requirements list features:
1. Ability to output an image (so-called "Hello world" for the graphics) #complete
2. Be able to operate with simple primitives (triangles, spheres)
3. Feature a simple camera (including futher extensions for positioning and/or varying focus depth)
4. Feature antialiasing (to fight Mach transitions, rough edges, and so on)
5. Feature different types of materials (diffuse, metal, dielectrics)
6. Support input from a file using a list of simple commands, keywords, etc.

This is a step-by-step roadmap for the development of this project. 
The implementation of the features from above will occur in the exact order in which they are mentioned.

Further improvement might include some code optimization and refactoring efforts:
  The refactoring part might include reorganizing the code in the more canonical fashion, 
  speaking from the high-level perspective. More explicitly, the hierarchy of classes can
  be reorganized, following the scheme from the picture below.
  ![](https://inst.eecs.berkeley.edu//~cs184/fa09/resources/raytracing.files/raytracer.png "High level class hierarchy for refactoring")
  
  You can find more on this topic here: [CS184 Ray Tracer Design Note](https://link-url-here.org)
  
  Code optimization has a broader scope and might vary depending on how (and if) would you 
  choose to refactor the classes. Sole -inline functions put aside, you might also be 
  interested in putting all the common resources (e.g. math functions, generic library 
  #include's, etc.) in the jumbo file, to gain some advantage in performing compilation.
  Math functions can be reimplemented in the form of simplified math expressions featuring 
  multiplication, addition, substraction, putting division at the very end (to avoid 
  multiple divisions while performing a calculation). Albeit requiring some manual formula
  expansions (rendering the code more verbose) this might result int some increased time and
  space efficiency.
  
Feel free to fork and implement your suggestions
