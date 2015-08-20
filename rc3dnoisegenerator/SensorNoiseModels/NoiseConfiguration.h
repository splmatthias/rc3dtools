/*
 * NoiseConfiguration.h
 *
 *  Created on: Nov 26, 2014
 *      Author: calli82
 */

#ifndef NOISECONFIGURATION_H_
#define NOISECONFIGURATION_H_

#define STANDARDSEED 1

#include <fstream>
#include <boost/random.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include "Config/Config.h"

using namespace std;

namespace Sim3DNoiseLib
{

	class NoiseConfiguration
	{
	public:
		NoiseConfiguration();
		virtual ~NoiseConfiguration();

		static void readConfigurationFile();
		static int getSeed();

		static bool initialized;
		static bool useRandomSeed;
		static bool useStandardSeed;

		// this class represents the full set of configuration flags
		static bool gyroAppGaussianNoise;
		static bool gyroAppSystematicNoise;
		static bool gyroAppSensorBlackout;

		static bool accAppGaussianNoise;
		static bool accAppSystematicNoise;
		static bool accAppSensorBlackout;

		static bool forceAppGaussianNoise;
		static bool forceAppSystematicNoise;
		static bool forceAppSensorBlackout;

		// just a basic switch
		static bool jointsNoiseGaussian;
		static bool useJointsNoiseAlgorithm;

		// vision configuration
		static bool visionBallNoise;
		static bool visionBallBlackout;
		static bool visionBallFalsePositives;
		static bool visionGoalsNoise;
		static bool visionGoalsBlackout;
		static bool visionGoalFalsePositives;
		static bool visionRobotsNoise;
		static bool visionRobotsBlackout;
		static bool visionRobotsFalsePositives;

		// field lines include center circle and penalty crosses as well
		static bool visionFieldLinesNoise;
		static bool visionFieldLinesBlackout;
		static bool visionFieldLinesFalsePositives;

		// switch to activate occlusion
		static bool visionActivateOcclusion;
		static bool distanceDependendNoise;

		// configuration values individual error model
		static double gyroNoiseStrength;
		static double gyroSystematicNoise;
		static double gyroBlackoutStrength;

		static double accNoiseStrength;
		static double accSystematicNoise;
		static double accBlackoutStrength;

		static double forceNoiseStrength;
		static double forceSystematicNoise;
		static double forceBlackoutStrength;

		static double visionNoiseStrengthX;
		static double visionNoiseStrengthY;
		static double visionNoiseStrengthZ;
		static double visionBallBlackoutStrength;
		static double visionFieldLinesBlackoutStrength;
		static double visionRobotsBlackoutStrength;
		static double visionGoalPostsBlackoutStrength;
		static double visionFalsePositiveStrength;

		static double jointsNoiseStrength;

		static bool commNoise;
		static double commNoiseStrength;

		static int numberOfJoints;

		// seed: 0 means time!
		static int seedSensorGyro;
		static int seedSensorAcc;
		static int seedSensorForce;
		static int seedJoints;
		static int seedVirtualVisionX;
		static int seedVirtualVisionY;
		static int seedVirtualVisionZ;
		static int seedCommunication;
	};

}

#endif /* NOISECONFIGURATION_H_ */
