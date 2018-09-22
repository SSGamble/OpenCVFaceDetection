//#include<iostream>  
//#include <opencv2/core/core.hpp>  
//#include <opencv2/highgui/highgui.hpp>  
//
//using namespace cv;
//
//int main()
//{
	// OpenCV中使用Mat类型来存储载入的图片数据
//	// 读入一张图片（游戏原画）  
//	Mat img = imread("pic.jpg");
//
//	// 创建一个名为 "游戏原画"窗口  
//	namedWindow("游戏原画");
//
//	// 在窗口中显示游戏原画  
//	imshow("游戏原画", img);
//
//	// 等待6000 ms后窗口自动关闭  
//	waitKey(6000);
//}
//

///////////////////////////////////////////////////////////////////////////

// Haar特征检测 - 人脸识别
#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
using namespace std;
int main()
{
	// 加载Haar特征检测分类器
	// haarcascade_frontalface_alt.xml是 OpenCV 自带的分类器 -- 文件路径
	const char *pstrCascadeFileName = "haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade *pHaarCascade = NULL;
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);

//从文件中读取图像 
	const char *pstrImageName = "6.jpg";
	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
	
	// 转为灰度图 
	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);

	// 人脸识别与标记
	if (pHaarCascade != NULL)
	{
		//opencv内存管理是其自己设计的链表，创建一个内存存储器，来统一管理各种动态对象的内存
		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
		cvClearMemStorage(pcvMStorage);

		CvScalar FaceCirclecolors[] =
		{
			{ 0, 0, 255 } ,{ 0, 128, 255 } ,{ 0, 255, 255 } ,
			{ 0, 255, 0 } ,{ 255, 128, 0 } ,{ 255, 255, 0 } ,
			{ 255, 0, 0 } ,{ 255, 0, 255 } 
		};

		// 时间
		DWORD dwTimeBegin, dwTimeEnd;
		dwTimeBegin = GetTickCount();

		// --识别-- 使用人脸的Haar特征分类器 cvHaarDetectObjects() / CvSeq是一个可增长的序列 CvSeq::total是指序列内部有效元素的个数
		//函数将返回CvSeq对象，该对象包含一系列CvRect表示检测到的人脸矩形
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);
		dwTimeEnd = GetTickCount();

		// 标记
		for (int i = 0; i < pcvSeqFaces->total; i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width * 0.5));
			center.y = cvRound((r->y + r->height * 0.5));
			radius = cvRound((r->width + r->height) * 0.25);
			cvCircle(pSrcImage, center, radius, FaceCirclecolors[i % 8], 2);
		}

		printf("人脸个数: %d   识别用时: %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);

		cvReleaseMemStorage(&pcvMStorage);
	}

	//创建窗口
	const char *pstrWindowsTitle = "人脸识别";
	cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);	
	cvShowImage(pstrWindowsTitle, pSrcImage);	//在指定窗口中显示图像 

	cvWaitKey(0);	//等待按键事件 <=0 无限等待

	cvDestroyWindow(pstrWindowsTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pGrayImage);
	return 0;
}









