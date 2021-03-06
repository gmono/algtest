// imagezip.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#pragma comment(lib,"opencv_world320d.lib")
//#pragma comment(lib,"7zcproj.lib")
using namespace cv;

#define calwsize(bsize,type) (bsize/sizeof(type)+(bsize%sizeof(type)!=0 ? 1:0))
inline void imagezip(Mat &buf1, Mat &buf2, Mat &result)
{
	if (!(result.rows&&result.cols)) return;
	uchar *b1 = buf1.data;
	uchar *b2 = buf2.data;
	uchar *res = result.data;
	int bufsize = result.step*result.rows;
	int i = 0;
#pragma omp parallel for
	for (i = 0; i<bufsize; i += sizeof(__m256i))
	{
		*(__m256i *)(res + i) = _mm256_xor_si256(*(__m256i *)(b1 + i), *(__m256i *)(b2 + i));
	}
}
template<class T>
void g_imagezip(Mat &buf1,Mat &buf2,Mat &result)
{
	if (!(result.rows&&result.cols)) return;
	uchar *b1 = buf1.data;
	uchar *b2 = buf2.data;
	uchar *res = result.data;

	int bufsize = result.step*result.rows ;
	int i = 0;
#pragma omp parallel for
	for (i = 0; i<bufsize; i += sizeof(T))
	{
		*(T *)(res+i)=(*(T *)(res + i) = *(T *)(b1 + i) ^ *(T *)(b2 + i))<0? 0:*(T *)(res+i) ;
	}
}
bool stop = false;
void stopfun(int state, void *userdata)
{
	stop = true;
}
int main()
{
	
	VideoCapture capture("E:/Video/1A-布局-上/1A-01-01-03-课程大纲和简介.mp4");
	if (!capture.isOpened()) return 1;
	double rate = capture.get(CV_CAP_PROP_FPS);
	Mat frame;
	Mat old;
	namedWindow("myvideo", WINDOW_NORMAL);
	namedWindow("myvideo2", WINDOW_NORMAL);
	namedWindow("huanyuan", WINDOW_NORMAL);
	//int delay = 1000 / rate/2;
	int delay = 1000 / rate;
	capture.set(CV_CAP_PROP_POS_FRAMES, 100);
	bool isone = true;
	int i = 1;
	char *buf = new char[4096];
	buf[1] = '.'; buf[2] = 'p'; buf[3] = 'n'; buf[4] = 'g'; buf[5] = '\0';
	while (!stop)
	{

		if (!capture.read(frame))
			break;
		if (isone)
		{
			frame.copyTo(old);
			buf[0] = i + '0';
			imwrite(buf, frame);
			isone = false;
		}
		imshow("myvideo", frame);
		Mat res(frame.rows, frame.cols, CV_8UC3);
		Mat hy(frame.rows, frame.cols, CV_8UC3);
		if (frame.data&&old.data)
		{
			imagezip(frame,old,res);
			imshow("myvideo2", res);
		}
		
		
			//显示异或回归
		if (old.data&&res.data)
		{
			imagezip(old,res,hy);
			imshow("huanyuan", hy);

			if (!isone)
			{
				buf[0] = i + '0';
				imwrite(buf, res);
				hy.copyTo(old);
			}
		}
		i++;
		waitKey(delay);
	}
	
	capture.release();
	return 0;
}
