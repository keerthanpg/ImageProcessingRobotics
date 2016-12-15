#include "stdafx.h"
#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include<conio.h>
 #define IMGDATA(image,i,j,k) (((uchar*)image->imageData)[(i)*(image->widthStep) + (j)*(image->nChannels) + (k)])	//extracts pixel information
int mx=0, my=0;

int chk=0; //Global variables to store image co-ordinates and the flag to check
#define TOLH 5
#define TOLS 100
#define TOLV 150

IplImage* colour_detect_HSV(IplImage* img, int hue, int sat, int val)
{
  IplImage* hsv; IplImage* result;
  int i,j,ht,wd;
  ht = img->height; wd = img->width;
  hsv = cvCreateImage(cvSize(wd,ht),IPL_DEPTH_8U,3); //The hsv intermediate is initialized
  result = cvCreateImage(cvSize(wd,ht),IPL_DEPTH_8U,1); //The result is initialized
  cvCvtColor(img,hsv,CV_BGR2HSV); //The HSV intermediate is created

  for(i=0;i<ht;i++)
  {
    for(j=0;j<wd;j++)
    {
      //The condition is enforced for the values of each channel as described
      if((IMGDATA(hsv,i,j,0)> hue-TOLH && IMGDATA(hsv,i,j,1)< hue+TOLH) && (IMGDATA(hsv,i,j,1)>sat-TOLS && IMGDATA(hsv,i,j,1)<sat+TOLS) && (IMGDATA(hsv,i,j,2)>val-TOLV&&IMGDATA(hsv,i,j,2)<val+TOLV))
        IMGDATA(result,i,j,0) = 255; //The necessary pixels are made white
      else
        IMGDATA(result,i,j,0) = 0; //The other pixels are made black
    }
  }
  return result;
}

void mouse_callback(int event, int x, int y, int flags, void* param)
{
	//This is called every time a mouse event occurs in the window
	if (event == CV_EVENT_LBUTTONDOWN) //This is executed when the left mouse button is clicked
	{ 
		//Co-ordinates of the left click are assigned to global variables and flag is set to 1
		mx = x; 
		my = y;
		chk = 1;
	}
}

int main()
{ 
CvCapture* capture = cvCreateCameraCapture(-1); //The streaming video is loaded into a pointer of type CvCapture
   IplImage* frame, *frhsv; //For each frame of the video
   char *win = "video_stream", *win2="hsv";
   int tolh, tols, tolv;
   
    cvNamedWindow(win,CV_WINDOW_AUTOSIZE); //To display the frames
	cvNamedWindow(win2,CV_WINDOW_AUTOSIZE);//Window created
	cvCreateTrackbar("htol",win2,&tolh,TOLH);
	cvCreateTrackbar("stol",win2,&tols,TOLS);
	cvCreateTrackbar("vtol",win2,&tolv,TOLV);
	
		cvSetMouseCallback(win,mouse_callback,0);
	while(1)
	{
		frame = cvQueryFrame(capture); //Image under consideration is captured as a shot of the video		
   cvShowImage(win,frame); //Frame is shown in the window 
   	
		if(chk)
			{
		break;}
		  
		char c = cvWaitKey(33); //This is to account for the frame speed of the loaded video
		if(c==27) //If the character of code 27 or the ESCAPE character is entered, the loop will break
			return 0;
	}
		frhsv = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U,1);
		cvCvtColor(frame,frhsv,CV_BGR2HSV); //Conversion of 'image' in BGR format to 'gscale' in gray-scale
		
		while(1)
		{   frhsv=colour_detect_HSV(frhsv, tolh, tols, tolv);
			cvShowImage(win2,frhsv);//Result is shown in window
			char c=cvWaitKey(0);
			if (c==27);
			break;
		}


			/*printf("The co-ordinates of the point are [%d,%d]\n",mx,my);
			printf("%d, %d, %d", IMGDATA(frame,mx,my,0), IMGDATA(frame,mx,my,1), IMGDATA(frame,mx,my,2));*/
                       
	cvReleaseImage(&frame); cvReleaseImage(&frhsv); //Images freed from memory
   cvDestroyWindow(win2); //Window is closed

	cvReleaseCapture(&capture); //Video is released from memory
	cvReleaseImage(&frame); //Image released from memory
	cvDestroyWindow(win); //Window closed

	
   	getch();
}


