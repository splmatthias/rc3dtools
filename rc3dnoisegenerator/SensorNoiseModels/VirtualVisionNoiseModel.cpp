/*
 * VirtualVisionNoiseModel.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: Matthias Hofmann
 *
 *      This file implements an error model for the virtual vision used in the 3D simulation league.
 *      It is customizable in order to configure the noise model according to the disadvantages of
 *      real image processors on the robot platform.
 *
 */

#include "VirtualVisionNoiseModel.h"

namespace Sim3DNoiseLib
{
		VirtualVisionNoiseModel::VirtualVisionNoiseModel() :
		gaussianVisionX(0.0,NoiseConfiguration::visionNoiseStrengthX),
		gaussianVisionY(0.0,NoiseConfiguration::visionNoiseStrengthY),
		gaussianVisionZ(0.0,NoiseConfiguration::visionNoiseStrengthZ),
		gaussianGeneratorBallX(gaussianRandBallX, gaussianVisionX),
		gaussianGeneratorBallY(gaussianRandBallY, gaussianVisionY),
		gaussianGeneratorBallZ(gaussianRandBallZ, gaussianVisionZ),
		gaussianGeneratorFieldLinesX(gaussianRandFieldLinesX, gaussianVisionX),
		gaussianGeneratorFieldLinesY(gaussianRandFieldLinesY, gaussianVisionY),
		gaussianGeneratorFieldLinesZ(gaussianRandFieldLinesZ, gaussianVisionZ),
		gaussianGeneratorRobotsX(gaussianRandRobotsX, gaussianVisionX),
		gaussianGeneratorRobotsY(gaussianRandRobotsY, gaussianVisionY),
		gaussianGeneratorRobotsZ(gaussianRandRobotsZ, gaussianVisionZ),
		gaussianGeneratorGoalPostsX(gaussianRandGoalPostsX, gaussianVisionX),
		gaussianGeneratorGoalPostsY(gaussianRandGoalPostsY, gaussianVisionY),
		gaussianGeneratorGoalPostsZ(gaussianRandGoalPostsZ, gaussianVisionZ),
		uniBall(0.0,1.0),
		uniFieldLines(0.0,1.0),
		uniRobots(0.0,1.0),
		uniGoalPosts(0.0,1.0),
		uniGeneratorBall(uniRandBall,uniBall),
		uniGeneratorFieldLines(uniRandFieldLines,uniFieldLines),
		uniGeneratorRobots(uniRandRobots,uniRobots),
		uniGeneratorGoalPosts(uniRandGoalPosts,uniGoalPosts)
		{
			if(NoiseConfiguration::useRandomSeed)
			{
				gaussianRandBallX.seed(std::time(0));
				gaussianRandBallY.seed(std::time(0));
				gaussianRandBallZ.seed(std::time(0));
				gaussianRandFieldLinesX.seed(std::time(0));
				gaussianRandFieldLinesY.seed(std::time(0));
				gaussianRandFieldLinesZ.seed(std::time(0));
				gaussianRandRobotsX.seed(std::time(0));
				gaussianRandRobotsY.seed(std::time(0));
				gaussianRandRobotsZ.seed(std::time(0));
				gaussianRandGoalPostsX.seed(std::time(0));
				gaussianRandGoalPostsY.seed(std::time(0));
				gaussianRandGoalPostsZ.seed(std::time(0));

				uniRandBall.seed(std::time(0));
				uniRandFieldLines.seed(std::time(0));
				uniRandRobots.seed(std::time(0));
				uniRandGoalPosts.seed(std::time(0));
			}
			else if(NoiseConfiguration::useStandardSeed)
			{
				gaussianRandBallX.seed(STANDARDSEED);
				gaussianRandBallY.seed(STANDARDSEED);
				gaussianRandBallZ.seed(STANDARDSEED);
				gaussianRandFieldLinesX.seed(STANDARDSEED);
				gaussianRandFieldLinesY.seed(STANDARDSEED);
				gaussianRandFieldLinesZ.seed(STANDARDSEED);
				gaussianRandRobotsX.seed(STANDARDSEED);
				gaussianRandRobotsY.seed(STANDARDSEED);
				gaussianRandRobotsZ.seed(STANDARDSEED);
				gaussianRandGoalPostsX.seed(STANDARDSEED);
				gaussianRandGoalPostsY.seed(STANDARDSEED);
				gaussianRandGoalPostsZ.seed(STANDARDSEED);

				uniRandBall.seed(STANDARDSEED);
				uniRandFieldLines.seed(STANDARDSEED);
				uniRandRobots.seed(STANDARDSEED);
				uniRandGoalPosts.seed(STANDARDSEED);
			}
			else
			{
				gaussianRandBallX.seed(NoiseConfiguration::seedVirtualVisionX);
				gaussianRandBallY.seed(NoiseConfiguration::seedVirtualVisionY);
				gaussianRandBallZ.seed(NoiseConfiguration::seedVirtualVisionZ);
				gaussianRandFieldLinesX.seed(NoiseConfiguration::seedVirtualVisionX);
				gaussianRandFieldLinesY.seed(NoiseConfiguration::seedVirtualVisionY);
				gaussianRandFieldLinesZ.seed(NoiseConfiguration::seedVirtualVisionZ);
				gaussianRandRobotsX.seed(NoiseConfiguration::seedVirtualVisionX);
				gaussianRandRobotsY.seed(NoiseConfiguration::seedVirtualVisionY);
				gaussianRandRobotsZ.seed(NoiseConfiguration::seedVirtualVisionZ);
				gaussianRandGoalPostsX.seed(NoiseConfiguration::seedVirtualVisionX);
				gaussianRandGoalPostsY.seed(NoiseConfiguration::seedVirtualVisionY);
				gaussianRandGoalPostsZ.seed(NoiseConfiguration::seedVirtualVisionZ);

				uniRandBall.seed(NoiseConfiguration::seedVirtualVisionX);
				uniRandFieldLines.seed(NoiseConfiguration::seedVirtualVisionX);
				uniRandRobots.seed(NoiseConfiguration::seedVirtualVisionX);
				uniRandGoalPosts.seed(NoiseConfiguration::seedVirtualVisionX);
			}
		}

