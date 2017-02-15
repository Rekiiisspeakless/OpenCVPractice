#include <iostream>
#include <highgui.h>
#include<opencv2\core\utility.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;
Mat src1, src2;
Mat camFrame, camFrameGray;
Mat mask, edgeDetected;
int lowThreshold;
int ratio = 3;
int kernalSize = 3;
Mat blendFrame;

void onTrackBar(int, void*) {

	double alpha = (double)lowThreshold / 100.0;
	double beta = 1.0 - alpha;
	
	blur(camFrameGray, edgeDetected, Size(3, 3));
	Canny(edgeDetected, edgeDetected, lowThreshold, lowThreshold * ratio, kernalSize);
	mask = Scalar::all(0);
	camFrame.copyTo(mask, edgeDetected);

	addWeighted(mask, alpha, camFrame, beta, 0.0, blendFrame);
}
int main() {
	int maxSlider = 100;
	namedWindow("edge detection", 0);
	createTrackbar("ratio", "edge detection", &lowThreshold, maxSlider, onTrackBar);
	VideoCapture cam(0);
	VideoCapture cap("video.mp4");
	if (!cam.isOpened()) {
		cout << "Can't open camera!" << endl;
		return -1;
	}
	if (!cap.isOpened()) {
		cout << "Can't open video!" << endl;
		return -1;
	}
	Mat edges;
	Mat frame;
	int camSize = 300;
	lowThreshold = 0;
	for (;;) {
		cam >> camFrame;
		resize(camFrame, camFrame, Size(camSize, camSize));
		mask.create(camFrame.size(), camFrame.type());
		cvtColor(camFrame, camFrameGray, CV_BGR2GRAY);
		onTrackBar(lowThreshold, 0);
		cap.read(frame);
		blendFrame.copyTo(frame(Rect(0, 0, camSize, camSize)));
		if (frame.rows > 0) imshow("edge detection", frame);
		else break;
		if(waitKey(10) >= 0) break;
	}
	
	return 0;
}