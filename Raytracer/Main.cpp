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
	
	//Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
	for (int j = 0; j < image_height; ++j) {

		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush; //progress indicator

		for (int i = 0; i < image_width; ++i) {
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.25;

			int ir = static_cast<int>(255.999 *r);
			int ig = static_cast<int>(255.999 *g);
			int ib = static_cast<int>(255.999 *b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n'; 
		}
	}

	std::cerr << "\nDone.\n";
}

int main() {
	render();
	return 0;
}