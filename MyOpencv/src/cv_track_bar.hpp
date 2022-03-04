#include <opencv2\highgui.hpp>
#include <iostream>

#define WINDOW_NAME "线性混合示例"

cv::Mat g_image1, g_image2, g_dstImage;

int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;

void on_TrackBack(int, void* arg)
{
	g_dAlphaValue = (double)(g_nAlphaValueSlider / g_nMaxAlphaValue);
	g_dBetaValue = 1.0 - g_dAlphaValue;
	cv::addWeighted(g_image1, g_dAlphaValue, g_image2, g_dBetaValue, 0.0, g_dstImage);
	cv::imshow(WINDOW_NAME, g_dstImage);
}

void showTrackBar()
{
	g_image1 = cv::imread("./res/Lena_HLS.png");
	if (g_image1.empty())
	{
		std::cout << "can not load image1" << std::endl;
		return;
	}
	g_image2 = cv::imread("./res/Lena.png");
	if (g_image2.empty())
	{
		std::cout << "can not load image2" << std::endl;
		return;
	}
	g_nAlphaValueSlider = 70;
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
	char trackBarName[50] = {0};
	sprintf_s(trackBarName, 50, "透明度%d ", g_nMaxAlphaValue);
	cv::createTrackbar(trackBarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_TrackBack);
	
	// 获取滚动条数值
	std::cout << cv::getTrackbarPos(trackBarName, WINDOW_NAME) << std::endl;

	on_TrackBack(g_nAlphaValueSlider, nullptr);
	cv::waitKey(0);
}