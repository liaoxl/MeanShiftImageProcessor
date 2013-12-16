/*
 * msPro.cpp
 * Copyright (C) 2013 moondark <liaoxl2012@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "segm/msImageProcessor.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	Mat img=imread("moondark.jpg");
	imshow("Origin", img);

	int img_height=img.size().height;
	int img_width=img.size().width;

	uchar* ms_data=new uchar[img_height*img_width*3];
	uchar* ptr_ms_data=ms_data;
	uchar* data=img.data;

	for(int i=0; i<img_height; i++)
	{
		for(int j=0; j<img_width; j++)
		{
			*(ptr_ms_data++) = *(data++);
			*(ptr_ms_data++) = *(data++);
			*(ptr_ms_data++) = *(data++);
		}
	}

	msImageProcessor* msIP=new msImageProcessor();

	msIP->DefineImage(ms_data, COLOR, img_height, img_width);

	msIP->SetSpeedThreshold(0.1);
	msIP->FuseRegions(10, 50);

	RegionList* regionList=msIP->GetBoundaries();
    int* regionIndeces=regionList->GetRegionIndeces(0);
    int num_Regions=regionList->GetNumRegions();
    int boundary_Points_Count=0;

    for(int i=0; i<num_Regions; i++)
    {
        boundary_Points_Count += regionList->GetRegionCount(i);
    }

    int* tmp_x=new int[boundary_Points_Count];
    int* tmp_y=new int[boundary_Points_Count];
    for(int i=0; i<boundary_Points_Count; i++)
    {
        tmp_x[i]=regionIndeces[i]%img_width;
        tmp_y[i]=regionIndeces[i]/img_width;
    }

    Mat dst_img=img;
    for(int i=0; i<boundary_Points_Count; i++)
    {
        dst_img.at<Vec3b>(tmp_y[i], tmp_x[i])[0]=255;
        dst_img.at<Vec3b>(tmp_y[i], tmp_x[i])[1]=255;
        dst_img.at<Vec3b>(tmp_y[i], tmp_x[i])[2]=255;
    }

    imshow("Meanshift", dst_img);
    waitKey(0);

//    assert(label_count==num_Regions);

    cout << num_Regions << endl; 
    delete [] ms_data; 
	waitKey(0);
	return 0;
}

