/*
 * SensorNoise.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: calli82
 */

#include "SensorNoise.h"

namespace Sim3DNoiseLib
{

	SensorNoise::SensorNoise() :
			gaussianGyro(0.0,NoiseConfiguration::gyroNoiseStrength),
			gaussianAcc(0.0,NoiseConfiguration::accNoiseStrength),
			gaussianForce(0.0,NoiseConfiguration::forceNoiseStrength),
			gaussianGeneratorGyro(gaussianRandGyro, gaussianGyro),
			gaussianGeneratorAcc(gaussianRandAcc, gaussianAcc),
			gaussianGeneratorForce(gaussianRandForce, gaussianForce),
			uniGyro(0.0,1.0),
			uniAcc(0.0,1.0),
			uniForce(0.0,1.0),
			uniGeneratorGyro(uniRandGyro,uniGyro),
			uniGeneratorAcc(uniRandAcc,uniAcc),
			uniGeneratorForce(uniRandForce,uniForce)

	{
		if(NoiseConfiguration::useRandomSeed)
		{
			gaussianRandGyro.seed(std::time(0));
			gaussianRandAcc.seed(std::time(0));
			gaussianRandForce.seed(std::time(0));
			uniRandGyro.seed(std::time(0));
			uniRandAcc.seed(std::time(0));
			uniRandForce.seed(std::time(0));
		}
		else if(NoiseConfiguration::useStandardSeed)
		{
			gaussianRandGyro.seed(STANDARDSEED);
			gaussianRandAcc.seed(STANDARDSEED);
			gaussianRandForce.seed(STANDARDSEED);
			uniRandGyro.seed(STANDARDSEED);
			uniRandAcc.seed(STANDARDSEED);
			uniRandForce.seed(STANDARDSEED);
		}
		else
		{
			gaussianRandGyro.seed(NoiseConfiguration::seedSensorGyro);
			gaussianRandAcc.seed(NoiseConfiguration::seedSensorAcc);
			gaussianRandForce.seed(NoiseConfiguration::seedSensorForce);
			uniRandGyro.seed(NoiseConfiguration::seedSensorGyro);
			uniRandAcc.seed(NoiseConfiguration::seedSensorAcc);
			uniRandForce.seed(NoiseConfiguration::seedSensorForce);
		}
	}

	SensorNoise::~SensorNoise()
	{

	}

	double SensorNoise::applyGyroNoise(string axis, double val)
	{
		// tbd: different distributions for different axis...

		double rand = 0;
		if(NoiseConfiguration::gyroAppSystematicNoise)
		{
			val += NoiseConfiguration::gyroAppSystematicNoise;
		}
		if(NoiseConfiguration::gyroAppGaussianNoise)
		{
			// add value from associated distribution
			rand = gaussianGeneratorGyro();
			val += rand;
		}
		if(NoiseConfiguration::gyroAppSensorBlackout)
		{
			rand = uniGeneratorGyro();
			if (rand > NoiseConfiguration::gyroBlackoutStrength)
				val = 1000;
		}
		return val;
	}


	double SensorNoise::applyAccNoise(string axis, double val)
	{
		double rand = 0;
		if(NoiseConfiguration::accAppSystematicNoise)
		{
			val += NoiseConfiguration::accAppSystematicNoise;
		}
		if(NoiseConfiguration::accAppGaussianNoise)
		{
			// add value from distribution
			rand = gaussianGeneratorAcc();
			val += rand;
		}
		if(NoiseConfiguration::accAppSensorBlackout)
		{
			rand = uniGeneratorAcc();
			if (rand > NoiseConfiguration::accBlackoutStrength)
				val = 1000;
		}

		return val;
	}

	double SensorNoise::applyForceNoise(string foot, double val)
	{
		double rand = 0;
		if(NoiseConfiguration::forceAppSystematicNoise)
		{
			val += NoiseConfiguration::forceAppSystematicNoise;
		}
		if(NoiseConfiguration::forceAppGaussianNoise)
		{
			// add value from distribution
			rand = gaussianGeneratorForce();
			val += rand;
		}
		if(NoiseConfiguration::forceAppSensorBlackout)
		{
			rand = uniGeneratorForce();
			if (rand > NoiseConfiguration::forceBlackoutStrength)
				val = 1000;
		}
		return val;
	}
}
