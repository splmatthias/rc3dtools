/*
 * SensorNoise.h
 * This class implements an error model with systematic and random noise.
 *  Created on: Sep 16, 2014
 *      Author: Matthias Hofmann
 */

#ifndef SENSORNOISE_H_
#define SENSORNOISE_H_

#define BUFFER 10

#include "NoiseConfiguration.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>

using namespace std;

namespace Sim3DNoiseLib
{
	class SensorNoise
	{
	public:
		SensorNoise();
		virtual ~SensorNoise();

		// single value noise
		double applyGyroNoise(string axis, double val);
		double applyAccNoise(string axis, double val);
		double applyForceNoise(string foot, double val);

	private:

		boost::normal_distribution<> gaussianGyro;
		boost::normal_distribution<> gaussianAcc;
		boost::normal_distribution<> gaussianForce;

		boost::uniform_real<> uniGyro;
		boost::uniform_real<> uniAcc;
		boost::uniform_real<> uniForce;

		boost::mt19937 gaussianRandGyro;
		boost::mt19937 gaussianRandAcc;
		boost::mt19937 gaussianRandForce;

		boost::mt19937 uniRandGyro;
		boost::mt19937 uniRandAcc;
		boost::mt19937 uniRandForce;

		boost::variate_generator<boost::mt19937&,
			   boost::uniform_real<> > uniGeneratorGyro;
		boost::variate_generator<boost::mt19937&,
			   boost::uniform_real<> > uniGeneratorAcc;
		boost::variate_generator<boost::mt19937&,
			   boost::uniform_real<> > uniGeneratorForce;

		boost::variate_generator<boost::mt19937&,
               boost::normal_distribution<> > gaussianGeneratorGyro;
		boost::variate_generator<boost::mt19937&,
			   boost::normal_distribution<> > gaussianGeneratorAcc;
		boost::variate_generator<boost::mt19937&,
			   boost::normal_distribution<> > gaussianGeneratorForce;
	};
}

#endif /* SENSORNOISE_H_ */