		VirtualVisionNoiseModel::~VirtualVisionNoiseModel()
		{

		}

		vector<double> VirtualVisionNoiseModel::applyVisionBallNoise(vector<double> percept)
		{
			double randX = 0;
			double randY = 0;
			double randZ = 0;

			double uniBallValue = 0;

			if(NoiseConfiguration::visionBallNoise)
			{
				randX = gaussianGeneratorBallX();
				randY = gaussianGeneratorBallY();
				randZ = gaussianGeneratorBallZ();
				percept.at(0) += randX;
				percept.at(1) += randY;
				percept.at(2) += randZ;
			}
			if(NoiseConfiguration::visionBallBlackout)
			{
				uniBallValue = uniGeneratorBall();
				if(uniBallValue > NoiseConfiguration::visionBallBlackoutStrength)
				{
					percept.at(0) = 0;
					percept.at(1) = 0;
					percept.at(2) = 0;
				}
			}
			return percept;
		}

		vector<double> VirtualVisionNoiseModel::applyVisionGoalNoise(vector<double> percept)
		{
			double randX = 0;
			double randY = 0;
			double randZ = 0;

			double uniGoalValue = 0;

			if(NoiseConfiguration::visionGoalsNoise)
			{
				randX = gaussianGeneratorGoalPostsX();
				randY = gaussianGeneratorGoalPostsY();
				randZ = gaussianGeneratorGoalPostsZ();
				percept.at(0) += randX;
				percept.at(1) += randY;
				percept.at(2) += randZ;
			}
			if(NoiseConfiguration::visionGoalsBlackout)
			{
				uniGoalValue = uniGeneratorGoalPosts();
				if(uniGoalValue > NoiseConfiguration::visionGoalPostsBlackoutStrength)
				{
					percept.at(0) = 0;
					percept.at(1) = 0;
					percept.at(2) = 0;
				}
			}
			return percept;
		}

		vector<double> VirtualVisionNoiseModel::applyVisionRobotsNoise(vector<double> percept)
		{
			double randX = 0;
			double randY = 0;
			double randZ = 0;

			double uniValue = 0;

			if(NoiseConfiguration::visionRobotsNoise)
			{
				randX = gaussianGeneratorRobotsX();
				randY = gaussianGeneratorRobotsY();
				randZ = gaussianGeneratorRobotsZ();
				percept.at(0) += randX;
				percept.at(1) += randY;
				percept.at(2) += randZ;
			}
			if(NoiseConfiguration::visionRobotsBlackout)
			{
				uniValue = uniGeneratorRobots();
				if(uniValue > NoiseConfiguration::visionRobotsBlackoutStrength)
				{
					percept.at(0) = 0;
					percept.at(1) = 0;
					percept.at(2) = 0;
				}
			}
			return percept;
		}

		vector<double> VirtualVisionNoiseModel::applyFieldLinesNoise(vector<double> percept)
		{
			double randX = 0;
			double randY = 0;
			double randZ = 0;

			double uniValue = 0;

			if(NoiseConfiguration::visionFieldLinesNoise)
			{
				randX = gaussianGeneratorFieldLinesX();
				randY = gaussianGeneratorFieldLinesY();
				randZ = gaussianGeneratorFieldLinesZ();
				percept.at(0) += randX;
				percept.at(1) += randY;
				percept.at(2) += randZ;
			}
			if(NoiseConfiguration::visionFieldLinesBlackout)
			{
				uniValue = uniGeneratorFieldLines();
				if(uniValue > NoiseConfiguration::visionFieldLinesBlackoutStrength)
				{
					percept.at(0) = 0;
					percept.at(1) = 0;
					percept.at(2) = 0;
				}
			}
			return percept;
		}

		// these methods generate a false positive within the given limits
		// for Field lines: use 2 spawnPositive positions
		vector<double> VirtualVisionNoiseModel::spawnFalsePositive(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ)
		{
		    boost::uniform_real<float> uX(limitsX.at(0), limitsX.at(1));
		    boost::uniform_real<float> uY(limitsY.at(0), limitsY.at(1));
		    boost::uniform_real<float> uZ(limitsZ.at(0), limitsZ.at(1));
			boost::mt19937 rngX;
			boost::mt19937 rngY;
			boost::mt19937 rngZ;
			rngX.seed(time(0));
			rngY.seed(time(0));
			rngZ.seed(time(0));
		    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > genX(rngX, uX);
		    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > genY(rngY, uY);
		    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > genZ(rngZ, uZ);
		    vector<double> fp_percept;
		    fp_percept.push_back(genX());
		    fp_percept.push_back(genY());
		    fp_percept.push_back(genZ());
		    return fp_percept;
		}
}
