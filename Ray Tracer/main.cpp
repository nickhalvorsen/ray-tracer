#include "pch.h"
#include <iostream>
#include "Bitmap.h"

int main()
{
    std::cout << "Hello World!\n"; 
	Bitmap bitmap(200, 200);

	//for (int x = 0; x < 200; x++)
	//{
	//	for (int y = 0; y < 200; y++) {
	//		//bitmap.setPixel(x, y, Color(x, y, 200));
	//	}
	//}

	std::string temp = "C:/temp/raytrace.bmp";
	char tab2[1024];
	strcpy_s(tab2, temp.c_str());
	bitmap.writeToFile(tab2);
}