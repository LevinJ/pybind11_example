/*
 * testimage.cpp
 *
 *  Created on: Nov 10, 2020
 *      Author: levin
 */

#include "testimage.h"
#include <opencv2/opencv.hpp>
#include <iostream>

//using namespace cv;

testimage::testimage() {
	// TODO Auto-generated constructor stub

}

testimage::~testimage() {
	// TODO Auto-generated destructor stub
}

void testimage::show_image(py::array_t<uint8_t>& img){
	auto rows = img.shape(0);
	auto cols = img.shape(1);
	auto type = CV_8UC3;

	cv::Mat img2(rows, cols, type, (unsigned char*)img.data());
	cv::imshow("test", img2);

	cv::waitKey(0);
}

