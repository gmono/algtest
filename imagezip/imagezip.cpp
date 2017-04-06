// imagezip.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#pragma comment(lib,"opencv_world320.lib")
using namespace cv;

#define calwsize(bsize,type) (bsize/sizeof(type)+(bsize%sizeof(type)!=0 ? 1:0))
inline void imagezip(int rows,int cols, uchar *b1, uchar *b2, uchar *res)
{
	if (!(rows&&cols)) return;
	int bufsize = (rows*cols)/sizeof(__m256i);
	int i = 0;
#pragma omp parallel for
	for (i = 0; i<bufsize; i += sizeof(__m256i))
	{
		*(__m256i *)(res + i) = _mm256_xor_si256(*(__m256i *)(b1 + i), *(__m256i *)(b2 + i));
	}
}

bool stop = false;
void stopfun(int state, void *userdata)
{
	stop = true;
}
int main()
{
	VideoCapture capture("E:\\Video\\1A-����-��\\1A-01-01-03-�γ̴�ٺͼ��.mp4");
	if (!capture.isOpened()) return 1;
	double rate = capture.get(CV_CAP_PROP_FPS);
	Mat frame;
	Mat old;
	namedWindow("myvideo", WINDOW_NORMAL);
	namedWindow("myvideo2", WINDOW_NORMAL);
	namedWindow("huanyuan", WINDOW_NORMAL);
	int delay = 1000 / rate;
	capture.set(CV_CAP_PROP_POS_FRAMES, 100);
	while (!stop)
	{
		frame.copyTo(old);
		if (!capture.read(frame))
			break;
		Mat res(frame.rows,frame.cols,CV_8UC3);
		Mat hy(frame.rows, frame.cols, CV_8UC3);
		if(frame.data&&old.data)
			imagezip(frame.rows, frame.step,frame.data,old.data,res.data);
		imshow("myvideo", frame);
		imshow("myvideo2", res);
			//��ʾ���ع�
		if(old.data&&res.data)
			imagezip(frame.rows, frame.step, old.data, res.data, hy.data);
		imshow("huanyuan", hy);

		waitKey(delay);
	}

	capture.release();
	return 0;
}

