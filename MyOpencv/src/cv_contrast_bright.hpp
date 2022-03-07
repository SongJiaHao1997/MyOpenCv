#include <opencv2\highgui.hpp>

#define WINDOW_NAME		"亮度对比度测试"
#define CONTRAST_NAME	"对比度"
#define BRIGHT_NAME		"亮度"

int g_contrastVal = 100;
int g_brightVal = 0;
cv::Mat g_image;

void on_trackBar(int n, void* arg)
{
	g_contrastVal = cv::getTrackbarPos(CONTRAST_NAME, WINDOW_NAME);
	g_brightVal = cv::getTrackbarPos(BRIGHT_NAME, WINDOW_NAME);
	cv::Mat tempImage = g_image.clone();
	auto itBegin = tempImage.begin<cv::Vec3b>();
	auto itEnd = tempImage.end<cv::Vec3b>();
	for (auto it = itBegin; it != itEnd; ++it)
	{
		for (int i = 0; i < 3; ++i)
		{
			auto val = (*it)[i];
			(*it)[i] = cv::saturate_cast<uchar>((g_contrastVal * 0.01) * val + g_brightVal);
		}
	}
	cv::imshow(WINDOW_NAME, tempImage);
}

void contrastBrightDemo()
{
	g_image = cv::imread("./res/Lena.png");
	if (g_image.empty())
	{
		return;
	}
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
	cv::createTrackbar(CONTRAST_NAME, WINDOW_NAME, &g_contrastVal, 300, on_trackBar);
	cv::createTrackbar(BRIGHT_NAME, WINDOW_NAME, &g_brightVal, 100, on_trackBar);
	on_trackBar(0, nullptr);
}