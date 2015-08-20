/*
 * CommunicationNoise.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: Matthias Hofmann
 */

#include "CommunicationNoise.h"

namespace Sim3DNoiseLib
{

	CommunicationNoise::CommunicationNoise() :
		uniCommunication(0.0,1.0),
		uniGeneratorCommunication(uniRandCommunication,uniCommunication)
	{
		if(NoiseConfiguration::useRandomSeed)
		{
			uniRandCommunication.seed(std::time(0));
		}
		else if(NoiseConfiguration::useStandardSeed)
		{
			uniRandCommunication.seed(STANDARDSEED);
		}
		else
		{
			uniRandCommunication.seed(NoiseConfiguration::seedCommunication);
		}

	}

	CommunicationNoise::~CommunicationNoise()
	{

	}

	bool CommunicationNoise::applyCommNoise()
	{
		double rand = 0;
		if(NoiseConfiguration::commNoise)
		{
			rand = uniGeneratorCommunication();
			if (rand > NoiseConfiguration::commNoiseStrength)
				return false;
		}
		return true;
	}

}
