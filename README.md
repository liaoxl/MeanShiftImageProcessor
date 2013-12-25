MeanShift Image Processor
=======

	MeanShiftImageProcessor - A modification with existing Meanshift Image Processor

	Origin Meanshift Image Processor - http://coewww.rutgers.edu/riul/research/code/EDISON/index.html

	https://github.com/liaoxl/MeanShiftImageProcessor
	Xiangli Liao(liaoxl2012@gmail.com)


### 1. Intorduction.

This is a modification with the public available source code, [EDISON](http://coewww.rutgers.edu/riul/research/code/EDISON/index.html)

The source code above is implemented in a MFC framework. It was not convenient for one which needs the algorithms only. So I made a soft modification.

References

	[1] D. Comanicu, P. Meer: "Mean shift: A robust approach toward feature space analysis".  IEEE Trans. Pattern Anal. Machine Intell., May 2002.  
	
	[2] P. Meer, B. Georgescu: "Edge detection with embedded confidence". IEEE Trans. Pattern Anal.  Machine Intell., 28, 2001.  
	
	[3] C. Christoudias, B. Georgescu, P. Meer: "Synergism in low level vision". 16th International Conference of Pattern Recognition, Track 1 - Computer Vision and Robotics, Quebec City, Canada, August 2001.


-----------------

### 2. Content.



-------------------

### 3. Example Usage

Sample code:

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

And results

<img src="moondark.jpg" align="left" />
<img src="Meanshift.png" align="right" />





