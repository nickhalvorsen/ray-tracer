#include "pch.h"
#include <iostream>
#include "ImageRenderer.h"

int main()
{
    std::cout << "Hello World!\n"; 
	
	std::string temp = "C:/temp/raytrace.bmp";
	char tab2[1024];
	strcpy_s(tab2, temp.c_str());


	ImageRenderer r;
	r.renderPictureToFile(400, 400, tab2);
}