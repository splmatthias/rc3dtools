/*
 * NoiseGenerator.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: calli82
 */

#include "NoiseGenerator.h"

namespace Sim3DNoiseLib
{

    NoiseGenerator::NoiseGenerator()
	{
    	noiseConfiguration = new NoiseConfiguration();
    	sensorNoise = new SensorNoise();
		jointNoise = new JointNoise();
		commNoise = new CommunicationNoise();
		virtualVisionNoise = new VirtualVisionNoiseModel();

		for(int i = 0; i < 3; i++)
		{
			defaultPercept.push_back(0);
		}
	}

	NoiseGenerator::~NoiseGenerator()
	{
		delete sensorNoise;
		delete jointNoise;
		delete commNoise;
		delete virtualVisionNoise;
		delete noiseConfiguration;

		sensorNoise = 0;
		jointNoise = 0;
		commNoise = 0;
		virtualVisionNoise = 0;
		noiseConfiguration = 0;
	}

	// single value noise
	// returns 1000 if percept should be left out
	double NoiseGenerator::applyGyroNoise(string axis, double val)
	{
		return sensorNoise->applyGyroNoise(axis, val);
	}

	// single value noise
	// returns 1000 if percept should be left out
	double NoiseGenerator::applyForceNoise(string foot, double val)
	{
		return sensorNoise->applyForceNoise(foot, val);
	}

	// single value noise
	// returns 1000 if percept should be left out
	double NoiseGenerator::applyAccNoise(string direction, double val)
	{
		return sensorNoise->applyAccNoise(direction, val);
	}

	// single value noise
	// returns 1000 if percept should be left out
	double NoiseGenerator::applyJointsNoise(int joint, double val)
	{
		return jointNoise->applyJointNoise(joint, val);
	}

	// two-dimensional noise
	vector<double> NoiseGenerator::applyVisionBallNoise(vector<double> percept)
	{
		return virtualVisionNoise->applyVisionBallNoise(percept);
	}

	vector<double> NoiseGenerator::applyVisionGoalNoise(string post, vector<double> percept)
	{
		return virtualVisionNoise->applyVisionGoalNoise(percept);
	}

	vector<double> NoiseGenerator::applyVisionRobotsNoise(vector<double> percept)
	{
		return virtualVisionNoise->applyVisionRobotsNoise(percept);
	}

	// returns
	vector<double> NoiseGenerator::applyFieldLinesNoise(vector<double> percept)
	{
		return virtualVisionNoise->applyFieldLinesNoise(percept);
	}

	vector<double> NoiseGenerator::spawnFalsePositiveBall(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ)
	{
		if(NoiseConfiguration::visionBallFalsePositives)
		{
			return virtualVisionNoise->spawnFalsePositive(limitsX, limitsY, limitsZ);
		}
		return defaultPercept;
	}

	vector<double> NoiseGenerator::spawnFalsePositiveFieldLine(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ)
	{
		if(NoiseConfiguration::visionFieldLinesFalsePositives)
		{
			return virtualVisionNoise->spawnFalsePositive(limitsX, limitsY, limitsZ);
		}
		return defaultPercept;
	}

	vector<double> NoiseGenerator::spawnFalsePositiveGoal(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ)
	{
		if(NoiseConfiguration::visionGoalFalsePositives)
		{
			return virtualVisionNoise->spawnFalsePositive(limitsX, limitsY, limitsZ);
		}
		return defaultPercept;
	}

	vector<double> NoiseGenerator::spawnFalsePositiveRobot(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ)
	{
		if(NoiseConfiguration::visionRobotsFalsePositives)
		{
			return virtualVisionNoise->spawnFalsePositive(limitsX, limitsY, limitsZ);
		}
		return defaultPercept;
	}
}
