#include "stdafx.h"
#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include<conio.h> 
 #define IMGDATA(image,i,j,k) (((uchar*)image->imageData)[(i)*(image->widthStep) + (j)*(image->nChannels) + (k)])	//extracts pixel information
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
		*IMGDATA(gscale,i,j,0) =(uchar)( 0.33*(*IMGDATA(img,i,j,0))+0.56*(*IMGDATA(img,i,j,1))+0.11*(*IMGDATA(img,i,j,2)));
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
  	IplImage* img, * gsc, *bin;
  	char *win1 = "image1";char *win2 = "image2"; char *win3="image3";
  	img = cvLoadImage("Lighthouse.jpg",1);
  	if(!img)
             printf("Could not load the image!\n");
    	else
        {
			 cvNamedWindow(win1,CV_WINDOW_AUTOSIZE);
     	     cvShowImage(win1,img);
    	     cvWaitKey(0);
  	}
	
  	cvDestroyWindow(win1);

	
	
			gsc=get_grayscale(img);
    	     cvNamedWindow(win2,CV_WINDOW_AUTOSIZE);
     	     cvShowImage(win2, gsc);
    	     cvWaitKey(0);
			 cvDestroyWindow(win2);

  	bin=get_binary(img,50);
	cvNamedWindow(win3,CV_WINDOW_AUTOSIZE);
	cvShowImage(win3, bin);
	cvWaitKey(0);
	cvDestroyWindow(win3);

	cvReleaseImage(&bin);
  	cvReleaseImage(&gsc);
	cvReleaseImage(&img);
  	
	
	getch();
  	
}

