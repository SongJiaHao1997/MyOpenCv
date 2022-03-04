#include <iostream>
#include "cv_mouse.hpp"

int main(int, char**)
{
	/*std::cout << cv::getVersionString() << std::endl;
	cv::Mat src = cv::imread("./res/Lena.png", cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH);
	if (src.empty())
	{
		std::cout << "can not load image!" << std::endl;
		system("pause");
		return -1;
	}*/
	mouseEventExample();
    return 0;
}