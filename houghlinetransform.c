//CODE FOR HOUGH LINE TRANSFORMATION

#include "stdafx.h"
#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include<conio.h>
#include<math.h>
#define TOLH 5
#define TOLS 100
#define TOLV 150
int mousex,mousey,chk;
struct coord
{int x,y;
}cent;
#define IMGDATA(image,i,j,k) (((uchar*)image->imageData)[(i)*(image->widthStep) + (j)*(image->nChannels) + (k)])	//extracts pixel informatio
void mouse_callback(int event, int x, int y, int flags, void* param)
{
	//This is called every time a mouse event occurs in the window
	if (event == CV_EVENT_LBUTTONDOWN) //This is executed when the left mouse button is clicked
	{ 
		//Co-ordinates of the left click are assigned to global variables and flag is set to 1
		mousex = x; 
		mousey = y;
		chk = 1;
	}
}



IplImage* houghtransform(IplImage* edge, int x, int y)			
{
	int ht=edge->height, wd=edge->width;
	IplImage*circle=cvCreateImage(cvSize(400,200),IPL_DEPTH_8U,1);

	int a[400];
	int i, j;
	for(i=0;i<100;i++)
		a[i]=0;
	float max_r=(int)sqrt((float)(ht*ht+wd*wd));
	
	
	int max=0;
	for(i=0;i<ht;i++)
		{
		for(j=0;j<wd;j++)
			{
				if(IMGDATA(edge,i,j,0)==255)
				{
						float r=sqrt((float)((x-j)*(x-j)+(y-i)*(y-i)));						
						a[int(r*200/max_r)]++;
				}

				
		}

	}
	max=0;
	for(i=0;i<200;i++)
		if(max<a[i])
			max=a[i];

	
	for(i=0;i<200;i++)
	{
		j=(int)(a[i]*400/max);
		for(int k=399;k>=0;k--)
					if(k>399-j)
						IMGDATA(circle,i,k,0)=0;
					else IMGDATA(circle,i,k,0)=255;



	}
	return circle;
}
void get_coordcent(IplImage* img)
{	
IplImage *hsv, *bin;
int tolh, tols, tolv;
int i, j, ht, wd;
char *win3="hsv";
ht=img->height;
wd=img->width;
hsv=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);
bin=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
cvCvtColor(img,hsv,CV_BGR2HSV);
cvNamedWindow(win3);

int hue=IMGDATA(hsv,mousey,mousex,0);
int sat=IMGDATA(hsv,mousey,mousex,1);
int val=IMGDATA(hsv,mousey,mousex,2);
cvCreateTrackbar("tolh",win3,&tolh,TOLH);
cvCreateTrackbar("tols",win3,&tols,TOLS);
cvCreateTrackbar("tolv",win3,&tolv,TOLV);

for(i=0;i<ht;i++)
{
	for(j=0;j<wd;j++)
	{
		if((IMGDATA(hsv,i,j,0)> hue-tolh && IMGDATA(hsv,i,j,1)< hue+tolh) && (IMGDATA(hsv,i,j,1)>sat-tols && IMGDATA(hsv,i,j,1)<sat+tols) && (IMGDATA(hsv,i,j,2)>val-tolv&&IMGDATA(hsv,i,j,2)<val+tolv))
        IMGDATA(bin,i,j,0) = 255; //The necessary pixels are made white
      else
        IMGDATA(bin,i,j,0) = 0; //The other pixels are made black


  
}



void main()
{ 
	IplImage *frame, *gscale,*edge;
char *win="edge", *win2="circle";
frame=cvLoadImage("circle.png",1);
gscale=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
edge=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
cvNamedWindow(win2,CV_WINDOW_AUTOSIZE);
cvNamedWindow(win,CV_WINDOW_AUTOSIZE);
IplImage* circle;
cvCvtColor(frame, gscale,CV_BGR2GRAY);
	cvSmooth(gscale,gscale,CV_GAUSSIAN,3,0,0,0);
	cvCanny(gscale,edge,100,210);
	get_coordcent(frame);
	circle=houghtransform(edge,cent.x,cent.y);
	cvShowImage(win,edge);
	cvShowImage(win2,circle);
	cvReleaseImage(&frame);
	cvWaitKey(0);
cvReleaseImage(&gscale);
cvReleaseImage(&circle);
cvDestroyWindow(win2);
cvDestroyWindow(win);

	/*CvCapture* capture=cvCreateCameraCapture(-1);
IplImage *frame, *gscale,*edge;
char *win="edge", *win2="linedet";
frame=cvQueryFrame(capture);
gscale=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
edge=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
IplImage* linedet=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
int ht=frame->height, wd=frame->width;

cvNamedWindow(win2,CV_WINDOW_AUTOSIZE);
cvNamedWindow(win,CV_WINDOW_AUTOSIZE);
while(1)
{
	frame=cvQueryFrame(capture);
	cvCvtColor(frame, gscale,CV_BGR2GRAY);
	cvSmooth(gscale,gscale,CV_GAUSSIAN,3,0,0,0);
	cvCanny(gscale,edge,100,210);
	linedet=houghtransform(edge);
	cvShowImage(win,edge);
	cvShowImage(win2,linedet);
	char c=cvWaitKey(55);
	if(c==27)
		break;
}
cvReleaseImage(&frame);
cvReleaseImage(&gscale);
cvReleaseImage(&linedet);
cvDestroyWindow(win2);
cvDestroyWindow(win);
cvReleaseCapture(&capture);
*/

getch();
}



	