#include "pch.h"
#include <iostream>
#include "RayTracer.h"

int main()
{
    std::cout << "Hello World!\n"; 
	
	std::string temp = "C:/temp/raytrace.bmp";
	char tab2[1024];
	strcpy_s(tab2, temp.c_str());


	RayTracer rt;
	rt.renderPicture(400, 400, tab2);
}