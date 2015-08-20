/*
 * NoiseConfiguration.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: calli82
 */

#include "NoiseConfiguration.h"

namespace Sim3DNoiseLib
{
	bool NoiseConfiguration::initialized = false;

	bool NoiseConfiguration::useRandomSeed = false;
	bool NoiseConfiguration::useStandardSeed = false;

	bool NoiseConfiguration::gyroAppGaussianNoise = false;
	bool NoiseConfiguration::gyroAppSystematicNoise = false;
	bool NoiseConfiguration::gyroAppSensorBlackout = false;

	bool NoiseConfiguration::accAppGaussianNoise = false;
	bool NoiseConfiguration::accAppSystematicNoise = false;
	bool NoiseConfiguration::accAppSensorBlackout = false;

	bool NoiseConfiguration::forceAppGaussianNoise = false;
	bool NoiseConfiguration::forceAppSystematicNoise = false;
	bool NoiseConfiguration::forceAppSensorBlackout = false;

	// just a basic switch
	bool NoiseConfiguration::jointsNoiseGaussian = false;
	bool NoiseConfiguration::useJointsNoiseAlgorithm = false;

	// vision configuration
	bool NoiseConfiguration::visionBallNoise = false;
	bool NoiseConfiguration::visionBallBlackout = false;
	bool NoiseConfiguration::visionBallFalsePositives = false;
	bool NoiseConfiguration::visionGoalsNoise = false;
	bool NoiseConfiguration::visionGoalsBlackout = false;
	bool NoiseConfiguration::visionGoalFalsePositives = false;
	bool NoiseConfiguration::visionRobotsNoise = false;
	bool NoiseConfiguration::visionRobotsBlackout = false;
	bool NoiseConfiguration::visionRobotsFalsePositives = false;

	// field lines include center circle and penalty crosses as well
	bool NoiseConfiguration::visionFieldLinesNoise = false;
	bool NoiseConfiguration::visionFieldLinesBlackout = false;
	bool NoiseConfiguration::visionFieldLinesFalsePositives = false;

	// switch to activate occlusion
	bool NoiseConfiguration::visionActivateOcclusion = false;
	bool NoiseConfiguration::distanceDependendNoise = false;

	// configuration values individual error model
	double NoiseConfiguration::gyroNoiseStrength = 0;
	double NoiseConfiguration::gyroSystematicNoise = 0;
	double NoiseConfiguration::gyroBlackoutStrength = 0;

	double NoiseConfiguration::accNoiseStrength = 0;
	double NoiseConfiguration::accSystematicNoise = 0;
	double NoiseConfiguration::accBlackoutStrength = 0;

	double NoiseConfiguration::forceNoiseStrength = 0;
	double NoiseConfiguration::forceSystematicNoise = 0;
	double NoiseConfiguration::forceBlackoutStrength = 0;

	double NoiseConfiguration::visionNoiseStrengthX = 0;
	double NoiseConfiguration::visionNoiseStrengthY = 0;
	double NoiseConfiguration::visionNoiseStrengthZ = 0;

	double NoiseConfiguration::visionBallBlackoutStrength = 0;
	double NoiseConfiguration::visionFieldLinesBlackoutStrength = 0;
	double NoiseConfiguration::visionRobotsBlackoutStrength = 0;
	double NoiseConfiguration::visionGoalPostsBlackoutStrength = 0;

	double NoiseConfiguration::visionFalsePositiveStrength = 0;

	double NoiseConfiguration::jointsNoiseStrength = 0;
	int NoiseConfiguration::numberOfJoints = 0;

	bool NoiseConfiguration::commNoise = false;
	double NoiseConfiguration::commNoiseStrength = 0;

	int NoiseConfiguration::seedSensorGyro = 0;
	int NoiseConfiguration::seedSensorAcc = 0;
	int NoiseConfiguration::seedSensorForce = 0;
	int NoiseConfiguration::seedVirtualVisionX = 0;
	int NoiseConfiguration::seedVirtualVisionY = 0;
	int NoiseConfiguration::seedVirtualVisionZ = 0;
	int NoiseConfiguration::seedCommunication = 0;
	int NoiseConfiguration::seedJoints = 0;

	NoiseConfiguration::NoiseConfiguration()
	{
		readConfigurationFile();
	}

	NoiseConfiguration::~NoiseConfiguration()
	{

	}

	int NoiseConfiguration::getSeed()
	{
	    ifstream rand("/dev/urandom");
	    char tmp[sizeof(int)];
	    rand.read(tmp,sizeof(int));
	    rand.close();
	    int* number = reinterpret_cast<int*>(tmp);
	    return (*number);
	}

