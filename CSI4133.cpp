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

#include "stdafx.h"
#include "CSI4133.h"

using namespace cvb;

CSI4133::CSI4133(){
	vidOriginal = 0;
	vidProcessed = 0;
	thresh = 0;;
}

CSI4133::~CSI4133(){
	cvDestroyAllWindows();
	if (vidOriginal)
		delete vidOriginal;
	if (vidProcessed)
		delete vidProcessed;
}

bool CSI4133::loadVideoPath(CString * _path){
	CFileDialog dlg(TRUE, _T("*.avi"), NULL, OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("video files (*.avi; *.mpeg) |*.avi;*.mpeg|All Files (*.*)|*.*||"),NULL);
	dlg.m_ofn.lpstrTitle= _T("Open Video");

	if (dlg.DoModal() == IDOK) {
		*_path = dlg.GetPathName();
		return true;
	} else {
		return false;
	}
}

bool CSI4133::saveVideoPath(CString * _path){
	CFileDialog dlg(TRUE, _T("*.avi"), NULL, OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("video files (*.avi; *.mpeg) |*.avi;*.mpeg|All Files (*.*)|*.*||"),NULL);
	dlg.m_ofn.lpstrTitle= _T("save Video");

	if (dlg.DoModal() == IDOK) {
		*_path = dlg.GetPathName();
		return true;
	} else {
		return false;
	}
}

bool CSI4133::loadVideo(CString * _str){
	if (loadVideoPath(_str)){
		if (vidOriginal)
			delete vidOriginal;
		if (vidProcessed)
			delete vidProcessed;
		
		CvCapture *tmpCap = cvCaptureFromAVI(*_str);

		vidOriginal = new ImgArr(tmpCap);
		vidProcessed = new ImgArr(vidOriginal);

		cvReleaseCapture(&tmpCap);

		return true;
	} else {
		return false;
	}
}

void CSI4133::showVideo(ImgArr * _arr, CString _title){
	int key = 0;
	if (_arr){
		for (int i = 0; i < _arr->nFrames && key != 'q'; i++){
			cvShowImage(_title, _arr->frames[i]);
			key = cvWaitKey(1000/_arr->fps);
		}
	}else{
		MessageBox(NULL, "Video not yet loaded","Error", MB_OK);
	}
}

void CSI4133::showImage(CString _name, IplImage * _img){
	if (_img)
		cvShowImage(_name, _img);
	else
		MessageBox(NULL, "Image cannot be shown: not yet loaded","Error", MB_OK);
}

void CSI4133::trackbarChange(int _val1, void * _val2){
	((CSI4133*)_val2)->processTest();
}

void CSI4133::processTest(){
	 CvCapture *capture = 0;
    IplImage  *frame = 0;
    int       key = 0;
 
    /* initialize camera */
    capture = cvCaptureFromCAM( 0 );
 
    /* always check */
    if ( !capture ) {
        fprintf( stderr, "Cannot open initialize webcam!\n" );
        
    }
 
    /* create a window for the video */
    cvNamedWindow( "result", CV_WINDOW_AUTOSIZE );
 
    while( key != 'q' ) {
        /* get a frame */
        frame = cvQueryFrame( capture );
 
        /* always check */
        if( !frame ) break;
       IplImage *imgFrame = cvCreateImage( cvSize((int)(frame->width*0.2) , (int)(frame->height*0.2 )),
                                     frame->depth, frame->nChannels );
			cvResize(frame, imgFrame);

		DetectBlobs(imgFrame,imgFrame,CV_RGB(0,255,0));

        /* display current frame */
        cvShowImage( "result", imgFrame );
 
        /* exit if user press 'q' */
        key = cvWaitKey( 1 );
    }
 
    /* free memory */
    cvDestroyWindow( "result" );
    cvReleaseCapture( &capture );
 
}

