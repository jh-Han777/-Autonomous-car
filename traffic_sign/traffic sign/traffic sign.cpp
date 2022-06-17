#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/legacy/legacy.hpp>

using namespace std;
using namespace cv;

bool dist(const DMatch &m){
	return  (m.distance<170 || m.distance>260);
}

bool eras(const DMatch &m){
	return (m.distance>0);
}
int main(int argc, char** argv[]) {

  Mat scene = imread("sign (1).jpg",0); // 영상입력 sign (1) ~ sign (8)
  
  //입력된 표지판
  Mat img1 = imread("방지턱 주의.jpg",0);
  Mat img2 = imread("천천히.jpg",0);
  Mat img3 = imread("보행자 주의.jpg",0);
  Mat img4 = imread("속도제한 50.jpg",0);
  Mat img5= imread("양보.jpg",0);
  Mat img6 = imread("우회전 금지.jpg",0);
  Mat img7 = imread("우회전 주의.jpg",0);
  Mat img8 = imread("위험.jpg",0);
  Mat img9 = imread("정지.jpg",0);
  Mat img10 = imread("좌회전 금지.jpg",0);
  Mat img11 = imread("좌회전 주의.jpg",0);
  Mat img12 = imread("직진금지.jpg",0);
  Mat img13 = imread("진입금지.jpg",0);
  Mat img14 = imread("통행금지.jpg",0);
  
  Mat scene2 = scene.clone();
  Mat scene3 = scene.clone();
  Mat scene4 = scene.clone();
  Mat scene5 = scene.clone();
  Mat scene6 = scene.clone();
  Mat scene7 = scene.clone();
  Mat scene8 = scene.clone();
  Mat scene9 = scene.clone();
  Mat scene10 = scene.clone();
  Mat scene11 = scene.clone();
  Mat scene12 = scene.clone();
  Mat scene13 = scene.clone();
  Mat scene14= scene.clone();

  //sift 선언
  SiftFeatureDetector detector(400);
  SiftDescriptorExtractor extractor;

 //천천히
// keypoint 출력
vector<KeyPoint> keypoints1, keypoints2;
detector.detect(img2, keypoints1); // 표지판 '천천히'입력
detector.detect(scene, keypoints2); // 찾고자 하는 배경 입력

// computing descriptors
Mat descriptors1, descriptors2;
extractor.compute(img2, keypoints1, descriptors1);
extractor.compute(scene, keypoints2, descriptors2);

// matching descriptors
BruteForceMatcher<L2<float>> matcher1;
vector<DMatch> matches1;
matcher1.match(descriptors1, descriptors2, matches1);
matches1.erase(std::remove_if(matches1.begin(),matches1.end(),dist),matches1.end());

//결과 출력
if(matches1.size()==62){
	Mat img_matches;
	drawMatches(img2, keypoints1, scene, keypoints2, matches1, img_matches);
	printf("천천히\n");
	//std::cout << "The size is: " << matches1.size() << '\n';
	imshow("matches", img_matches);
	waitKey(0);
	return 0;
}


//방지턱 주의(img1,keypoints3 4,match2,img_matches2, scene2)
vector<KeyPoint> keypoints3, keypoints4;
detector.detect(img1, keypoints3); // 표지판 '천천히'입력
detector.detect(scene2, keypoints4); // 찾고자 하는 배경 입력

// computing descriptors
Mat descriptors3, descriptors4;
extractor.compute(img1, keypoints3, descriptors3);
extractor.compute(scene2, keypoints4, descriptors4);

// matching descriptors
BruteForceMatcher<L2<float>> matcher2;
vector<DMatch> matches2;
matcher2.match(descriptors3, descriptors4, matches2);
matches2.erase(std::remove_if(matches2.begin(),matches2.end(),dist),matches2.end());

//결과 출력
if(matches1.size()>60 &&matches1.size()<70){
	Mat img_matches2;
	drawMatches(img1, keypoints3, scene2, keypoints4, matches2, img_matches2);
	printf("천천히\n");
	//std::cout << "The size is: " << matches2.size() << '\n';
	imshow("matches", img_matches2);
	waitKey(0);
	return 0;
}


//보행자 주의(img3,keypoints56,match3,scene3)
// keypoint 출력
vector<KeyPoint> keypoints5,keypoints6;
detector.detect(img3, keypoints5);
detector.detect(scene3, keypoints6);
// computing descriptors
Mat descriptors5, descriptors6;
extractor.compute(img3, keypoints5, descriptors5);
extractor.compute(scene3, keypoints6, descriptors6);

// matching descriptors
BruteForceMatcher<L2<float>> matcher3;
vector<DMatch> matches3;
matcher3.match(descriptors5, descriptors6, matches3);
matches3.erase(std::remove_if(matches3.begin(),matches3.end(),dist),matches3.end());

//결과 출력
if(matches3.size()>60 &&matches3.size()<70){
	printf("보행자 주의\n");
	//std::cout << "The size is: " << matches3.size() << '\n';
	Mat img_matches3;
	drawMatches(img3, keypoints4, scene, keypoints2, matches3, img_matches3);
	imshow("matches", img_matches3);
	waitKey(0);
	return 0;
}

//속도제한 50(img4, scene4,keypoints78,descriptors78,match4,matcher4)
// keypoint 출력
vector<KeyPoint> keypoints7, keypoint8;
detector.detect(img4, keypoints7);
detector.detect(scene4, keypoint8);
// computing descriptors
Mat descriptors7, descriptors8;
extractor.compute(img4, keypoints5, descriptors7);
extractor.compute(scene4,keypoint8,descriptors8);
// matching descriptors
BruteForceMatcher<L2<float>> matcher4;
vector<DMatch> matches4;
matcher4.match(descriptors7, descriptors8, matches4);
matches4.erase(std::remove_if(matches4.begin(),matches4.end(),dist),matches4.end());

//결과 출력
if(matches4.size()>60 &&matches4.size()<70){
	printf("속도제한 50\n");
	//std::cout << "The size is: " << matches4.size() << '\n';
	Mat img_matches4;
	drawMatches(img4, keypoints7, scene, keypoint8, matches4, img_matches4);
	imshow("matches", img_matches4);
	waitKey(0);
	return 0;
}


//양보(img5,keypoints9 10,descriptors9 10,match5,matcher5)
// keypoint 출력
vector<KeyPoint> keypoints9, keypoint10;
detector.detect(img5, keypoints9);
detector.detect(scene5, keypoint10);
// computing descriptors
Mat descriptors9, descriptors10;
extractor.compute(img5, keypoints9, descriptors9);
extractor.compute(scene5,keypoint10,descriptors10);
// matching descriptors
BruteForceMatcher<L2<float>> matcher5;
vector<DMatch> matches5;
matcher5.match(descriptors9, descriptors10, matches5);
matches5.erase(std::remove_if(matches5.begin(),matches5.end(),dist),matches5.end());

//결과 출력
if(matches5.size()>60 &&matches5.size()<70){
	printf("양보\n");
	//std::cout << "The size is: " << matches5.size() << '\n';
	Mat img_matches5;
	drawMatches(img5, keypoints9, scene5, keypoint10, matches5, img_matches5);
	imshow("matches", img_matches5);
	waitKey(0);
	return 0;
}

//우회전 금지(img6,keypoints11 12,descriptors11 12,match6,matcher6)
// keypoint 출력
vector<KeyPoint> keypoints11, keypoint12;
detector.detect(img6, keypoints11);
detector.detect(scene6, keypoint12);
// computing descriptors
Mat descriptors11, descriptors12;
extractor.compute(img6, keypoints11, descriptors12);
extractor.compute(scene6,keypoint12,descriptors12);
// matching descriptors
BruteForceMatcher<L2<float>> matcher6;
vector<DMatch> matches6;
matcher6.match(descriptors11, descriptors12, matches6);
matches6.erase(std::remove_if(matches6.begin(),matches6.end(),dist),matches6.end());

//결과 출력
if(matches6.size()>100 && matches6.size()<30){
	printf("우회전 금지\n");
	Mat img_matches6;
	//std::cout << "The size is: " << matches6.size() << '\n';
	drawMatches(img6, keypoints11, scene6, keypoint12, matches6, img_matches6);
	imshow("matches", img_matches6);
	waitKey(0);
	return 0;
}


//우회전 주의(img7,keypoints13 14,descriptors13 14,match7,matcher7)
// keypoint 출력
vector<KeyPoint> keypoints13, keypoints14;
detector.detect(img7, keypoints13);
detector.detect(scene7, keypoints14);
// computing descriptors
Mat descriptors13, descriptors14;
extractor.compute(img7, keypoints13, descriptors13);
extractor.compute(scene7, keypoints14, descriptors14);

// matching descriptors
BruteForceMatcher<L2<float>> matcher7;
vector<DMatch> matches7;
matcher7.match(descriptors13, descriptors14, matches7);
matches7.erase(std::remove_if(matches7.begin(),matches7.end(),dist),matches7.end());
	
//결과 출력
if(matches7.size()==35){
	printf("우회전 주의\n");
	//std::cout << "The size is: " << matches7.size() << '\n';
	Mat img_matches7;
	drawMatches(img7, keypoints13, scene5, keypoints14, matches7, img_matches7);
	imshow("matches", img_matches7);
	waitKey(0);
	return 0;
}


//위험(img8,keypoints15 16,descriptors15 16,match8,matcher8)
// keypoint 출력
vector<KeyPoint> keypoints15, keypoints16;
detector.detect(img8, keypoints15);
detector.detect(scene8, keypoints16);
// computing descriptors
Mat descriptors15, descriptors16;
extractor.compute(img8, keypoints15, descriptors15);
extractor.compute(scene8, keypoints16, descriptors16);

// matching descriptors
BruteForceMatcher<L2<float>> matcher8;
vector<DMatch> matches8;
matcher8.match(descriptors15, descriptors16, matches8);
matches8.erase(std::remove_if(matches8.begin(),matches8.end(),dist),matches8.end());

//결과 출력
if(matches8.size()==58){
	printf("위험\n");
	//std::cout << "The size is: " << matches8.size() << '\n';
	Mat img_matches8;
	drawMatches(img8, keypoints15, scene8, keypoints16, matches8, img_matches8);
	imshow("matches", img_matches8);
	waitKey(0);
	return 0;
}


//정지(img9,keypoints17 18,descriptors17 18,match9,matcher9)
// keypoint 출력
vector<KeyPoint> keypoints17, keypoints18;
detector.detect(img9, keypoints17);
detector.detect(scene9, keypoints18);
// computing descriptors
Mat descriptors17, descriptors18;
extractor.compute(img9, keypoints17, descriptors17);
extractor.compute(scene9, keypoints18, descriptors18);

// matching descriptors
BruteForceMatcher<L2<float>> matcher9;
vector<DMatch> matches9;
matcher9.match(descriptors17, descriptors18, matches9);
matches9.erase(std::remove_if(matches9.begin(),matches9.end(),dist),matches9.end());

//결과 출력
if(matches9.size()==56){
	printf("정지\n");
	//std::cout << "The size is: " << matches9.size() << '\n';
	Mat img_matches9;
	drawMatches(img9, keypoints17, scene9, keypoints18, matches9, img_matches9);
	imshow("matches", img_matches9);
	waitKey(0);
	return 0;
}


//좌회전 금지(img10,keypoints19 20,descriptors19 20,match10,matcher10)
// keypoint 출력
vector<KeyPoint> keypoints19, keypoints20;
detector.detect(img10, keypoints19);
detector.detect(scene10, keypoints20);
// computing descriptors
Mat descriptors19, descriptors20;
extractor.compute(img10, keypoints19, descriptors19);
extractor.compute(scene10, keypoints20, descriptors20);

// matching descriptors
BruteForceMatcher<L2<float>> matcher10;
vector<DMatch> matches10;
matcher10.match(descriptors19, descriptors20, matches10);
matches10.erase(std::remove_if(matches10.begin(),matches10.end(),dist),matches10.end());
//결과 출력
if(matches10.size()>60 &&matches10.size()<70){
	printf("좌회전 금지\n");
	//std::cout << "The size is: " << matches10.size() << '\n';
	Mat img_matches10;
	drawMatches(img10, keypoints19, scene10, keypoints20, matches10, img_matches10);
	imshow("matches", img_matches10);
	waitKey(0);
	return 0;
}


//좌회전 주의(img11,keypoints21 22,descriptors21 22,match11,matcher11)
// keypoint 출력
vector<KeyPoint> keypoints21, keypoints22;
detector.detect(img11, keypoints21);
detector.detect(scene11, keypoints22);
// computing descriptors
Mat descriptors21, descriptors22;
extractor.compute(img11, keypoints21, descriptors21);
extractor.compute(scene11, keypoints22, descriptors22);

// matching descriptors
BruteForceMatcher<L2<float>> matcher11;
vector<DMatch> matches11;
matcher11.match(descriptors21, descriptors22, matches11);
matches11.erase(std::remove_if(matches11.begin(),matches11.end(),dist),matches11.end());

//결과 출력
if(matches11.size()==27){
	printf("좌회전 주의\n");
	//std::cout << "The size is: " << matches11.size() << '\n';
	Mat img_matches11;
	drawMatches(img11, keypoints21, scene, keypoints22, matches11, img_matches11);
	imshow("matches", img_matches11);
	waitKey(0);
	return 0;
}


//직진 금지(img12,keypoints23 24,descriptors23 24,match12,matcher12)
// keypoint 출력
vector<KeyPoint> keypoints23, keypoints24;
detector.detect(img12, keypoints23);
detector.detect(scene12, keypoints24);
// computing descriptors
Mat descriptors23, descriptors24;
extractor.compute(img12, keypoints23, descriptors23);
extractor.compute(scene12, keypoints24, descriptors24);

// matching descriptors
BruteForceMatcher<L2<float>> matcher12;
vector<DMatch> matches12;
matcher12.match(descriptors23, descriptors24, matches12);
matches12.erase(std::remove_if(matches12.begin(),matches12.end(),dist),matches12.end());

//결과 출력
if(matches12.size()==17){
	printf("직진금지\n");
	//std::cout << "The size is: " << matches12.size() << '\n';
	Mat img_matches12;
	drawMatches(img12, keypoints23, scene12, keypoints24, matches12, img_matches12);
	imshow("matches", img_matches12);
	waitKey(0);
	return 0;
}


//직입 금지(img13,keypoints25 26,descriptors25 26,match13,matcher13)
// keypoint 출력
vector<KeyPoint> keypoints25, keypoints26;
detector.detect(img13, keypoints25);
detector.detect(scene13, keypoints26);
// computing descriptors
Mat descriptors25, descriptors26;
extractor.compute(img13, keypoints25, descriptors25);
extractor.compute(scene13, keypoints26, descriptors26);

// matching descriptors
BruteForceMatcher<L2<float>> matcher13;
vector<DMatch> matches13;
matcher13.match(descriptors25, descriptors26, matches13);
matches13.erase(std::remove_if(matches13.begin(),matches13.end(),dist),matches13.end());

//결과 출력
if(matches13.size()==47){
	printf("진입금지\n");
	//std::cout << "The size is: " << matches13.size() << '\n';
	Mat img_matches13;
	drawMatches(img13, keypoints25, scene13, keypoints26, matches13, img_matches13);
	imshow("matches", img_matches13);
	waitKey(0);
	return 0;
}


//통행 금지(img14,keypoints27 28,descriptors27 28,match14,matcher14)
// keypoint 출력
vector<KeyPoint> keypoints27, keypoints28;
detector.detect(img14, keypoints27);
detector.detect(scene14, keypoints28);
// computing descriptors
Mat descriptors27, descriptors28;
extractor.compute(img14, keypoints27, descriptors27);
extractor.compute(scene14, keypoints28, descriptors28);

// matching descriptors
BruteForceMatcher<L2<float>> matcher14;
vector<DMatch> matches14;
matcher14.match(descriptors27, descriptors28, matches14);
matches14.erase(std::remove_if(matches14.begin(),matches14.end(),dist),matches14.end());

//결과 출력
if(matches14.size()==70){
	printf("통행금지\n");
	//std::cout << "The size is: " << matches14.size() << '\n';
	Mat img_matches14;
	drawMatches(img14, keypoints27, scene14, keypoints28, matches14, img_matches14);
	imshow("matches", img_matches14);
	waitKey(0);
	return 0;
}


return 0;
}