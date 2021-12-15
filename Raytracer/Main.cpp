#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "Geometry.h"
using std::cout;

//the function that renders the scene
void render() {
	//Image dimensions
	//avoid defining global constants
	const int image_width = 1024; 
	const int image_height = 768;
	
	std::vector<Vec3f> framebuffer(image_width * image_height); //creating a framebuffer using std::vector from STL

	//Render cycle - writing to the framebuffer
	for (int j = 0; j < image_height; ++j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush; //progress indicator

		for (int i = 0; i < image_width; ++i) {
			framebuffer[i + j * image_width] = Vec3f(j / float(image_height), i / float(image_width), 0.25);
		}
	}

	//create and open the file to save the image
	std::ofstream ofs; 
	ofs.open("./output.ppm");
	ofs << "P6\n" << image_width << " " << image_height << "\n255\n";

	std::cerr << "\nSaving...\n";

	//Writing image to the file
	for (size_t i = 0; i < image_height * image_width; ++i) {			//here "i" is a joint index to traverse the image buffer like 2D array
		for (size_t j = 0; j < 3; j++) {					// "j" is a counter that separates the 3-vector triplets
			ofs << (char)(255 * max(0.f, min(1.f, framebuffer[i][j])));
		}
	}
	ofs.close();

	std::cerr << "\nDone.\n";
}

int main() {
	render();
	return 0;
}
