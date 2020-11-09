/*
 * ekf.h
 *
 *  Created on: Nov 9, 2020
 *      Author: levin
 */

#ifndef SRC_EKF_H_
#define SRC_EKF_H_

class ekf {
public:
	ekf();
	void process_measurement();
	virtual ~ekf();
};

#endif /* SRC_EKF_H_ */