void CSI4133::updateSlider(){
	
	if (vidOriginal){
		
		
		
	}else{
		MessageBox(NULL, "Video not yet loaded","Error", MB_OK);
	}
}

void CSI4133::processVideo(){
	
	if (vidOriginal && vidProcessed){
		vidProcessed->clearFrames();
			
		
		int key =0;
		//Loop through each frame of the video and process
		for (int frame =0;frame < vidOriginal->nFrames;frame++)
		{	
		
			//Create a Clone of the current frame. To be used as the source.
			IplImage* imgFrame = cvCloneImage(vidOriginal->frames[frame]); 
			/*IplImage *imgFrame = cvCreateImage( cvSize((int)(vidOriginal->frames[frame]->width*0.2) , (int)(vidOriginal->frames[frame]->height*0.2 )),
                                     vidOriginal->frames[frame]->depth, vidOriginal->frames[frame]->nChannels );
			cvResize(vidOriginal->frames[frame], imgFrame);
*/
			//Create a clone of the current frame. To be used to store processed result
			IplImage* imgFrameProcessed = cvCloneImage(vidOriginal->frames[frame]);
			
			//Create a temp image to hold temporarily processed data
			IplImage* imgProcessed;
			
			/*
				For each desired color, call IsolateHueSat to retriece an image containing only
				pixels meeting the specified criteria for that colour and store it in the temp image. 

				Call DetectBlobs with the temp image to detect and identify all blobs in the temp image.
				If the criteria specified in the call to IsolateHueSat is correct, the blobs detected
				will only be of the desired colour. 
			*/
			
			//Red
			imgProcessed = IsolateHueSat(imgFrame, 115,150,145,255,0,255,3,6);
			imgProcessed = DetectBlobs(imgProcessed,imgFrameProcessed,CV_RGB(255,0,0));	
			//Green
			imgProcessed = IsolateHueSat(imgFrame,71,75,50,255,50,255,3,4);
			imgProcessed = DetectBlobs(imgProcessed,imgFrameProcessed,CV_RGB(0,255,0));	
			//Yellow
			imgProcessed = IsolateHueSat(imgFrame,100,105,130,255,100,255,3,4); 
			imgProcessed = DetectBlobs(imgProcessed,imgFrameProcessed,CV_RGB(255,255,0));	
			//Dark Blue
			imgProcessed = IsolateHueSat(imgFrame,20,22,0,255,57,255,1,7);
			imgProcessed = DetectBlobs(imgProcessed,imgFrameProcessed,CV_RGB(0,0,255));	

			//Black
			imgProcessed = IsolateHueSat(imgFrame,20,26,0,255,0,31,3,13);
			imgProcessed = DetectBlobs(imgProcessed,imgFrameProcessed,CV_RGB(0,0,0));	

			//show frame after processing. This will not be in real time 
			cvShowImage("Processing Video... Pleas Wait.", imgFrameProcessed);
			
			key = cvWaitKey(1000/vidOriginal->fps);	
			
			//add processed frame to the processed video
			vidProcessed->addFrame(imgFrameProcessed);
			
			//Release images			
			cvReleaseImage(&imgFrame);
			cvReleaseImage(&imgFrameProcessed); 
			//cvReleaseImage(&imgProcessed);  // why do you crash when I include this line?
		}
		//show video after processing all frames
		showVideo(vidProcessed, "Processed Video");
	} else {
		MessageBox(NULL, "Video not yet loaded","Error", MB_OK);
	}	
}

void CSI4133::saveVideo(ImgArr * _arr){
	CString path;
	CvVideoWriter * writer;
	if (vidOriginal && vidProcessed){
		if (saveVideoPath(&path)){
			CvSize dim = cvSize(_arr->frmWidth, _arr->frmHeight);
			int tempDepth = _arr->frmDepth;
			if(writer = cvCreateVideoWriter(path, -1, vidOriginal->fps, dim)){
				for (int i = 0 ; i < _arr->nFrames;i++)
					cvWriteFrame(writer, _arr->frames[i]);
				cvReleaseVideoWriter(&writer);
			}
		}
	} else{
		MessageBox(NULL, "Video not yet loaded","Error", MB_OK);
	}
}

