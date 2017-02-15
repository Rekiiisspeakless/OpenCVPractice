#include <iostream>
#include <highgui.h>
#include<opencv2\core\utility.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;
int main() {
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
	for (;;) {
		Mat camFrame;
		cam >> camFrame;
		resize(camFrame, camFrame, Size(camSize, camSize));
		//imshow("Camera", camFrame);
		//if (waitKey(30) >= 0) break;
		cap.read(frame);
		camFrame.copyTo(frame(Rect(0, 0, camSize, camSize)));
		if (frame.rows > 0) imshow("Video", frame);
		else break;
		if(waitKey(10) >= 0) break;
	}
	//namedWindow("Camera", 1);
	
	return 0;
}