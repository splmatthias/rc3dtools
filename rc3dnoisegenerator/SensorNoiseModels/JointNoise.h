/*
 * JointNoise.h
 *
 *  Created on: Sep 16, 2014
 *      Author: Matthias Hofmann
 */

#ifndef JOINTNOISE_H_
#define JOINTNOISE_H_

#include "NoiseConfiguration.h"
#include <string>

using namespace std;

// optional: sophisticated noise model 

namespace Sim3DNoiseLib
{
	class JointNoise
	{
	public:
		JointNoise();
		virtual ~JointNoise();
		double applyJointNoise(int joint, double val);
		double applyJointNoiseAlgorithm(double val);

	private:
		boost::normal_distribution<> gaussianJoints;
		boost::mt19937 gaussianRandJoints;
		boost::variate_generator<boost::mt19937&,
		               boost::normal_distribution<> >  gaussianGeneratorJoints;
		int numberOfJoints;
	};
}
#endif /* JOINTNOISE_H_ */
