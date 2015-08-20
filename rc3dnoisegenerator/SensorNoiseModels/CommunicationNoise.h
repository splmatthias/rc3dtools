/*
 * CommunicationNoiseGenerator.h
 *
 *  Created on: Sep 16, 2014
 *      Author: Matthias Hofmann
 */

#ifndef COMMUNICATIONNOISE_H_
#define COMMUNICATIONNOISE_H_



#include "NoiseConfiguration.h"

// more possibilities: delayed packages noise
// valid for sound or wireless communication

namespace Sim3DNoiseLib
{
	class CommunicationNoise
	{
	public:
		CommunicationNoise();
		virtual ~CommunicationNoise();

		bool applyCommNoise();

	private:
		boost::uniform_real<> uniCommunication;
		boost::mt19937 uniRandCommunication;
		boost::variate_generator<boost::mt19937&,
			   boost::uniform_real<> > uniGeneratorCommunication;
	};
}

#endif /* COMMUNICATIONNOISEGENERATOR_H_ */
