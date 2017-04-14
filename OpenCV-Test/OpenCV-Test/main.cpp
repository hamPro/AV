//OpenCV Linedetect

#include "stdafx.h"
#include "LaneDetect.h"


int lowThreshold=230, highThreshold=250; // for use Canny
unsigned long start = 0; // for use get getTickCount();
unsigned long finish = 0;

int main(int argc, char** argv)
{
	VideoCapture capture(".\\challenge.mp4");
	if (!capture.isOpened())
	{
		cout << "Video file can not open." << endl;
		return 0;
	}

	Mat frame;
	Mat imgRoi;
	Mat noiseFilter;
	Mat edgeDetection;
	Mat hough;
	vector<Vec4i> lines;
	Rect Roi1(0, 370, 960, 130);

	LaneDetect lane_l;
	LaneDetect lane_r;

	Vec4i l;
	Vec4i left;
	Vec4i right;


	//create window
	namedWindow("orgin");
	namedWindow("roadVideo");

	int max_lowThreshold = 500, max_highThreshold = 500;
	namedWindow("Edge threshold", CV_WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold:", "Edge threshold", &lowThreshold, max_lowThreshold);
	createTrackbar("Max Threshold:", "Edge threshold", &highThreshold, max_highThreshold);
	//Canny_Trackbar;

	while (1)
	{
		start = getTickCount();

		capture >> frame;
		if (frame.empty())
			break;

		resize(frame, frame, Size(960, 540));
		imgRoi = frame(Roi1);

		GaussianBlur(imgRoi, noiseFilter, Size(3, 3), 0);
		Canny(noiseFilter, edgeDetection, lowThreshold, highThreshold);
	    	//low임계값보다 작으면 엣지(x), high임계값보다 크면 엣지(o), 값이 사이에 있는것은 주위에 엣지가 있는지 유무에 따라

		cvtColor(edgeDetection, hough, COLOR_GRAY2BGR);
		HoughLinesP(edgeDetection, lines, 1, CV_PI / 180, 50, 50, 10);

		for (size_t i = 1; i < lines.size(); i++)
		{
			l = lines[i];
			if (l[0] < 480 & l[0] > 200)
			{
				left = lane_l.find(lines[i]);
			}
			else if(l[0] > 480 & l[0] <700) 
			{
				right = lane_r.find(lines[i]);
			}
		}
	
		// Lengthen
		lane_l.lengthen(&hough, left);
		lane_r.lengthen(&hough, right);
		line(hough, Point(20, 64), Point(940, 64), Scalar(0, 255, 0), 2); // 직선
		circle(hough, Point((lane_r.c - lane_l.c / 2)-20, 64), 3, Scalar(200, 125, 125), 6);
		cout << "midPoint : " << lane_r.c - lane_l.c / 2 << endl;
		
		lane_l.reset();
		lane_r.reset();

		imshow("roadVideo", hough);
		//imshow("origin", frame);
		if (waitKey(2) == 27) // Esc = '27'
			break;

		finish = getTickCount();
		cout << "loop sec : " << (finish - start) / getTickFrequency() << endl;
	}

	destroyAllWindows();

	return 0;
}