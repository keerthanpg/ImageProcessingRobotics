#include "stdafx.h"
#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include<conio.h> 
 #define IMGDATA(image,i,j,k) ((uchar *)&image->imageData[(i)*(image->widthStep) + (j)*(image->nChannels) + (k)])	//extracts pixel information
IplImage* get_grayscale(IplImage* img)
{
	IplImage* gscale; //To store and return the result
	int i,j,ht,wd; 
	ht = img->height; wd = img->width; 
	gscale = cvCreateImage(cvSize(wd,ht),IPL_DEPTH_8U,1); //Resultant image initialized

	for(i=0;i<ht;i++)
	{
		for(j=0;j<wd;j++)
		{
		//Conversion formula for gray-scale is applied as had been discussed
		*IMGDATA(gscale,i,j,0) = 0.33*(*IMGDATA(img,i,j,0))+0.56*(*IMGDATA(img,i,j,1))+0.11*(*IMGDATA(img,i,j,2));
		}
	}

	return gscale; //Result returned
}
IplImage* get_binary(IplImage* img, int thresh){

	IplImage* bin; //To store and return the result
	int i,j,ht,wd;
	ht = img->height; wd = img->width; 
	bin = cvCreateImage(cvSize(wd,ht),IPL_DEPTH_8U,1);

	for(i=0;i<ht;i++)
	{
		for(j=0;j<wd;j++)
		{
		//It is checked if the gray-scale equivalent is larger than the threshold or not 
		if((0.33*(*IMGDATA(img,i,j,0))+0.56*(*IMGDATA(img,i,j,1))+0.11*(*IMGDATA(img,i,j,2))) > thresh)
			*IMGDATA(bin,i,j,0) = 255;//Assigned white
		else
			*IMGDATA(bin,i,j,0) = 0;//Assigned black
		}
	}

	return bin; //Result is returned
}
void main(){
  	 int thresh;
  	  	CvCapture* capture = cvCreateCameraCapture(-1); //The streaming video is loaded into a pointer of type CvCapture
   IplImage* frame1, *frame2, *frame3; //For each frame of the video
   char *win1 = "video_stream1", *win2="grayscale", *win3="binary";
   cvNamedWindow(win1,CV_WINDOW_AUTOSIZE); //To display the frames
   cvNamedWindow(win2,CV_WINDOW_AUTOSIZE); //To display the frames
   cvNamedWindow(win3,CV_WINDOW_AUTOSIZE); //To display the frames
   while(1)
   {
	//Each frame of video will be captured and displayed now
	frame1 = cvQueryFrame(capture);
	cvShowImage(win1,frame1); //Result shown
	frame2=get_grayscale(frame1);
	//Each frame of video will be captured and displayed now
	
	cvShowImage(win2,frame2); //Result shown
	
	//Each frame of video will be captured and displayed now
	cvCreateTrackbar("damn", win3, &thresh, 255);
	frame3=get_binary(frame1, thresh);
	cvShowImage(win3,frame3); //Result shown
	
	char c = cvWaitKey(33);
	if(c==27) break;
   }
   
   cvDestroyWindow(win1);
   cvDestroyWindow(win2);
   cvDestroyWindow(win3);
  	
	
	getch();
  	
}