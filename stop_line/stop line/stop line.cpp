#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

int main(){
	Mat img = imread("lane (7).jpg");//영상입력 lane (1) ~ lane (17)
	resize(img,img,Size(640,480));
	Mat detect= cvCreateMat(img.rows,img.cols,CV_8UC3);

	for(int y=img.rows*5/12; y<img.rows*4/5;y++){
		for(int x=img.cols/4;x<img.cols*3/4;x++){
			for(int k=0;k<3;k++){
				detect.at<Vec3b>(y,x)[k]=img.at<Vec3b>(y,x)[k];
			}
		}
	}
	//imshow("detect",detect);
	//waitKey(0);

	//hsv변환
	Mat detect_hsv;
	cvtColor(detect,detect_hsv,CV_BGR2HSV);
	
	Scalar lower_white(0, 0, 210);
	Scalar upper_white(255, 50, 255);

	inRange(detect_hsv,lower_white,upper_white,detect_hsv);

	//imshow("detect_hsv",detect_hsv);
	//waitKey(0);

	//thresh
	Mat W_thresh;
	threshold(detect_hsv,W_thresh,120,255,THRESH_BINARY);

	//imshow("W_thresh",W_thresh);
	//waitKey(0);

	//정지선 검출
	int detect_constant=0;
	Mat final=Mat::zeros(img.rows,img.cols,CV_8UC1);
	for(int y=0; y<img.rows;y++){
		for(int x=0;x<img.cols;x++){
			if(W_thresh.at<uchar>(y,x)==255){
				final.at<uchar>(y,x)=255;
				detect_constant+=1;
			}
			if(W_thresh.at<uchar>(y,x)==0)
			{
				if(detect_constant<80){
					for(int z = detect_constant;z>=0;z--)
					{
						final.at<uchar>(y,x-z)=0;
					}
			}

					detect_constant=0;
			}
		}
		detect_constant=0;
	}

	for(int k=0;k<3;k++){
		dilate(final,final,Mat(),Point(-1,-1));
		bitwise_and(final,W_thresh,final);
	}

	//imshow("final",final);
	//waitKey(0);

	//결과 출력
	Mat result =img.clone();

	for(int y=0; y<img.rows;y++){
		for(int x=0;x<img.cols;x++){
			if(final.at<uchar>(y,x)==255){
				result.at<Vec3b>(y,x)[0] =255;
				result.at<Vec3b>(y,x)[1] =0;
				result.at<Vec3b>(y,x)[2] =255;
			}
		}
	}
	int distinction=0;
	for(int y=0; y<img.rows;y++){
		for(int x=0;x<img.cols;x++){
			if(final.at<uchar>(y,x)==255)
				distinction++;
		}
	}
	if(distinction<80)
		printf("No stop line\n");

	imshow("result",result);
	waitKey(0);

	return 0;
}
	
