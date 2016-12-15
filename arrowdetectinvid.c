//Final code which will detect arrow from video and tell the direction

#include "stdafx.h"
#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>

#define IMGDATA(image,i,j,k) (((uchar *)image->imageData)[(i)*(image->widthStep) + (j)*(image->nChannels) + (k)])	//extracts pixel information


IplImage* binary(IplImage* img,int threshol)
{
	int i,j;
	IplImage *result;
	result = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	int B,G,R;
	for(i=0;i<img->height;i++)
		{for(j=0;j<img->width;j++)
		{
			B=IMGDATA(img,i,j,0);
			G=IMGDATA(img,i,j,1);
			R=IMGDATA(img,i,j,2);
		
	if(B>threshol&&G>threshol&&R>threshol)
	{
		IMGDATA(result,i,j,0)=255;
	}
	else
	{
		IMGDATA(result,i,j,0)=0;
	}
	}}
		return result;
}



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
		IMGDATA(gscale,i,j,0) = 0.33* IMGDATA(img,i,j,0)+0.56* IMGDATA(img,i,j,1)+0.11* IMGDATA(img,i,j,2);
		}
	}

	return gscale; 
}


int threshold(IplImage *img)
{
	int i,j;
	int a[256];
	for(i=0;i<256;i++)
	{
		a[i]=0;
	}
	int c=0;
	int w=((img->height)*(img->width));
	w=w/2;
	
	
	for(i=0;i<img->height;i++)
	{
		for(j=0;j<img->width;j++)
		{
			int v= IMGDATA(img,i,j,0);
			a[v]++;
		}
	}

	for(i=0;i<256;i++)
	{
		if(c>=w)
		{
			break;
		}
		else
		{
			c=c+a[i];
		}
	}

	return i;
}

int final(IplImage* img)
{
	int a,b;
	int m=1000;
	int no_white ;
	int countleft=0, countright=0;
	for(a=0;a<img->width;a++)
	{
		no_white=0;
		for(b=0;b<img->height;b++)
		{

			if(IMGDATA(img,b,a,0) == 255)
				{
					no_white++;
		     	}
		}
		if(no_white>m )
		{
			countleft++; countright=0;
			if(countleft>(img->width/3))
			{
				return 1;
			}
		}
		else if(no_white<m)
		{
			countleft=0; countright++;
			if(countright>(img->width/3))
				return(0);
		}	
			
			
		
		m=no_white;
	}
	

}


void main()
{
	


   CvCapture* capture = cvCreateCameraCapture(-1);
   IplImage* frame; //For each frame of the video
   char *win = "video_stream";
   char *win2 = "video_stream binary";
   cvNamedWindow(win,CV_WINDOW_AUTOSIZE); //To display the frames
   cvNamedWindow(win2,CV_WINDOW_AUTOSIZE);

   while(1)
   {
	//Each frame of video will be captured and displayed now
	frame = cvQueryFrame(capture);
	cvShowImage(win,frame); //Result shown

	IplImage* gray;
	int i,j,ht,wd; 
	ht = frame->height; wd = frame->width; 
	gray = cvCreateImage(cvSize(wd,ht),IPL_DEPTH_8U,1);
   
	gray=get_grayscale(frame);
	int threshol=threshold(gray);

	cvShowImage(win2,binary(frame,threshol));

	
		int x = final(binary(frame,threshol));
        if(x==0)
        {
	       printf("TURN RIGHT \n");
        }
        else
        {
	     printf("TURN LEFT \n");
        }
	


	char c = cvWaitKey(33);
	if(c==27) break;
   }

   cvReleaseCapture(&capture);
   cvReleaseImage(&frame);
   cvDestroyWindow(win);
}

