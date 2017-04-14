#include "LaneDetect.h"



LaneDetect::LaneDetect(double gradient)
{
	
}
 

Vec4i LaneDetect::find(Vec4i l1)
{
	temp = ((double)l1[3] - l1[1]) / ((double)l1[2] - l1[0]);
	if (gradient != std::max(abs(temp), abs(gradient)))
	{
		gradient = std::max(abs(temp), abs(gradient));
		result = l1;
	}

	// cout << "temp : " << temp << ", gradient : " << gradient << endl;
	
	return result;
	
}

void LaneDetect::lengthen(Mat * src, Vec4i l2)
{
	// y=ax+b
	a = ((double)l2[3] - l2[1]) / ((double)l2[2] - l2[0]); // 기울기
	b = (double)l2[3] - a*l2[2]; // y절편

	// EndPoint
	x1 = -b / a;           // y = 0
	x2 = (480 - b) / a;    // y = 480
	c = (64 - b) / a;

	//	cout << "a : " << a << ", b : " << b << endl;
	//	cout << "x1 : " << x1 << ", y1 : " << y1 << ", x2 : " << x2 << ", y2 : " << y2 << endl;
	line(*src, Point(x1, 0), Point(x2, 480), Scalar(0, 0, 255), 3, CV_AA);

}

void LaneDetect::reset()
{
	gradient = 0;
}

LaneDetect::~LaneDetect()
{
}
