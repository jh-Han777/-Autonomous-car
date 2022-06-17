#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <cstdlib>

using namespace std;
using namespace cv;

int main(){
	Mat img=imread("tlight (1).jpg"); //영상입력 tlight (1) ~ tlight (3)
	resize(img,img,Size(640,480));
	Mat Detect_traffic =img.clone();
	Mat Detect_all = img.clone();
	Mat gray;
	cvtColor(img,gray,CV_BGR2GRAY);
	//imshow("gray",gray);
	//waitKey(0);

	Mat Thresh_Binary,Thresh_Adaptive,Thresh_Final;
	threshold(gray,Thresh_Binary,100,255,THRESH_BINARY_INV);
	//imshow("Normal_thresh",Thresh_Binary);
	//waitKey(0);

	adaptiveThreshold(gray,Thresh_Adaptive,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,3,5);
	//imshow("Adaptive_thresh",Thresh_Adaptive);
	//waitKey(0);
	
	bitwise_and(Thresh_Binary,Thresh_Adaptive, Thresh_Final);
	//imshow("Thresh_Final",Thresh_Final);
	//waitKey(0);

	//canny edge
	Mat canny;
	Canny(Thresh_Final,canny,100,300,3);
	//imshow("canny",canny);
	//waitKey(0);

	//find all contours
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny,contours,hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point());
	vector<vector<Point>> contours_All(contours.size());
	vector<Rect> boundRect(contours.size());
	
	for(int i=0;i<contours.size();i++){
		approxPolyDP(Mat(contours[i]),contours_All[i],1,true);
		boundRect[i] = boundingRect(Mat(contours_All[i]));
	}

	//refine contours
	vector<Rect> Rect_refined(contours.size());
	int refinerycount = 0, refine_constant=0;
	Mat refine_Gray,before_refine;
	Rect Rect_final;
	double ratio;
	for(int i =0;i<contours.size();i++){
		ratio = (double)boundRect[i].height/boundRect[i].width;
		before_refine = Detect_all(boundRect[i]);
		cvtColor(before_refine,refine_Gray,CV_BGR2GRAY);
		threshold(refine_Gray,refine_Gray,150,255,THRESH_BINARY);

		//검정색을 일정수준 보유해야 신호등으로 인식
		for(int y=0;y<before_refine.rows;y++){
			for(int x=0;x<before_refine.cols;x++){
				if(refine_Gray.at<uchar>(y,x)==0)
					refine_constant+=1;
			}
		}

		if(refine_constant>100){
			if((ratio<=0.6)&&(ratio>=0.3)&&(boundRect[i].area()>=300)&&(boundRect[i].area()<=800))
			{
				drawContours(Detect_all,contours,i,Scalar(0,0,0),1,8,hierarchy,0,Point());
				rectangle(Detect_all, boundRect[i].tl(), boundRect[i].br(), Scalar(255,0,0), 1, 8, 0);
				Rect_final = boundRect[i];
			}
		}
		refine_constant=0;
	}
	Mat traffic = Detect_all(Rect_final);
	

	//신호등 상태 파악
	Mat traffic_hsv;
	cvtColor(traffic,traffic_hsv,CV_BGR2HSV);

	//red
	Mat range_red1, range_red2,red;

	Scalar lower_red1(0,50,50);
	Scalar upper_red1(10,255,255);

	Scalar lower_red2(170,50,50);
	Scalar upper_red2(180,255,255);

	inRange(traffic_hsv,lower_red1,upper_red1,range_red1);
	inRange(traffic_hsv,lower_red2,upper_red2,range_red2);
	bitwise_or(range_red1, range_red2, red);
	

	threshold(red,red,100,255,THRESH_BINARY);

	int adjust_red=0;
	for(int y=0;y<red.rows;y++){
		for(int x=0;x<red.cols;x++){
			if(red.at<uchar>(y,x)==255)
				adjust_red+=1;
		}
	}
	if(adjust_red>=20)
		printf("빨간불입니다\n");
//imshow("red",red);
//waitKey(0);
	//green
	Mat green;

	Scalar lower_green(40, 50, 50);
	Scalar upper_green(70, 255, 255);

	inRange(traffic_hsv,lower_green,upper_green,green);
	
	threshold(green,green,100,255,THRESH_BINARY);

	int adjust_green=0;
	for(int y=0;y<green.rows;y++){
		for(int x=0;x<green.cols;x++){
			if(green.at<uchar>(y,x)==255)
				adjust_green+=1;
		}
	}
	if(adjust_green>=20){
		printf("초록불입니다\n");
//imshow("green",green);
	//waitKey(0);
	}
	//yellow
	Mat yellow;

	Scalar lower_yellow(15, 50, 60);
	Scalar upper_yellow(45, 255, 255);
	inRange(traffic_hsv,lower_yellow,upper_yellow,yellow);
	
	threshold(yellow,yellow,100,255,THRESH_BINARY);

	int adjust_yellow=0;
	for(int y=0;y<yellow.rows;y++){
		for(int x=0;x<yellow.cols;x++){
			if(yellow.at<uchar>(y,x)==255)
				adjust_yellow+=1;
		}
	}
	if(adjust_yellow>=20){
		printf("노란불입니다\n");
//imshow("yellow",yellow);
	//waitKey(0);
	}
	imshow("신호등 전체", Detect_all);
	//imshow("신호등 부분",traffic);
	waitKey(0);
	return 0;

}