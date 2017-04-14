#pragma once
#include "stdafx.h"

class LaneDetect
{
	double temp, gradient;
	double x, y, a, b;
	double x1, y1, x2, y2;
	Vec4i result;

public:
	double c;
	LaneDetect(double gradient = 0);
	Vec4i find(Vec4i l);
	void LaneDetect::lengthen(Mat * src, Vec4i l2);
	void reset();
	~LaneDetect();
};