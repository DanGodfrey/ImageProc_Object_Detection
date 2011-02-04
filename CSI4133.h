/*
Name: Daniel Godfrey
Student Number: 4910083
References:
[Site] http://code.google.com/p/cvblob/wiki/
[Site] flassari.is (http://flassari.is/2008/11/line-line-intersection-in-cplusplus/) - Inspired Line Intercection Method
[Book] Geometry and Discrete Mathematics (Addison - Wesley) - Inspired Line Intercection Method
[Site] Random Noise (http://blog.weisu.org/2007/12/opencv-detect-circles-with-hough.html) - Inspired Circle Detection Method
[Site] OSDir (http://osdir.com/ml/lib.opencv/2005-12/msg00504.html) - Helped when I was considering using Sobel. Does not appear in final solution.
[Site] OpenCVWiki (http://opencv.willowgarage.com/documentation/feature_detection.html) - Inspired Edge Detection Method

*/
#ifndef CSI4133_H
#define CSI4133_H

#include "cv.h"
#include "highgui.h"
#include "cvblob.h"

class ImgArr{
public:
	int fps;
	int frmWidth;
	int frmHeight;
	int frmDepth;
	int nFrames;
	int fourCC;
	IplImage ** frames;

	ImgArr(ImgArr * _arr){
		fps = _arr->fps;
		frmWidth = _arr->frmWidth;
		frmHeight = _arr->frmHeight;
		frmDepth = _arr->frmDepth;
		fourCC = _arr->fourCC;

		nFrames = 0;
		frames = 0;
	}

	ImgArr(CvCapture * _cap){
		nFrames = (int)cvGetCaptureProperty(_cap, CV_CAP_PROP_FRAME_COUNT);
		fps = (int)cvGetCaptureProperty(_cap, CV_CAP_PROP_FPS);
		frmWidth = (int)cvGetCaptureProperty(_cap, CV_CAP_PROP_FRAME_WIDTH);
		frmHeight = (int)cvGetCaptureProperty(_cap, CV_CAP_PROP_FRAME_HEIGHT);
		frmDepth = -1;
		fourCC = (int)cvGetCaptureProperty(_cap, CV_CAP_PROP_FOURCC);

		frames = new IplImage *[nFrames];

		for (int i = 0; i < nFrames;i++){
			IplImage * tmpImg = cvQueryFrame(_cap);
			frmDepth = tmpImg->depth;
			frames[i] = cvCloneImage(tmpImg);
		}
	}
	void clearFrames(){
		if (frames){
			for (int i = 0 ; i < nFrames; i++)
				cvReleaseImage(&frames[i]);
			delete [] frames;
		}
		frames = 0;
		nFrames = 0;
	}
	~ImgArr(){
		clearFrames();
	}
	void addFrame(IplImage * _img){
		IplImage ** tmpFrames = new IplImage * [nFrames+1];

		for (int i = 0; i < nFrames; i++){
			tmpFrames[i] = frames[i];
		}
		tmpFrames[nFrames] = cvCloneImage(_img);

		delete [] frames;

		frames = tmpFrames;
		nFrames++;
	}
};


class CSI4133{
private:
public:
	ImgArr * vidOriginal;
	ImgArr * vidProcessed;

	CString path;

	int thresh;

	CSI4133();
	~CSI4133();

	bool loadVideoPath(CString * _path);
	bool saveVideoPath(CString * _path);
	bool loadVideo(CString * _str);
	void saveVideo(ImgArr * _arr);
	void saveProcessedVideo();
	void showVideo(ImgArr * _arr, CString _title);
	void showImage(CString _name, IplImage * _img);
	static void trackbarChange(int _val1, void * _val2);
	void processTest();
	void updateSlider();

	void processVideo();
	IplImage* IsolateHueSat(IplImage* imgFrame, int minHue, int maxHue, int minSat=0, int maxSat=255,int minVal=0, int maxVal =255, int numErodes=1, int numDilates=1);
	IplImage* DetectBlobs(IplImage* src, IplImage* dst,CvScalar recColor);

	CString getPath(){return path;}
	
};

#endif