	void NoiseConfiguration::readConfigurationFile()
	{
		Config cfg("noiseLibConfiguration");

		// add validity check and messages
		NoiseConfiguration::gyroAppGaussianNoise = cfg.getValue("gyroAppGaussianNoise", false);
		NoiseConfiguration::gyroAppSystematicNoise = cfg.getValue("gyroAppSystematicNoise", false);
		NoiseConfiguration::gyroAppSensorBlackout = cfg.getValue("gyroAppSensorBlackout", false);

		NoiseConfiguration::accAppGaussianNoise = cfg.getValue("accAppGaussianNoise", false);
		NoiseConfiguration::accAppSystematicNoise = cfg.getValue("accAppSystematicNoise", false);
		NoiseConfiguration::accAppSensorBlackout = cfg.getValue("accAppSensorBlackout", false);

		NoiseConfiguration::forceAppGaussianNoise = cfg.getValue("forceAppGaussianNoise", false);
		NoiseConfiguration::forceAppSystematicNoise = cfg.getValue("forceAppSystematicNoise", false);
		NoiseConfiguration::forceAppSensorBlackout = cfg.getValue("forceAppSensorBlackouts", false);

		// just a basic switch
		NoiseConfiguration::jointsNoiseGaussian = cfg.getValue("jointsNoise", false);
		NoiseConfiguration::numberOfJoints = cfg.getValue("numberOfJoints", 23);

		// vision configuration
		NoiseConfiguration::visionBallNoise = cfg.getValue("visionBallNoise", false);
		NoiseConfiguration::visionBallBlackout = cfg.getValue("visionBallBlackout", false);
		NoiseConfiguration::visionBallFalsePositives = cfg.getValue("visionBallFalsePositives", false);
		NoiseConfiguration::visionGoalsNoise = cfg.getValue("visionGoalsNoise", false);
		NoiseConfiguration::visionGoalsBlackout = cfg.getValue("visionGoalsBlackout", false);
		NoiseConfiguration::visionGoalFalsePositives = cfg.getValue("visionGoalFalsePositives", false);
		NoiseConfiguration::visionRobotsNoise = cfg.getValue("visionRobotsNoise", false);
		NoiseConfiguration::visionRobotsBlackout = cfg.getValue("visionRobotsBlackout", false);
		NoiseConfiguration::visionRobotsFalsePositives = cfg.getValue("visionRobotsFalsePositives", false);

		// field lines include center circle and penalty crosses as well
		NoiseConfiguration::visionFieldLinesNoise = cfg.getValue("visionFieldLinesNoise", false);
		NoiseConfiguration::visionFieldLinesBlackout = cfg.getValue("visionFieldLinesBlackout", false);
		NoiseConfiguration::visionFieldLinesFalsePositives = cfg.getValue("visionFieldLinesFalsePositives", false);

		// switch to activate occlusion
		NoiseConfiguration::visionActivateOcclusion = cfg.getValue("visionActivateOcclusion", false);
		NoiseConfiguration::distanceDependendNoise = cfg.getValue("distanceDependendNoise", false);

		// configuration values individual error model
		NoiseConfiguration::gyroNoiseStrength = cfg.getValue("gyroNoiseStrength", 0.0);
		NoiseConfiguration::gyroSystematicNoise = cfg.getValue("gyroSystematicNoise", 0.0);
		NoiseConfiguration::gyroBlackoutStrength = cfg.getValue("gyroBlackoutStrength", 0.0);

		NoiseConfiguration::accNoiseStrength = cfg.getValue("accNoiseStrength", 0.0);
		NoiseConfiguration::accSystematicNoise = cfg.getValue("accSystematicNoise", 0.0);
		NoiseConfiguration::accBlackoutStrength = cfg.getValue("accBlackoutStrength", 0.0);

		NoiseConfiguration::forceNoiseStrength = cfg.getValue("forceNoiseStrength", 0.0);
		NoiseConfiguration::forceSystematicNoise = cfg.getValue("forceSystematicNoise", 0.0);
		NoiseConfiguration::forceBlackoutStrength = cfg.getValue("forceBlackoutStrength", 0.0);

		NoiseConfiguration::visionNoiseStrengthX = cfg.getValue("visionNoiseStrengthX", 0.0);
		NoiseConfiguration::visionNoiseStrengthY = cfg.getValue("visionNoiseStrengthY", 0.0);
		NoiseConfiguration::visionNoiseStrengthZ = cfg.getValue("visionNoiseStrengthZ", 0.0);
		NoiseConfiguration::visionBallBlackoutStrength = cfg.getValue("visionBallBlackoutStrength", 0.0);
		NoiseConfiguration::visionFieldLinesBlackoutStrength = cfg.getValue("visionFieldLinesBlackoutStrength", 0.0);
		NoiseConfiguration::visionRobotsBlackoutStrength = cfg.getValue("visionRobotsBlackoutStrength", 0.0);
		NoiseConfiguration::visionGoalPostsBlackoutStrength = cfg.getValue("visionGoalPostsBlackoutStrength", 0.0);

		NoiseConfiguration::visionFalsePositiveStrength = cfg.getValue("visionFalsePositiveStrength", 0.0);

		NoiseConfiguration::jointsNoiseStrength = cfg.getValue("jointsNoiseStrength", 0.0);

		NoiseConfiguration::commNoise = cfg.getValue("commNoise", 0.0);
		NoiseConfiguration::commNoiseStrength = cfg.getValue("commNoiseStrength", 0.0);

		NoiseConfiguration::useRandomSeed = cfg.getValue("useRandomSeed", false);
		NoiseConfiguration::useStandardSeed = cfg.getValue("useStandardSeed", false);
		NoiseConfiguration::seedSensorGyro = cfg.getValue("seedSensorGyro", 0.0);
		NoiseConfiguration::seedSensorAcc = cfg.getValue("seedSensorAcc", 0.0);
		NoiseConfiguration::seedSensorForce = cfg.getValue("seedSensorForce", 0.0);
		NoiseConfiguration::seedJoints = cfg.getValue("seedJoints", 0.0);
		NoiseConfiguration::seedVirtualVisionX = cfg.getValue("seedVirtualVisionX", 0.0);
		NoiseConfiguration::seedVirtualVisionY = cfg.getValue("seedVirtualVisionY", 0.0);
		NoiseConfiguration::seedVirtualVisionZ = cfg.getValue("seedVirtualVisionZ", 0.0);
		NoiseConfiguration::seedCommunication = cfg.getValue("seedCommunication", 0.0);

		NoiseConfiguration::initialized = true;
	}
}
