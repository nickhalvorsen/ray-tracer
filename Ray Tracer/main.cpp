#include "pch.h"
#include <iostream>
#include "ImageRenderer.h"

int main()
{
    std::cout << "Hello World!\n"; 
	
	std::string temp = "C:/temp/raytrace.bmp";
	char tab2[1024];
	strcpy_s(tab2, temp.c_str());

	RayTracer rt(2, 1, Color(0, 0, 0));
	ImageRenderer r;
	r.renderPictureToFile(&rt, 800, 800, tab2);
}