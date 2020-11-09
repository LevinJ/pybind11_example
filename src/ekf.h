/*
 * ekf.h
 *
 *  Created on: Nov 9, 2020
 *      Author: levin
 */

#ifndef SRC_EKF_H_
#define SRC_EKF_H_
#include <vector>
#include <iostream>
#include <memory>
#include <pybind11/functional.h>

class Measurement{
public:
	Measurement(float timestamp, const std::vector<float> &data, int seq);
	virtual ~Measurement(){
//		std::cout<<"Measurement destrctor"<<std::endl;
	}
	virtual void info(){
		std::cout<<"processing "<< meas_type_ <<", seq="<<seq_<<std::endl;
	}
	std::string meas_type_;
	int seq_;
};



class ekf {
public:
	ekf();
	std::vector<std::shared_ptr<Measurement>> mea_list_;
	void process_measurement(std::shared_ptr<Measurement> meas);
	virtual ~ekf();
	void regiger_state_sub(std::function<void(std::shared_ptr<Measurement>, std::vector<float> &, std::vector<float> & )> &f){
		subs_.push_back(f);
	}
	std::vector<std::function<void(std::shared_ptr<Measurement>, std::vector<float> &, std::vector<float> &)>>  subs_;
};



class WheelMeasurement: public Measurement{
public:
	WheelMeasurement(float timestamp, const std::vector<float> &data, int seq);
	virtual ~WheelMeasurement(){
		std::cout<<"WheelMeasurement destrctor"<<std::endl;
	}
};

class VOMeasurement: public Measurement{
public:
	VOMeasurement(float timestamp, const std::vector<float> &data, int seq);
	virtual ~VOMeasurement(){
		std::cout<<"VOMeasurement destrctor"<<std::endl;
	}
};

#endif /* SRC_EKF_H_ */