void CSI4133::saveProcessedVideo(){
	saveVideo(vidProcessed);
}


IplImage* CSI4133::IsolateHueSat(IplImage* imgFrame, int minHue, int maxHue, int minSat, int maxSat, int minVal,int maxVal, int numErodes, int numDilates ){
				
		IplImage* imgHSV = cvCreateImage(cvGetSize(imgFrame), imgFrame->depth , 3);
		cvCvtColor(imgFrame, imgHSV, CV_RGB2HSV);
		IplImage* imgTemp =  cvCreateImage(cvGetSize(imgFrame), imgFrame->depth , 3);
		IplImage* imgRGB =  cvCreateImage(cvGetSize(imgFrame), imgFrame->depth , 3);

		int i = 0;
		int width = imgHSV->width;
		int height = imgHSV->height;
		for (int i = 0; i < width; i++) //loop through rows of pixels
		{

          // process each pixel

          for (int j = 0; j < height; j++)
          {
			
				CvScalar s = cvGet2D(imgHSV,j,i);
				
				if (s.val[0] > minHue && s.val[0] < maxHue && s.val[1] > minSat && 
					s.val[1] < maxSat && s.val[2] > minVal && s.val[2] < maxVal){ //check hue, sat, and Val against desired min and max
				
					cvSet2D(imgTemp,j,i,s); //add scalar to temp image
					
				}
				else
				{
					CvScalar t = CvScalar();
					cvSet2D(imgTemp,j,i,t); //add default scalar
				}
			
				
				
			}
		}
		cvCvtColor(imgTemp, imgRGB, CV_HSV2RGB);

		//dilate and erode image based on method parameters. If numDilates == numErodes a closer is performed.
		cvDilate(imgRGB,imgRGB,0,numDilates);
		cvErode(imgRGB,imgRGB,0,numErodes);
	
		//Release Images/Memort
		cvReleaseImage(&imgTemp); 
		//cvReleaseImage(&imgRGB);
		cvReleaseImage(&imgHSV);
		
		return imgRGB;
}

IplImage* CSI4133::DetectBlobs(IplImage* src, IplImage* dst,CvScalar recColor)
{
			
			//Create a GRAY scale image to be used for blob detection. cvBlob only works on gray scale images
			IplImage *gray = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
			cvCvtColor(src, gray, CV_BGR2GRAY);
			cvThreshold(gray, gray, 0, 255, CV_THRESH_BINARY);
			
			showImage("Gray",gray);

			//use cvBlob to detect all blobs in the image. 
			IplImage *labelImg=cvCreateImage(cvGetSize(gray), IPL_DEPTH_LABEL, 1);
			CvBlobs blobs;
			unsigned int result=cvLabel(gray, labelImg, blobs);
			
			/*Iterate over each blob and add a rectangle with colour equal to recColor 
			  and dimensions equal to the the bounding rectagle of the blob to the dst image. 
			  If the bounding dimensions are too small (noise) ignore the blob. 
			*/
			int x = 0;
			for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
			{
			
				CvPoint p1,p2;
				p1.x =it->second->maxx;
				p1.y =it->second->maxy;

				p2.x =it->second->minx;
				p2.y =it->second->miny;
				cvRectangle(dst, p1, p2, recColor, 1);
				x = x+1;
				
  			}
			
			//cvPutText(dst,reinterpret_cast<char *>(5),cvPoint(0,0), CV_FONT_HERSHEY_SIMPLEX, cvScalar(255,255,0));

			//Release Images. 
			cvReleaseBlobs (blobs);
			cvReleaseImage(&gray);
			cvReleaseImage(&labelImg);
			return dst;
}