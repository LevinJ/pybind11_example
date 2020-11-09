/*
 * ekf.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: levin
 */

#include "ekf.h"
#include <iostream>
#include <vector>

ekf::ekf() {
	// TODO Auto-generated constructor stub

}

ekf::~ekf() {
	// TODO Auto-generated destructor stub
}

void ekf::process_measurement(std::shared_ptr<Measurement> meas){
//	std::cout<<"process_measurement is called"<<std::endl;
//	meas->info();
	mea_list_.push_back(meas);
	std::vector<float> x;
	std::vector<float> p;
	for(auto &sub :subs_){
		sub(meas, x, p);
	}
}

Measurement::Measurement(float timestamp, const std::vector<float> &data, int seq){
//	std::cout<<"Measurement constructor "<<std::endl;
	seq_ = seq;
}
WheelMeasurement::WheelMeasurement(float timestamp, const std::vector<float> &data, int seq): Measurement(timestamp, data, seq){
//	std::cout<<"WheelMeasurement constructor "<<std::endl;
	meas_type_ = "wheel";
}

VOMeasurement::VOMeasurement(float timestamp, const std::vector<float> &data, int seq): Measurement(timestamp, data, seq){
//	std::cout<<"VOMeasurement constructor "<<std::endl;
	meas_type_ = "vo";
}


