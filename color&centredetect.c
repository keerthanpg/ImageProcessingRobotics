#include "stdafx.h"
#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include<conio.h> 


 #define IMGDATA(image,i,j,k) (((uchar*)image->imageData)[(i)*(image->widthStep) + (j)*(image->nChannels) + (k)])	//extracts pixel informationormation
/*IplImage* get_grayscale(IplImage* img)
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
}*/
/*IplImage* get_binary(IplImage* img, int thresh){

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
}*/
int sum1=0; int sum2=0;
IplImage* get_framebindet(IplImage* img, int thresh1, int thresh2, int thresh3, int tol1, int tol2, int tol3)
{
	sum1=sum2=0;
	IplImage* bindet;
	int i, j, ht, wd;int count=0;
	ht=img->height; wd=img->width;
	bindet=cvCreateImage(cvSize(wd, ht), IPL_DEPTH_8U, 1);
	for(i=0; i<ht; i++)
	{
		for(j=0; j<wd;j++)
		{
			if(IMGDATA(img,i,j,0)<thresh1+tol1 && IMGDATA(img,i,j,0)>thresh1-tol1&&IMGDATA(img,i,j,1)<thresh2+tol2 && IMGDATA(img,i,j,1)>thresh2-tol2&&IMGDATA(img,i,j,2)<thresh3+tol3 && IMGDATA(img,i,j,2)>thresh3-tol3)
				{count++;
					IMGDATA(bindet,i,j,0)=255;
					sum1+=i;
					sum2+=j;
			}
			else
				IMGDATA(bindet,i,j,0)=0;
		}
	}
	if(count)
	{
	sum1=sum1/count;
	sum2=sum2/count;
	}
	printf("sum1 and sum2 are %d and %d\n",sum1,sum2);
	//}
	//else printf( "\ncolor not detected");
	return bindet;
}


void main(){
  	 int thresh1=0, thresh2=0, thresh3=0;
	 int tol1=0, tol2=0, tol3=0;
	 int maxtolb=50, maxtolg=50, maxtolr=50;
  	  	CvCapture* capture = cvCreateCameraCapture(-1); //The streaming video is loaded into a pointer of type CvCapture
   IplImage* frame1, *frame2, *frame3; //For each frame of the video
   char *win1 = "video_stream1", *win2="grayscale", *win3="binary";
   cvNamedWindow(win1,CV_WINDOW_AUTOSIZE); //To display the frames
   cvNamedWindow(win2,CV_WINDOW_AUTOSIZE); //To display the frames
   cvNamedWindow(win3,CV_WINDOW_AUTOSIZE); //To display the frames
   cvCreateTrackbar("blue", win2, &thresh1, 255);
	cvCreateTrackbar("green", win2, &thresh2, 255);
	cvCreateTrackbar("red", win2, &thresh3, 255);
	cvCreateTrackbar("tolb", win2,&tol1, maxtolb);
	cvCreateTrackbar("tolg", win2, &tol2, maxtolg);
	cvCreateTrackbar("tolr", win2, &tol3, maxtolr);
   while(1)
   {
	//Each frame of video will be captured and displayed now
	frame1 = cvQueryFrame(capture);
	cvShowImage(win1,frame1); //Result shown
	

	frame2=get_framebindet(frame1, thresh1, thresh2, thresh3, tol1, tol2, tol3);
	//cout<<sum1<<","<<sum2;
	printf("%d, %d\n", sum2, sum1);
	cvShowImage(win2,frame2); //Result shown