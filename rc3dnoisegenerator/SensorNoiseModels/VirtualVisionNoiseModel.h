/*
 * VirtualVisionNoiseModel.h
 *
 *  Created on: Sep 11, 2014
 *      Author: Matthias Hofmann
 *
 */

#include <ctime>            // std::time
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

#include <boost/math/distributions/uniform.hpp>
#include <boost/math/policies/policy.hpp>

#include "NoiseConfiguration.h"

using namespace std;

namespace Sim3DNoiseLib
{
	// optional: modeling hidden objects
	class VirtualVisionNoiseModel
	{
		public:
			VirtualVisionNoiseModel();
			virtual ~VirtualVisionNoiseModel();

			// ------------- VISION ---------------
			// false positives for ball and goalposts within the methods as they are only one
			vector<double> applyVisionBallNoise(vector<double> percept);
			vector<double> applyVisionGoalNoise(vector<double> percept);
			vector<double> applyVisionRobotsNoise(vector<double> percept);
			vector<double> applyFieldLinesNoise(vector<double> percept);

			// these methods generate a false positive within the given limits
			vector<double> spawnFalsePositive(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ);


		private:
			boost::normal_distribution<> gaussianVisionX;
			boost::normal_distribution<> gaussianVisionY;
			boost::normal_distribution<> gaussianVisionZ;

			boost::uniform_real<> uniBall;
			boost::uniform_real<> uniFieldLines;
			boost::uniform_real<> uniRobots;
			boost::uniform_real<> uniGoalPosts;

			boost::mt19937 gaussianRandBallX;
			boost::mt19937 gaussianRandBallY;
			boost::mt19937 gaussianRandBallZ;

			boost::mt19937 gaussianRandFieldLinesX;
			boost::mt19937 gaussianRandFieldLinesY;
			boost::mt19937 gaussianRandFieldLinesZ;

			boost::mt19937 gaussianRandRobotsX;
			boost::mt19937 gaussianRandRobotsY;
			boost::mt19937 gaussianRandRobotsZ;

			boost::mt19937 gaussianRandGoalPostsX;
			boost::mt19937 gaussianRandGoalPostsY;
			boost::mt19937 gaussianRandGoalPostsZ;

			boost::mt19937 uniRandBall;
			boost::mt19937 uniRandFieldLines;
			boost::mt19937 uniRandRobots;
			boost::mt19937 uniRandGoalPosts;

			boost::variate_generator<boost::mt19937&,
				boost::uniform_real<> > uniGeneratorBall;
			boost::variate_generator<boost::mt19937&,
				boost::uniform_real<> > uniGeneratorFieldLines;
			boost::variate_generator<boost::mt19937&,
			    boost::uniform_real<> > uniGeneratorRobots;
			boost::variate_generator<boost::mt19937&,
			 	boost::uniform_real<> > uniGeneratorGoalPosts;

			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorBallX;
			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorBallY;
			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorBallZ;

			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorFieldLinesX;
			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorFieldLinesY;
			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorFieldLinesZ;

			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorRobotsX;
			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorRobotsY;
			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorRobotsZ;

			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorGoalPostsX;
			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorGoalPostsY;
			boost::variate_generator<boost::mt19937&,
			    boost::normal_distribution<> > gaussianGeneratorGoalPostsZ;
		};
}


