#include <opencv2\opencv.hpp>

// ͼ��ʴ����
void imageErode(cv::Mat img)
{
	cv::imshow("Before", img);
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
	cv::Mat res;
	cv::erode(img, res, element);
	cv::imshow("After", res);
	cv::waitKey(0);
}

// ͼ��ģ������
void imageBlur(cv::Mat img)
{
	cv::imshow("Before", img);
	cv::Mat res;
	cv::blur(img, res, cv::Size(7, 7));
	cv::imshow("After", res);
	cv::waitKey(0);
}

// ͼ���Ե��ȡ
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

// ��ȡ��Ƶ֡������������Ҫ����opencv_ffmpeg3416_64.dll
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
	// ������ɫֵΪshort���ͣ�ֵΪ0-255��
	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for (int i = 0; i < 256; i++)
	{
		// ��256ɫֵ����Ϊ64ɫֵ��
		p[i] = (i / 4) * 4;//(i/10)*i;
	}

	cv::Mat dst;
	// ʹ�ò��ұ�ķ�ʽ��ͼƬ��ɫ�������м��١�
	// �����0-255����ֵ��ɫ���ֵ������㼴�ɻ�á�
	cv::LUT(src, lookUpTable, dst);
	cv::imshow("Before", src);
	cv::imshow("after", dst);
}

// ʹ��RIO�������ͼ��
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

// ʹ�����Ի��
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
	cv::imshow("���Ի�ϴ���", dst);
}

// roi+���Ի�ϣ����ư�͸��Ч����
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

	cv::imshow("ROI���Ի��", image);
}

// ������ɫͨ��
// indexȡֵΪ0��1��2���ֱ����BGRͨ��
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
	// ע���˴���ȡ�Ҷ�ͼ���Ҷ�ͼΪ��ͨ����
	cv::Mat logo = cv::imread("./res/dota_logo.jpg", cv::IMREAD_GRAYSCALE);
	if (logo.empty())
	{
		return;
	}
	std::vector<cv::Mat> channels;
	cv::split(image, channels);
	cv::Mat channel = channels.at(index);
	cv::Mat roiImage = channel(cv::Rect(200, 250, logo.cols, logo.rows));
	// ��֮ǰlogo��ȡ�Ĳ��ǻҶ�ͼ���˴����Խ���ͨ������ͨ�����ӣ����򱨴�
	cv::addWeighted(roiImage, 1.5, logo, 0.5, 0.0, roiImage);
	cv::merge(channels, image);
	cv::imshow("����ͨ��", image);
}

