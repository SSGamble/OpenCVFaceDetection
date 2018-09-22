//#include<iostream>  
//#include <opencv2/core/core.hpp>  
//#include <opencv2/highgui/highgui.hpp>  
//
//using namespace cv;
//
//int main()
//{
	// OpenCV��ʹ��Mat�������洢�����ͼƬ����
//	// ����һ��ͼƬ����Ϸԭ����  
//	Mat img = imread("pic.jpg");
//
//	// ����һ����Ϊ "��Ϸԭ��"����  
//	namedWindow("��Ϸԭ��");
//
//	// �ڴ�������ʾ��Ϸԭ��  
//	imshow("��Ϸԭ��", img);
//
//	// �ȴ�6000 ms�󴰿��Զ��ر�  
//	waitKey(6000);
//}
//

///////////////////////////////////////////////////////////////////////////

// Haar������� - ����ʶ��
#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
using namespace std;
int main()
{
	// ����Haar������������
	// haarcascade_frontalface_alt.xml�� OpenCV �Դ��ķ����� -- �ļ�·��
	const char *pstrCascadeFileName = "haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade *pHaarCascade = NULL;
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);

//���ļ��ж�ȡͼ�� 
	const char *pstrImageName = "6.jpg";
	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
	
	// תΪ�Ҷ�ͼ 
	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);

	// ����ʶ������
	if (pHaarCascade != NULL)
	{
		//opencv�ڴ���������Լ���Ƶ���������һ���ڴ�洢������ͳһ������ֶ�̬������ڴ�
		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
		cvClearMemStorage(pcvMStorage);

		CvScalar FaceCirclecolors[] =
		{
			{ 0, 0, 255 } ,{ 0, 128, 255 } ,{ 0, 255, 255 } ,
			{ 0, 255, 0 } ,{ 255, 128, 0 } ,{ 255, 255, 0 } ,
			{ 255, 0, 0 } ,{ 255, 0, 255 } 
		};

		// ʱ��
		DWORD dwTimeBegin, dwTimeEnd;
		dwTimeBegin = GetTickCount();

		// --ʶ��-- ʹ��������Haar���������� cvHaarDetectObjects() / CvSeq��һ�������������� CvSeq::total��ָ�����ڲ���ЧԪ�صĸ���
		//����������CvSeq���󣬸ö������һϵ��CvRect��ʾ��⵽����������
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);
		dwTimeEnd = GetTickCount();

		// ���
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

		printf("��������: %d   ʶ����ʱ: %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);

		cvReleaseMemStorage(&pcvMStorage);
	}

	//��������
	const char *pstrWindowsTitle = "����ʶ��";
	cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);	
	cvShowImage(pstrWindowsTitle, pSrcImage);	//��ָ����������ʾͼ�� 

	cvWaitKey(0);	//�ȴ������¼� <=0 ���޵ȴ�

	cvDestroyWindow(pstrWindowsTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pGrayImage);
	return 0;
}









