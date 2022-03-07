#include <opencv2\opencv.hpp>
#define WINDOW_NAME "����¼�"

bool g_bOnDraw = false;
cv::Rect g_rectangle;
cv::RNG g_rng;

void drawRect(cv::Mat& image, cv::Rect rect)
{
	if (rect.width < 0)
	{
		rect.x += rect.width;
		rect.width *= -1;
	}
	if (rect.height < 0)
	{
		rect.y += rect.height;
		rect.height *= -1;
	}
	cv::rectangle(image, rect, cv::Scalar(g_rng.uniform(0, 255), 
							g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

void onMouseEvent(int event, int x, int y, int flags, void* args)
{
	cv::Mat& image = *(static_cast<cv::Mat*>(args));
	switch (event)
	{
		case cv::EVENT_LBUTTONDOWN:
		{
			g_bOnDraw = true;
			g_rectangle = cv::Rect(x, y, 0, 0);
			break;
		}
		case cv::EVENT_LBUTTONUP:
		{
			g_bOnDraw = false;
			drawRect(image, g_rectangle);
			break;
		}
		case cv::EVENT_MOUSEMOVE:
		{
			if (g_bOnDraw)
			{
				g_rectangle.width = x - g_rectangle.x;
				g_rectangle.height = y - g_rectangle.y;
			}
			break;
		}
		default:
			break;
	}
}

void mouseEventExample()
{
	g_rectangle = cv::Rect(-1, -1, 0, 0);
	cv::Mat image(600, 800, CV_8UC3);
	cv::Mat tempImage;
	image = cv::Scalar::all(0);
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
	// ע���˴�����ص��Ĳ���Ϊԭͼ��
	cv::setMouseCallback(WINDOW_NAME, onMouseEvent, (void*)(&image));
	for (;;)
	{
		// ����ԭͼ����ʱ��������������������Ϣ����ǰ���ı�ԭͼ��
		image.copyTo(tempImage);
		if (g_bOnDraw)
		{
			// ����ʱͼ���ϻ��Ƶ�ǰ���Σ���ʱ���δ�ɿ���
			drawRect(tempImage, g_rectangle);
		}
		cv::imshow(WINDOW_NAME, tempImage);
		if (cv::waitKey(10) == 27) // Esc��������
		{
			break;
		}
	}
}