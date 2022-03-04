#include <opencv2\opencv.hpp>

// Í¼Ïñ¸¯Ê´²Ù×÷
void imageErode(cv::Mat img)
{
	cv::imshow("Before", img);
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
	cv::Mat res;
	cv::erode(img, res, element);
	cv::imshow("After", res);
	cv::waitKey(0);
}

// Í¼ÏñÄ£ºý²Ù×÷
void imageBlur(cv::Mat img)
{
	cv::imshow("Before", img);
	cv::Mat res;
	cv::blur(img, res, cv::Size(7, 7));
	cv::imshow("After", res);
	cv::waitKey(0);
}

// Í¼Ïñ±ßÔµÌáÈ¡
void imageCanny(cv::Mat img)
{
	cv::imshow("Before", img);
	cv::Mat res, img_gary;
	cv::cvtColor(img, img_gary, cv::COLOR_BGR2GRAY);
	cv::blur(img_gary, res, cv::Size(3, 3));
	cv::Canny(res, res, 3, 9, 3);
	cv::imshow("After", res);
	cv::waitKey(0);
}

// ¶ÁÈ¡ÊÓÆµÖ¡£¬³ÌÐòÔËÐÐÐèÒªÒÀÀµopencv_ffmpeg3416_64.dll
int videoShow(const cv::String& path)
{
	cv::VideoCapture capture(path);
	if (!capture.isOpened())
	{
		return -1;
	}
	cv::Mat frame;
	for (;;)
	{
		capture >> frame;
		//cv::imshow("Video", frame);
		imageCanny(frame);
		cv::waitKey(30);
	}
	return 0;
}

