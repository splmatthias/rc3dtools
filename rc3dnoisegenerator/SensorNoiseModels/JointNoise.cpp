/*
 * JointNoise.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: Matthias Hofmann
 */

#include "JointNoise.h"

namespace Sim3DNoiseLib
{
	JointNoise::JointNoise() :
				gaussianJoints(0.0,NoiseConfiguration::jointsNoiseStrength),
				gaussianGeneratorJoints(gaussianRandJoints, gaussianJoints),
				numberOfJoints(0)
	{
		if(NoiseConfiguration::useRandomSeed)
		{
			gaussianRandJoints.seed(std::time(0));
		}
		else if(NoiseConfiguration::useStandardSeed)
		{
			gaussianRandJoints.seed(STANDARDSEED);
		}
		else
		{
			gaussianRandJoints.seed(NoiseConfiguration::seedJoints);
		}
	}

	JointNoise::~JointNoise()
	{

	}

	double JointNoise::applyJointNoise(int joint, double val)
	{
		double rand = 0;
		if(NoiseConfiguration::jointsNoiseGaussian)
		{
			// add value from distribution
			rand = gaussianGeneratorJoints();
			val += rand;
		}
		return val;
	}

	double JointNoise::applyJointNoiseAlgorithm(double val)
	{
		if(NoiseConfiguration::useJointsNoiseAlgorithm)
		{
			// method stub
			return val;
		}
		return val;
	}
}
