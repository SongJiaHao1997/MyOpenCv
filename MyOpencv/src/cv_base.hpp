#include <opencv2\opencv.hpp>

// 图像腐蚀操作
void imageErode(cv::Mat img)
{
	cv::imshow("Before", img);
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
	cv::Mat res;
	cv::erode(img, res, element);
	cv::imshow("After", res);
	cv::waitKey(0);
}

// 图像模糊操作
void imageBlur(cv::Mat img)
{
	cv::imshow("Before", img);
	cv::Mat res;
	cv::blur(img, res, cv::Size(7, 7));
	cv::imshow("After", res);
	cv::waitKey(0);
}

// 图像边缘提取
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

// 读取视频帧，程序运行需要依赖opencv_ffmpeg3416_64.dll
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

void colorReduce(cv::Mat src)
{
	// 像素颜色值为short类型，值为0-255。
	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for (int i = 0; i < 256; i++)
	{
		// 将256色值减少为64色值。
		p[i] = (i / 4) * 4;//(i/10)*i;
	}

	cv::Mat dst;
	// 使用查找表的方式对图片减色操作进行加速。
	// 即针对0-255像素值减色后的值无需计算即可获得。
	cv::LUT(src, lookUpTable, dst);
	cv::imshow("Before", src);
	cv::imshow("after", dst);
}

// 使用RIO混合两张图像
void rioImageMixed()
{
	cv::Mat image = cv::imread("./res/dota_pa.jpg");
	if (image.empty())
	{
		return;
	}
	cv::Mat logo = cv::imread("./res/dota_logo.jpg");
	if (logo.empty())
	{
		return;
	}

	cv::Mat roiImage = image(cv::Rect(50, 50, logo.cols, logo.rows));
	cv::Mat mask = cv::imread("./res/dota_logo.jpg", cv::IMREAD_GRAYSCALE);
	logo.copyTo(roiImage, mask);
	cv::imshow("mixed", image);
}

// 使用线性混合
void linearBlending()
{
	double alphaValue = 0.5;
	double betaValue = 1 - alphaValue;

	cv::Mat image1 = cv::imread("./res/mogu.jpg");
	cv::Mat image2 = cv::imread("./res/rain.jpg");
	if (image1.empty() || image2.empty())
	{
		return;
	}
	cv::Mat dst;
	cv::addWeighted(image1, alphaValue, image2, betaValue, 0.0, dst);
	cv::imshow("线性混合窗口", dst);
}

// roi+线性混合，类似半透明效果。
void rio_linearBlending()
{
	cv::Mat image = cv::imread("./res/dota_pa.jpg");
	if (image.empty())
	{
		return;
	}
	cv::Mat logo = cv::imread("./res/dota_logo.jpg");
	if (logo.empty())
	{
		return;
	}

	cv::Mat roiImage = image(cv::Rect(50, 50, logo.cols, logo.rows));

	cv::addWeighted(roiImage, 0.7, logo, 0.3, 0.0, roiImage);

	cv::imshow("ROI线性混合", image);
}

// 分离颜色通道
// index取值为0、1、2，分别代表BGR通道
void cvSplit(int index = 0)
{
	if (index < 0 || index >2)
	{
		return;
	}
	cv::Mat image = cv::imread("./res/dota_pa.jpg");
	if (image.empty())
	{
		return;
	}
	// 注：此处读取灰度图，灰度图为单通道。
	cv::Mat logo = cv::imread("./res/dota_logo.jpg", cv::IMREAD_GRAYSCALE);
	if (logo.empty())
	{
		return;
	}
	std::vector<cv::Mat> channels;
	cv::split(image, channels);
	cv::Mat channel = channels.at(index);
	cv::Mat roiImage = channel(cv::Rect(200, 250, logo.cols, logo.rows));
	// 若之前logo读取的不是灰度图，此处尝试将单通道和三通道叠加，程序报错。
	cv::addWeighted(roiImage, 1.5, logo, 0.5, 0.0, roiImage);
	cv::merge(channels, image);
	cv::imshow("分离通道", image);
}

